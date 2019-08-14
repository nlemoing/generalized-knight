package main

import (
	"net/http"
	"fmt"
	"strconv"
	"os"
	"os/exec"
	"bytes"
	"hash/fnv"
	"time"
	"io/ioutil"
)

func min(a, b int) int {
	if a < b {
		return a
	}
	return b
}


func HSL2HSV(hs, ss, ls string) (int, int, int) {
	h, _ := strconv.Atoi(hs)
	l, _ := strconv.Atoi(ls)
	shsl, _ := strconv.Atoi(ss)
	v := l + ((shsl * min(l, 100 - l))/100)
	s := 0
	if v != 0 {
		s = 200 - (200 * l/v)
	}
	h = h / 2
	s = (s * 255)/100
	v = (v * 255)/100
	return h, s, v
}

func getJobId(conf string) string {
	input := []byte(conf)
	curTime, err := time.Now().MarshalText()
	if err != nil {
		curTime = []byte{}
	}
	input = append(input, curTime...)
	h := fnv.New32()
	h.Write(input)
	return fmt.Sprintf("%x", h.Sum(nil))
}

func writeConfig(r *http.Request) (string, error) {
	inp := map[string]string{}
	for k, v := range r.MultipartForm.Value {
		inp[k] = v[0]
	}
	// Color
	lh, ls, lv := HSL2HSV(inp["low-hue"], inp["low-sat"], inp["low-light"])
	hh, hs, hv := HSL2HSV(inp["high-hue"], inp["high-sat"], inp["high-light"])
	lo_color := fmt.Sprintf("%d %d %d\n", lh, ls, lv)
	hi_color := fmt.Sprintf("%d %d %d\n", hh, hs, hv)
	// Save
	save := "n\n"
	if inp["animated"] == "on" {
		save = "y\n"
	}
	// Board
	bw, bh, sf := inp["board-width"], inp["board-height"], inp["scale-factor"]
	board := fmt.Sprintf("%s %s %s\n", bw, bh, sf)
	// Knight
	ka, kb := inp["knight-a"], inp["knight-b"]
	knight := fmt.Sprintf("%s %s\n", ka, kb)
	// Type-dependent
	mvmt := fmt.Sprintf("%s %s\n", inp["sb-row"], inp["sb-col"])
	if inp["movement-type"] == "rw" {
		mvmt += fmt.Sprintf("%s %s\n", inp["sb-width"], inp["sb-height"])
		mvmt += fmt.Sprintf("%s %s\n", inp["iterations"], inp["steps"])
		trace := "n\n"
		if inp["trace-paths"] == "on" {
			trace = "y\n"
		}
		mvmt += trace
	}

	config := lo_color + hi_color + save + board + knight + mvmt

	jobId := getJobId(config)
	workspace, err := ioutil.TempDir("", "knight")
	if err != nil {
		return "", err
	}
	defer os.RemoveAll(workspace)

	cmd := exec.Command("./scripts/knight", inp["movement-type"], workspace)
	cmd.Stdin = bytes.NewBuffer([]byte(config))
	cmd.Stdout = os.Stdout
	if err := cmd.Run(); err != nil {
		return "", err
	}

	imageType := ".png"
	if inp["animated"] == "on" {
		imageType = ".gif"
		makeGif := exec.Command("./scripts/make_gif", workspace)
		makeGif.Stdout = os.Stdout
		if err := makeGif.Run(); err != nil {
			return "", err
		}
	}

	src := workspace + "/final" + imageType
	dest := "images/" + jobId + imageType

	copyOutput := exec.Command("cp", src, dest)
	if err := copyOutput.Run(); err != nil {
		return "", err
	}

	return "/" + dest, nil
}

func createImage(w http.ResponseWriter, r *http.Request) {
	if r.Method != "POST" {
		http.NotFound(w, r)
		return
	}
	r.ParseMultipartForm(4096)
	loc, err := writeConfig(r)
	if err != nil {
		fmt.Print(err)
		http.Error(w, "Internal server error", 500)
		return
	}

	w.WriteHeader(http.StatusCreated)
	w.Write([]byte(loc))
}

func main() {
	http.Handle("/", http.FileServer(http.Dir(".")))
	http.HandleFunc("/api/knight/createImage", createImage)
	http.ListenAndServe(":8000", nil)
}

package main

import (
	"net/http"
	"fmt"
	"os"
	"os/exec"
	"bytes"
	"hash/fnv"
	"time"
	"io/ioutil"
	"strconv"
	"errors"
)

type config struct {
	movement string
	low, high Color
	animated bool
	bWidth, bHeight, scale int
	knightA, knightB int
	sRow, sCol, sWidth, sHeight int
	iterations, steps int
	trace bool
}

func (conf *config) String() string {
	c := ""
	c += fmt.Sprintf("%d %d %d\n", conf.low.v1, conf.low.v2, conf.low.v3)
	c += fmt.Sprintf("%d %d %d\n", conf.high.v1, conf.high.v2, conf.high.v3)
	if conf.animated {
		c += "y\n"
	} else {
		c += "n\n"
	}
	c += fmt.Sprintf("%d %d %d\n", conf.bWidth, conf.bHeight, conf.scale)
	c += fmt.Sprintf("%d %d\n", conf.knightA, conf.knightB)
	c += fmt.Sprintf("%d %d %d %d\n", conf.sRow, conf.sCol, conf.sWidth, conf.sHeight)
	c += fmt.Sprintf("%d %d\n", conf.iterations, conf.steps)
	if conf.trace {
		c += "y\n"
	} else {
		c += "n\n"
	}
	return c
}

func stringsToInts(strs ...string) ([]int, error) {
	ints := []int{}
	for _, str := range strs {
		i, err := strconv.Atoi(str)
		if err != nil {
			return []int{}, nil
		}
		ints = append(ints, i)
	}
	return ints, nil
}

func getConfig(r *http.Request) (*config, error) {
	inp := map[string]string{}
	for k, v := range r.MultipartForm.Value {
		inp[k] = v[0]
	}

	conf := new(config)

	if inp["movement-type"] != "rw" && inp["movement-type"] != "bfs" {
		return conf, errors.New("Invalid movement type")
	}
	conf.movement = inp["movement-type"]

	// Color
	lowValues, err := stringsToInts(inp["low-hue"], inp["low-sat"], inp["low-light"])
	if err != nil {
		return conf, err
	}
	conf.low, err = HslToHsv(MakeColor(lowValues[0], lowValues[1], lowValues[2]))
	if err != nil {
		return conf, err
	}
	conf.low.ToOpenCVRange()

	highValues, err := stringsToInts(inp["high-hue"], inp["high-sat"], inp["high-light"])
	if err != nil {
		return conf, err
	}
	conf.high, err = HslToHsv(MakeColor(highValues[0], highValues[1], highValues[2]))
	if err != nil {
		return conf, err
	}
	conf.high.ToOpenCVRange()

	// Animated
	conf.animated = inp["animated"] == "on"

	// Board
	board, err := stringsToInts(inp["board-width"], inp["board-height"], inp["scale-factor"])
	if err != nil {
		return conf, err
	}
	conf.bWidth, conf.bHeight, conf.scale = board[0], board[1], board[2]

	// Knight
	knight, err := stringsToInts(inp["knight-a"], inp["knight-b"])
	if err != nil {
		return conf, err
	}
	conf.knightA, conf.knightB = knight[0], knight[1]

	// Start
	start, err := stringsToInts(inp["sb-row"], inp["sb-col"], inp["sb-width"], inp["sb-height"])
	if err != nil {
		return conf, err
	}
	conf.sRow, conf.sCol, conf.sWidth, conf.sHeight = start[0], start[1], start[2], start[3]

	// RW specific
	rw, err := stringsToInts(inp["iterations"], inp["steps"])
	if err != nil {
		return conf, err
	}
	conf.iterations, conf.steps = rw[0], rw[1]

	conf.trace = inp["trace-paths"] == "on"

	return conf, nil
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

func writeImage(conf *config) (string, error) {
	jobId := getJobId(conf.String())
	workspace, err := ioutil.TempDir("", "knight")
	if err != nil {
		return "", err
	}
	defer os.RemoveAll(workspace)

	cmd := exec.Command("./scripts/knight", conf.movement, workspace)
	cmd.Stdin = bytes.NewBuffer([]byte(conf.String()))
	cmd.Stdout = os.Stdout
	if err := cmd.Run(); err != nil {
		return "", err
	}

	imageType := ".png"
	if conf.animated {
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

func CreateImage(w http.ResponseWriter, r *http.Request) {
	if r.Method != "POST" {
		http.NotFound(w, r)
		return
	}
	r.ParseMultipartForm(4096)
	conf, err := getConfig(r)
	if err != nil {
		fmt.Print(err)
		http.Error(w, "Bad Request", http.StatusBadRequest)
		return
	}
	loc, err := writeImage(conf)
	if err != nil {
		fmt.Print(err)
		http.Error(w, "Internal Server Error", http.StatusInternalServerError)
	}

	w.WriteHeader(http.StatusCreated)
	w.Write([]byte(loc))
}

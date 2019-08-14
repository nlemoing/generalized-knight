package main

import (
	"net/http"
)

func main() {
	http.Handle("/", http.FileServer(http.Dir(".")))
	http.HandleFunc("/api/knight/createImage", CreateImage)
	http.ListenAndServe(":8000", nil)
}

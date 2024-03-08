package main

import (
	"gorail/mylib"
)

func main() {
	NumBytes := mylib.Retrieve_Bytes()
	mylib.Rail_Generation(20)
	println("Num Bytes: ", NumBytes)

}

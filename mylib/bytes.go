package mylib

import (
	"fmt"
	"os"
)

func Retrieve_Bytes() int {
	// Open input file
	Ifile, err := os.Open("test.txt")
	if err != nil {
		fmt.Println("Error opening file:", err)
		return -1
	}
	defer Ifile.Close()

	// Retrieve Number of bytes that will be passed to the rail generator function
	IfileInfo, _ := Ifile.Stat()
	IfileSize := IfileInfo.Size()
	return int(IfileSize)

	/*
		// Open output file
		Ofile, err := os.Create("output.txt")
		if err != nil {
			fmt.Println("Error creating output file:", err)
			return -2
		}

		defer Ofile.Close()

		// Specify the number of bytes to read at a time
		chunkSize := 10 // Change this to whatever chunk size you want
		data := make([]byte, chunkSize)

		// Loop until end of file
		for {
			// Read a chunk of bytes from the file
			bytesRead, err := Ifile.Read(data)
			if err != nil {
				fmt.Println("Error reading file:", err)
				return -3
			}

			// Exit the loop if no more bytes are read
			if bytesRead == 0 {
				break
			}

			// Convert Bytes to single block of bits
			var BitBlock uint64
			for i := 0; i < bytesRead; i++ {
				BitBlock |= uint64(data[i]) << uint(8*i)
			}

			//Modify the bit block here
			//ModifiedBitBlock := operation(BitBlock)

			//ModifiedBitBLock
		}*/
}

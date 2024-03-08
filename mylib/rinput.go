package mylib

import (
	"fmt"
	"math/rand"
	"os"
	"strconv"
	"time"
)

func Rail_Generation(ByteBlocks uint32) {
	// Set the seed for random number generation
	rand.NewSource(time.Now().UnixNano())

	// Define the start and end time for the range
	startTime := time.Date(1000, time.January, 0, 0, 0, 0, 0, time.UTC)
	endTime := time.Now().UnixNano()

	// Generate a random duration within the specified range
	randomDuration := time.Duration(rand.Int63n(endTime-startTime.Unix())) * time.Second

	// Create a random time within the specified range
	randomTime := startTime.Add(randomDuration)

	// Print the random time
	rand.NewSource(randomTime.UnixNano())

	// Open Key file for writing
	file, err := os.Create("key.rg")
	if err != nil {
		fmt.Println("Error:", err)
		return
	}
	defer file.Close()

	//Generate random rail numbers
	for i := 0; i < int(ByteBlocks); i++ {
		rNum := rand.Intn(15+1-2) + 2

		_, err := file.WriteString(strconv.Itoa(rNum))
		if err != nil {
			fmt.Println("Error:", err)
			return
		}
	}

}

func UTF_RAND_INPUT() {
	//Ensure both values are valid for number of rails
	var input string
	fmt.Println("Enter a single line of text:")
	fmt.Scanln(&input)

	// Print the UTF-8 code points of each character in the string as integers
	fmt.Println("UTF-8 code points as integers:")
	total := uint16(0)
	for _, char := range input {
		intValue := int(char) // Convert rune to integer
		total += uint16(intValue)
	}
	fmt.Println(total)
	fmt.Println()
}

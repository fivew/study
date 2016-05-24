// echo 2 programe for test for

package main

import (
	"fmt"
	"os"
)

func main() {
	s, sep := "", ""
	//  for index, value in range
	for _, arg := range os.Args[1:] {
		s += sep + arg
		sep = " "
	}

	fmt.Println(s)
}

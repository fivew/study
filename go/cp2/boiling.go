// boiling for const

package main

import "fmt"

const boilingF = 212.1

func main() {
	var f = boilingF
	var c = (f - 32) * 5 / 9
	fmt.Printf("boiling point = %gF or %gC\n", f, c)

}

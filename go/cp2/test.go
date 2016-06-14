package main

import (
	"fmt"
	"tmpconv"
)

type A int
type B int

func main() {
	var a A
	var b B
	fmt.Printf("%d\n", B(a))
	fmt.Printf("%d\n", int(b))
	//fmt.Printf("%v\n", a == b)

	var c tmpconv.F = 123
	fmt.Println(c.String())
	fmt.Printf("pc is %d, %#[1]X\n", tmpconv.Pc)
}

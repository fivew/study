package tmpconv

import "fmt"

var Pc int

func init() {
	fmt.Printf("init: pc = %d\n", Pc)
	Pc = 1222
	fmt.Printf("init: pc = %d\n", Pc)
}

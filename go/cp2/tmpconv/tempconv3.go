package tmpconv

import "fmt"

type C float64
type F float64

const (
	ZeroC    C = -273.15
	FreeC    C = 0
	BoilingC C = 100
)

func init() {
	fmt.Printf("1.init\n")
}

func (c C) String() string { return fmt.Sprintf("%gC", c) }
func (c F) String() string { return fmt.Sprintf("%gF", c) }

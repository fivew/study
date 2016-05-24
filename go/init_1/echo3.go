// echo 3 programe for join
package main

import "fmt"
import "os"
import "strings"

func main() {
	fmt.Println(strings.Join(os.Args[1:], " "))
	fmt.Println(os.Args[:])
}

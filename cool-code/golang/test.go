package main
import "fmt"
/*
切片并不存储任何数据，它只是描述了底层数组中的一段。
更改切片的元素会修改其底层数组中对应的元素。
与它共享底层数组的切片都会观测到这些修改。
*/
func main() {
	str := [4]string{
	    "aaa",
	    "bbb",
	    "ccc",
	    "ddd",
	}
	fmt.Println("str", str, len(str))

	a := str[0:2]
	b := str[1:3]
	fmt.Println("a, b", a, b)

	b[0] = "XXX"

}

package main

import "fmt"

func t_bool() {
    var v1, v2 bool         // 声明变量，默认值为 false
    v1 = true               // 赋值
    v3, v4 := false, true   // 声明并赋值

    fmt.Print("v1:", v1)   // v1 输出 true
    fmt.Print("\nv2:", v2) // v2 没有重新赋值，显示默认值：false
    fmt.Print("\nv3:", v3) // v3 false
    fmt.Print("\nv4:", v4) // v4 true
}

func main(){
	t_bool()
}

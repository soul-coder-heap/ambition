package main

import (
    "context"
    "fmt"

    "github.com/docker/docker/api/types"
    "github.com/docker/docker/client"
)

func main() {
    cl, err := client.NewEnvClient()
    if err != nil {
        fmt.Println("Unable to create docker client")
        panic(err)
    }

    fmt.Println(cl.ImageList(context.Background(), types.ImageListOptions{}))

}

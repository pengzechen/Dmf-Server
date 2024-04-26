package main

import (
	"C"
	"lib/request"
)
import "lib/response"

func main() {}

// go build -buildmode=c-archive -o librr.a

//export req_test
func req_test(req_str string) {
	req := request.ReqInit(false)
	req.ParseHeader(req_str)
	req.ParseBody([]byte(req_str))

	// fmt.Println(req.Method, req.Path, req.Protocol)
}

//export res_test
func res_test(str *string) {
	res := response.DefaultTest()
	*str = string(res.GenerateResponse())
}

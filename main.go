package main

/*
#cgo LDFLAGS: -L. -ltree
#cgo CFLAGS: -I.
#include "tree.h"
*/
import (
	"C"
	"fmt"
)
import "sync"

func main() {
	fmt.Println("pthread tree started")
	// C.insert_wrapper(C.int(5))
	// C.insert_wrapper(C.int(10))
	// C.insert_wrapper(C.int(15))

	// fmt.Print("Inorder traversal: ")
	// C.inorder_wrapper()
	// fmt.Println()

	// C.freeTree_wrapper()

	root := &Node{Data: 10}
	values1 := []int{5, 3, 7, 1, 4, 6, 8, 2, 9}
	values2 := []int{20, 15, 30, 25, 35, 22, 28, 32, 40}

	var wg sync.WaitGroup
	wg.Add(2)

	go insertValues(root, values1, &wg)
	go insertValues(root, values2, &wg)

	wg.Wait()

	fmt.Println("Inorder traversal of the binary tree:")
	root.Inorder()
	fmt.Println()
}

// $ gcc -shared -o libtree.so -fPIC tree.c -lpthread
// gcc -shared -o libtree.so -fPIC -I../ptree ../ptree/tree.c -lpthread
// gcc -shared -o libtree.so -fPIC tree.c -lpthread
// export LD_LIBRARY_PATH=./ptree

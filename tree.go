package main

import (
	"fmt"
	"sync"
)

type Node struct {
	Data  int
	Left  *Node
	Right *Node
	mu    sync.Mutex
}

func (n *Node) Insert(value int) {
	n.mu.Lock()
	defer n.mu.Unlock()

	if value < n.Data {
		if n.Left == nil {
			n.Left = &Node{Data: value}
		} else {
			n.Left.Insert(value)
		}
	} else {
		if n.Right == nil {
			n.Right = &Node{Data: value}
		} else {
			n.Right.Insert(value)
		}
	}
}

func (n *Node) Inorder() {
	if n == nil {
		return
	}

	n.Left.Inorder()
	fmt.Print(n.Data, " ")
	n.Right.Inorder()
}

func insertValues(root *Node, values []int, wg *sync.WaitGroup) {
	defer wg.Done()
	for _, value := range values {
		root.Insert(value)
	}
}

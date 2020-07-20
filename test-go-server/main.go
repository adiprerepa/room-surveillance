package main

import (
	"fmt"
	"log"
	"net"
	"os"

	pb "./pb"
	"github.com/golang/protobuf/proto"
)

var (
	addr, network string
)

func main() {
	// setup flags
	network = "tcp"
	addr = ":3570"

	ln, err := net.Listen(network, addr)
	if err != nil {
		log.Println(err)
		os.Exit(1)
	}
	defer ln.Close()

	log.Printf("Temperator Service started: (%s) %s\n", network, addr)

	// connection loop
	for {
		conn, err := ln.Accept()
		if err != nil {
			log.Println(err)
			conn.Close()
			continue
		}
		log.Println("Connected to ", conn.RemoteAddr())
		go handleConnection(conn)
	}
}

func handleConnection(conn net.Conn) {
	defer func() {
		log.Println("INFO: closing connection")
		if err := conn.Close(); err != nil {
			log.Println("error closing connection:", err)
		}
	}()

	buf := make([]byte, 1024)

	n, err := conn.Read(buf)
	if err != nil {
		log.Println(err)
		return
	}
	if n <= 0 {
		log.Println("no data received")
		return
	}

	var e pb.AlertThresholdCross
	if err := proto.Unmarshal(buf[:n], &e); err != nil {
		log.Println("failed to unmarshal:", err)
		return
	}

	fmt.Printf("got %d\n", e.CrossedThresh)
}

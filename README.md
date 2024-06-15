# C_SocketProgramming

This repo is for me to learn how to use sockets for communication between servers and clients.

## Current implementation

I have implemented a simple TCP socket connection between a client and a server on my local machine on port 9002

## Process

The server is established using the following workflow:

1. Create socket()
2. Bind the socket() to my IP and desired port
3. Call listen() and allow conenctions to come in from clients
4. Wait for connections and call accept() when clients come in
5. Send a message to the client

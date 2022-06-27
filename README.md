# Tcp_Client-Server
File transfer from client to server using cpp

The given assignment asks us to implement a basic server and client using sockets.
A network socket is an internal endpoint which allows communication between two different processes
on the same or different machines.
A socket is bound to a port number so that the TCP layer can identify the application that data is
destined to be sent to.
The server program just waits, listening to the socket for a client to make a connection request.
On the client-side: The client knows the hostname of the machine on which the server is running and
the port number on which the server is listening. To make a connection request, the client tries to
rendezvous with the server on the server's machine and port. The client also needs to identify itself to
the server so it binds to a local port number that it will use during this connection. This is usually
assigned by the system.

If everything goes well, the server accepts the connection. Upon acceptance, the server gets a new
socket bound to the same local port and also has its remote endpoint set to the address and port of the
client. It needs a new socket so that it can continue to listen to the original socket for connection
requests while tending to the needs of the connected client.


On the client side, if the connection is accepted, a socket is successfully created and the client can use
the socket to communicate with the server.
The client and server can now communicate by writing to or reading from their sockets.

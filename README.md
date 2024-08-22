# Socket_Programming_practices
LAB: Establishment of TCP SOCK_STREAM based connectivity for sending asynchronous state of message sending and reading
1) TCPclient.c - Program that receives the message from server confirming the IPC is established over SOCK_STREAM for message exchanging.
2) TCPserver.c - Program that initializes the IPC connectivity towards start of message exchanging- which actually sends the messages on successfull connection.

STEPS:
1) Required to compile the server implementation : gcc -o <server binary filename> TCPserver.c>
2) Required to compile the client implementation : gcc -o <client binary filename> TCPclient.c>
3) FIRST run the [<server binary filename> in a seperate window] (or) [run as Background process with bg ./<server binary filename> to check on same WINDOW for client repsonse] - For establishment of TCP port and SOCK address for IPC communication.
4) SECOND run the [<client binary filename> in a seperate window ] for IPC communication to get used for Message exchange.



=======================================================
Practice and debugging:
=======================

1) echo_server_pract.c
2) echo_client_pract.c


These files are included to practice on debugging and locating the exact problem through gdb on attending "Bad file descriptor" problem.
share me the steps to debug
=======================================================
Resolved above problem and Fixed:
=================================
1) accept and connect - parameters differentiation and understandings
2) communication with software flitches and getting calmness algo on fixing - to bring as expected
=======================================================

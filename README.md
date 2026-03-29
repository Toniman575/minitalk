_This project has been created as part of the 42 curriculum by asadik._

# Description
This project creates two programs: a client and a server. The server waits for signals from the client, reconstructs the message (transmitted bit-by-bit using `SIGUSR1` and `SIGUSR2`) into a string, and prints it to the standard output.

# Instructions
Compile with `make`. To compile with debug flags, use `make debug`. All other standard Make rules apply.<br>
The server prints its PID to the standard output upon launch. The client takes two arguments: the server PID and the string to be sent. If the PID is invalid or the number of arguments is incorrect, an error message is printed to the standard output, and the client program exits gracefully.<br>
If the server does not receive a message for 30 seconds it will exit gracefully.

# Resources
[Bitwise Operators in C](https://www.geeksforgeeks.org/c/bitwise-operators-in-c-cpp/).<br>
[Global Variables in C](https://www.geeksforgeeks.org/c/global-variables-in-c/).<br>
[Signals in C language](https://www.geeksforgeeks.org/c/signals-c-language/).
[Set, Clear and Toggle a Given Bit of a Number in C](https://www.geeksforgeeks.org/dsa/set-clear-and-toggle-a-given-bit-of-a-number-in-c/).
Discussions with peers and AI helped me figure out async safety.
# PrivCommunication

**CURRENTLY NOT COMPILING - BUG IS BEING FIXED**
private and invisible communication (inspired by snake malware)
it's not meant to work. it's meant to be fun to make this project.
Communication is encrypted and sent via popular protocols like HTTP,DNS,FTP spoofing as normal communication in those protocols

**Building:**
gcc -o server.o server.c
gcc -o client.o client.c

Supports only linux.

**Setting up:**

_FOR CLIENT:_

set PASSWORD const as your password (must be long and complicated)

set PORT as port you use

set SERVER_IP

set BUFFSIZE (the amount of data that you can sent in 1 time)

_FOR SERVER_
the same things without SERVER_IP but with ACCEPTED_IPS

_new feature (now only for client) - USER_SETUP_

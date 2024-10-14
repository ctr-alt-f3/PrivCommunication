# PrivCommunication
# **DISCLAIEMER: DON'T USE CURRENT VERSION - FUNCTIONALLITY IS BEING ADDED, SO NOW CODE IS NOT WORKIG (NOT COMPILING)**
private and invisible communication (inspired by snake malware)
it's not meant to work. it's meant to be fun to make this project.
Communication is encrypted and sent via popular protocols like HTTP,DNS,FTP spoofing as normal communication in those protocols
![working](https://github.com/github/docs/actions/workflows/main.yml/badge.svg?event=push)

**Building:**
gcc -o server.o server.c
gcc -o client.o client.c

Supports only linux.

**Setting up:**

*FOR CLIENT:*

set PASSWORD const as your password (must be long and complicated)

set PORT as port you use

set SERVER_IP

set BUFFSIZE (the amount of data that you can sent in 1 time)

*FOR SERVER*
the same things without SERVER_IP but with ACCEPTED_IPS

Poller-Server-Client-CPP

This repository contains a C++ implementation of a server-client system for conducting polls. The server receives names of voters and their corresponding votes from the client and calculates the poll log and statistics. The results are saved in separate text files, namely "pollLog.txt" and "pollStats.txt". Additionally, the repository includes two auxiliary scripts: "create_input.sh" and "processLogFile.sh".

Usage
To run the server and client, use the following commands in the command prompt:
First make the 2 files,then use this type of commands to run server and client,
first run server,then the client.And remember to be the same port.

Server:


prompt> poller [portNum] [pollLog.txt] [pollStats.txt]


Client:

prompt> pollSwayer [serverName] [portNum] [inputFile.txt]


Repository Structure
Server: Contains the implementation of the server.
Client: Contains the implementation of the client.
create_input.sh: Shell script for generating an input file with random voter names and votes.
processLogFile.sh: Shell script for comparing server results with the output of create_input.sh.
pollLog.txt: Text file to store the poll log generated by the server.
pollStats.txt: Text file to store the poll statistics generated by the server.

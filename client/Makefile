OBJS	= ClientArgumentManager.o ClientMasterThread.o ClientSocketManager.o ClientThread.o ClientWorkerThread.o Transport.o main.o
SOURCE	= ClientArgumentManager.cpp ClientMasterThread.cpp ClientSocketManager.cpp ClientThread.cpp ClientWorkerThread.cpp Transport.cpp main.cpp
HEADER	= ClientArgumentManager.h ClientMasterThread.h ClientSocketManager.h ClientThread.h ClientWorkerThread.h Transport.h
OUT	= pollSwayer
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = -lpthread

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

ClientArgumentManager.o: ClientArgumentManager.cpp
	$(CC) $(FLAGS) ClientArgumentManager.cpp 

ClientMasterThread.o: ClientMasterThread.cpp
	$(CC) $(FLAGS) ClientMasterThread.cpp 

ClientSocketManager.o: ClientSocketManager.cpp
	$(CC) $(FLAGS) ClientSocketManager.cpp 

ClientThread.o: ClientThread.cpp
	$(CC) $(FLAGS) ClientThread.cpp 

ClientWorkerThread.o: ClientWorkerThread.cpp
	$(CC) $(FLAGS) ClientWorkerThread.cpp 

Transport.o: Transport.cpp
	$(CC) $(FLAGS) Transport.cpp 

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp 


clean:
	rm -f $(OBJS) $(OUT)

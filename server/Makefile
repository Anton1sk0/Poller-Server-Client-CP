OBJS	= ArgumentManager.o main.o MasterThread.o PartyManager.o ProducerConsumerQueue.o SocketManager.o Thread.o Transport.o VoteManager.o WorkerThread.o
SOURCE	= ArgumentManager.cpp main.cpp MasterThread.cpp PartyManager.cpp ProducerConsumerQueue.cpp SocketManager.cpp Thread.cpp Transport.cpp VoteManager.cpp WorkerThread.cpp
HEADER	= ArgumentManager.h List.h MasterThread.h PartyManager.h ProducerConsumerQueue.h SocketManager.h Thread.h Transport.h VoteManager.h WorkerThread.h
OUT	= poller
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = -lpthread

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

ArgumentManager.o: ArgumentManager.cpp
	$(CC) $(FLAGS) ArgumentManager.cpp 

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp 

MasterThread.o: MasterThread.cpp
	$(CC) $(FLAGS) MasterThread.cpp 

PartyManager.o: PartyManager.cpp
	$(CC) $(FLAGS) PartyManager.cpp 

ProducerConsumerQueue.o: ProducerConsumerQueue.cpp
	$(CC) $(FLAGS) ProducerConsumerQueue.cpp 

SocketManager.o: SocketManager.cpp
	$(CC) $(FLAGS) SocketManager.cpp 

Thread.o: Thread.cpp
	$(CC) $(FLAGS) Thread.cpp 

Transport.o: Transport.cpp
	$(CC) $(FLAGS) Transport.cpp 

VoteManager.o: VoteManager.cpp
	$(CC) $(FLAGS) VoteManager.cpp 

WorkerThread.o: WorkerThread.cpp
	$(CC) $(FLAGS) WorkerThread.cpp 


clean:
	rm -f $(OBJS) $(OUT)
CXX=g++
CFLAGS=-g -Wall
DEMULTIPLEX=Select_Demultiplexer.o
OBJS=Reactor.o $(DEMULTIPLEX) Acceptor_Handler.o Echo_Handler.o
BIN=client server

.SUFFIXES:.cpp .o

.cpp.o:
	$(CXX) -c $< $(CFLAGS) 

all:$(BIN)

server:Server.o $(OBJS)
	$(CXX) -o $@ $^ 

client:Client.o
	$(CXX) -o $@ $^ 

clean:
	$(RM) *.o  $(BIN) core*
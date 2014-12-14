objects= main.o protocol/protocol.o socket/socket_server.o

edit : $(objects)
	g++ -o socket_server  $(objects)

socket/socket_server.o	: socket/socket_server.h
protocol/protocol.o		: protocol/protocol.h
main.o					: protocol/protocol.h socket/socket_server.h

.PHONY : clean
clean : 
	rm socket_server $(objects)

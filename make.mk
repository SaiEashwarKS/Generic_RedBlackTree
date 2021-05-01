a.out : client.o
	g++ client.o 
client.o : client.cpp rbt.h
	g++ -c client.cpp
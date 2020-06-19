INCLUDE = -I F:\AVC\SFML\include
LIBS = -L F:\AVC\SFML\lib
server3.exe: server3.o 
	g++ $(LIBS) -o server3 server3.o -lsfml-window  -lsfml-graphics -lsfml-system -lsfml-network 
server3.o: server3.cpp 
	g++  -c $(INCLUDE) server3.cpp 

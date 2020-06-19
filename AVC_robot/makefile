INCLUDE = -I F:\AVC\SFML\include
LIBS = -L F:\AVC\SFML\lib
robot.exe: robot.o 
	g++ $(LIBS) -o robot robot.o -lsfml-window  -lsfml-graphics -lsfml-system -lsfml-network 
robot.o: robot.cpp 
	g++  -c $(INCLUDE) robot.cpp 

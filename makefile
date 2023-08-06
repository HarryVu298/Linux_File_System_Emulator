CC = g++
CFLAGS = -std=c++14 -Wall

main: main.o File.o Directory.o System.o
	$(CC) $(CFLAGS) main.o File.o Directory.o System.o -o main

main.o: main.cpp File.h Directory.h System.h
	$(CC) $(CFLAGS) -c main.cpp

File.o: File.cpp File.h System.h
	$(CC) $(CFLAGS) -c File.cpp

Directory.o: Directory.cpp Directory.h System.h
	$(CC) $(CFLAGS) -c Directory.cpp

System.o: System.cpp System.h
	$(CC) $(CFLAGS) -c System.cpp

clean:
	rm *.o main

CC = g++
CFLAGS = -Wall 
DEPS = header.h 
OBJ = main.o directoryFunctions.o header.h
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

main: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf *o main
CC = g++
CFLAGS = -Wall 
DEPS = headers.h 
OBJ = main.o dirFunctions.o keyFunctions.o normalMode.o 
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

main: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf *o main

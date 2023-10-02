CC=g++
CFLAGS=-I.
OBJ = main.o 

%.o: %.cpp %.hpp
	$(CC) -c -o $@ $< $(CFLAGS)

li4th: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
	./li4th.exe

clean: li4th.exe $(OBJ)
	rm $(OBJ)
	rm li4th.exe
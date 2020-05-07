CC = gcc
CFLAGS = -Wall -O2 -g
LIBS = -lglut -lGLU -lpthread -lGL
EXANAME = snix

$(EXANAME): main.c graphics.o field.o snake.o food.o point.o
	$(CC) main.c graphics.o field.o snake.o food.o point.o -o $(EXANAME) $(CFLAGS) $(LIBS)

field.o: field.c
	$(CC) -c field.c -o field.o $(CFLAGS) 

food.o: food.c
	$(CC) -c food.c -o food.o $(CFLAGS) 

graphics.o: graphics.c
	$(CC) -c graphics.c -o graphics.o $(LIBS) $(CFLAGS) 

point.o: point.c
	$(CC) -c point.c -o point.o $(CFLAGS) 

snake.o: snake.c
	$(CC) -c snake.c -o snake.o $(CFLAGS)

run: $(EXANAME)
	./$(EXANAME)

build:
	make clean
	make

clean clear:
	rm *.o $(EXANAME)

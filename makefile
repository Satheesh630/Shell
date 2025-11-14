CC = cc
CFLAGS = -Wall -Wextra -g
OBJ = custom_shell.o src.o

all: shell

shell: $(OBJ)
	@$(CC) $(OBJ) -o shell

custom_shell.o: custom_shell.c header.h
	@$(CC) $(CFLAGS) -c custom_shell.c

src.o: src.c header.h
	@$(CC) $(CFLAGS) -c src.c

clean:
	@rm -f *.o shell


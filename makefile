CC = gcc
CFLAGS = -Wall -pedantic -Werror -Wextra -std=gnu11 -Wconversion
OBJS = objects#nombre de la carpeta donde se guardan los .o
SRC = source
BIN = binaries
#LIB = libraries
WHERE = -Wl,-rpath,.

all: mkdir $(BIN)/tcp_client $(BIN)/tcp_server 

mkdir:
	mkdir -p $(OBJS) $(SRC) $(BIN)


$(BIN)/tcp_client: $(SRC)/tcp_client.c
	$(CC) $(SRC)/tcp_client.c $(CFLAGS) -o $@ 
#$@ es una variable automática que se corresponde con el target que estoy creando

$(BIN)/tcp_server: $(SRC)/tcp_server.c 
	$(CC) $(SRC)/tcp_server.c $(CFLAGS) -o $@

clean:
	rm -rf $(BIN)

git: 
	git add $(SRC)/tcp_client.c $(SRC)/tcp_server.c
	
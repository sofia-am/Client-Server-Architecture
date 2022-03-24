CC = gcc
CFLAGS = -Wall -pedantic -Werror -Wextra -std=gnu11 -Wconversion
OBJS = obj#nombre de la carpeta donde se guardan los .o
SRC = src
BIN = bin
INC = inc
#LIB = libraries
DEP = inc/dependencies.h
WHERE = -Wl,-rpath,.

all: mkdir $(BIN)/ipv4_client $(BIN)/unix_client $(BIN)/ipv4_server $(BIN)/unix_server $(BIN)/ipv6_client $(BIN)/ipv6_server

mkdir:
	mkdir -p $(SRC) $(INC) $(BIN)

$(BIN)/ipv4_client: $(SRC)/dependencies.h $(SRC)/ipv4_client.c
	$(CC) $(SRC)/ipv4_client.c $(CFLAGS) -o $@ 
#$@ es una variable automática que se corresponde con el target que estoy creando

$(BIN)/ipv4_server: $(SRC)/dependencies.h $(SRC)/ipv4_server.c
	$(CC) $(SRC)/ipv4_server.c $(CFLAGS) -o $@

$(BIN)/unix_client: $(SRC)/dependencies.h $(SRC)/unix_client.c 
	$(CC) $(SRC)/unix_client.c $(CFLAGS) -o $@

$(BIN)/unix_server: $(SRC)/dependencies.h $(SRC)/unix_server.c 
	$(CC) $(SRC)/unix_server.c $(CFLAGS) -o $@

$(BIN)/ipv6_client: $(SRC)/dependencies.h $(SRC)/ipv6_client.c
	$(CC) $(SRC)/ipv6_client.c $(CFLAGS) -o $@ 

$(BIN)/ipv6_server: $(SRC)/dependencies.h $(SRC)/ipv6_server.c
	$(CC) $(SRC)/ipv6_server.c $(CFLAGS) -o $@ 

clean:
	rm -rf $(BIN) 

git: 
	git add $(SRC)/ipv4_client.c $(SRC)/ipv4_server.c
	
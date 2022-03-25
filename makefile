CC = gcc
CFLAGS = -Wall -pedantic -Werror -Wextra -std=gnu11 -Wconversion
OBJS = obj#nombre de la carpeta donde se guardan los .o
SRC = src
BIN = bin
INC = inc
LIB = libraries
DEP = inc/dependencies.h
WHERE = -Wl,-rpath,.

all: mkdir server

mkdir:
	mkdir -p $(SRC) $(BIN) $(LIB) $(OBJS)

lib_servers.a: servers.o
	ar rcs $(LIB)/$@ $(OBJS)/$<

servers.o: $(SRC)/server_config.c $(SRC)/server_config.h
	$(CC) -c $< $(CFLAGS) -o $(OBJS)/$@

lib_clients.a: client_config.o
	ar rcs $(LIB)/$@ $(OBJS)/$<

client_config.o: $(SRC)/client_config.c $(SRC)/client_config.h
	$(CC) -c $< $(CFLAGS) -o $(OBJS)/$@

server: server.o lib_servers.a 
	$(CC) -o $(BIN)/$@ $(OBJS)/$< $(LIB)/lib_servers.a

server.o: $(SRC)/server.c
	$(CC) -c $< -o $(OBJS)/$@

clean:
	rm -rf $(BIN) $(OBJS) $(LIB)

git: 
	git add $(INC)/ipv4_client.c $(INC)/ipv4_server.c
	
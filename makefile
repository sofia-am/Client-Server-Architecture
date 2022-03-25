CC = gcc 
CFLAGS = -g -Wall -pedantic -Werror -Wextra -std=gnu11 -Wconversion
OBJS = obj#nombre de la carpeta donde se guardan los .o
SRC = src
BIN = bin
INC = inc
LIB = lib
DEP = inc/dependencies.h
WHERE = -Wl,-rpath,.

all: mkdir server ipv4_client ipv6_client unix_client

mkdir:
	mkdir -p $(SRC) $(BIN) $(LIB) $(OBJS)

lib_servers.a: servers.o
	ar rcs $(LIB)/$@ $(OBJS)/$<

servers.o: $(SRC)/server_config.c $(SRC)/server_config.h
	$(CC) -c $< $(CFLAGS) -o $(OBJS)/$@

server: server.o lib_servers.a 
	$(CC) -o $(BIN)/$@ $(OBJS)/$< $(LIB)/lib_servers.a

server.o: $(SRC)/server.c
	$(CC) -c $< -o $(OBJS)/$@

ipv4_client: $(SRC)/ipv4_client.c $(SRC)/client_config.h
	$(CC) $< $(CFLAGS) -o $(BIN)/$@

ipv6_client: $(SRC)/ipv6_client.c $(SRC)/client_config.h
	$(CC) $< $(CFLAGS) -o $(BIN)/$@

unix_client: $(SRC)/unix_client.c $(SRC)/client_config.h
	$(CC) $< $(CFLAGS) -o $(BIN)/$@
	
#lib_clients.a: client_config.o
#	ar rcs $(LIB)/$@ $(OBJS)/$<

#client_config.o: $(SRC)/client_config.c $(SRC)/client_config.h
#	$(CC) -c $< $(CFLAGS) -o $(OBJS)/$@


#client: client.o lib_clients.a
#	$(CC) -o $(BIN)/$@ $(OBJS)/$< $(LIB)/lib_clients.a

#client.o: $(SRC)/client.c
#	$(CC) -c $< -o $(OBJS)/$@

clean:
	rm -rf $(BIN) $(OBJS) $(LIB)

	
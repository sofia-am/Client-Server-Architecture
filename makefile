CC = gcc
CFLAGS = -Wall -pedantic -Werror -Wextra -Wconversion -std=gnu11
OBJS = objects#nombre de la carpeta donde se guardan los .o
SRC = source
#LIB = libraries
WHERE = -Wl,-rpath,.

all: mkdir $(OBJS)/tcp_client $(OBJS)/tcp_server

mkdir:
	mkdir -p $(OBJS) $(SRC)


$(OBJS)/tcp_client: $(SRC)/tcp_client.c
	$(CC) $(SRC)/tcp_client.c $(CFLAGS) -o $@ 
#$@ es una variable automática que se corresponde con el target que estoy creando

$(OBJS)/tcp_server: $(SRC)/tcp_server.c 
	$(CC) $(SRC)/tcp_server.c $(CFLAGS) -o $@

clean:
	rm -rf $(OBJS)

git: 
	git add $(SRC)/tcp_client.c $(SRC)/tcp_server.c
	
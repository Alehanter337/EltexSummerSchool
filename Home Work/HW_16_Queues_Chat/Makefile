SERVER := server
CLIENT := client
SERVER_SOURCES := server.c
CLIENT_SOURCES := client.c

server: $(SERVER_SOURCES)
		@gcc $(SERVER_SOURCES) -o $(SERVER) -ansi -pedantic -Wall -lrt -lpthread

client: $(CLIENT_SOURCES)
		@gcc $(CLIENT_SOURCES) -o $(CLIENT) -ansi -pedantic -Wall -lrt -lpthread

.PHONY: clean
clean:
		@rm -rf $(SERVER)
		@rm -rf $(CLIENT)

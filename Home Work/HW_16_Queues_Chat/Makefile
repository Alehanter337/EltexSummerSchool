SERVER := server
CLIENT := client
SERVER_SOURCES := server.c
CLIENT_SOURCES := client.c

server: $(SERVER_SOURCES)
		@gcc $(SERVER_SOURCES) -o $(SERVER) -lrt -lpthread

client: $(CLIENT_SOURCES)
		@gcc $(CLIENT_SOURCES) -o $(CLIENT)  -lrt -lpthread

.PHONY: clean
clean:
		@rm -rf $(SERVER)
		@rm -rf $(CLIENT)

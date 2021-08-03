SERVER := server
CLIENT := client
SERVER_SOURCES := server.c
CLIENT_SOURCES := client.c

server: $(SERVER_SOURCES)
		@gcc $(SERVER_SOURCES) -o $(SERVER) -g

client: $(CLIENT_SOURCES)
		@gcc $(CLIENT_SOURCES) -o $(CLIENT)

.PHONY: clean
clean:
		@rm -rf $(SERVER)
		@rm -rf $(CLIENT)

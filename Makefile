.PHONY: server client

default: server client
	cp server/_build/server server.exe
	cp client/_build/client.jar client.jar

server:
	@make -C server

client:
	@make -C client

clean:
	@make -C server clean
	@make -C client clean
	rm -f server.exe
	rm -f client.jar


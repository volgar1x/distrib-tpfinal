.PHONY: server client

default: server client

server:
	@make -C server clean build

client:
	@make -C client clean build

run:
	@make -C server run &
	@make -C client run

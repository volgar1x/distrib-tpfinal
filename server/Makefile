NAME    = server
SRC_DIR = src
INC_DIR = include
OUT_DIR = _build
OPTI    = -O2

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OUT_DIR)/%.o)

CDEPS  = 
CFLAGS = -Wall $(OPTI) -I$(INC_DIR) $(CDEPS)
CC     = gcc $(CCMD) $(CFLAGS)

LDFLAGS =
LD      = gcc $(LDFLAGS)

all: clean build

$(OUT_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c -o $@ $^

pre_build:
	mkdir -p $(OUT_DIR)

build: pre_build $(OBJ)
	$(LD) -o $(OUT_DIR)/$(NAME) $(OBJ)

run: build
	$(OUT_DIR)/$(NAME)

clean:
	rm -rf $(OUT_DIR)

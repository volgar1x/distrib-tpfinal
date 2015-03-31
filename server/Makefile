include config.mk

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OUT_DIR)/%.o)

all: build

$(OUT_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -I$(INC_DIR) $(CDEPS) $(CFLAGS) -c -o $@ $^

pre_build:
	mkdir -p $(OUT_DIR)

build: pre_build $(OBJ)
	$(LD) $(LDFLAGS) -o $(OUT_DIR)/$(NAME) $(OBJ)

run: build
	$(OUT_DIR)/$(NAME)

clean:
	rm -rf $(OUT_DIR)

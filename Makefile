.PHONY: all run clean

CC := gcc-9

# compile flags
CFLAGS += -std=c18 -Wall -Wextra -Wpedantic -Waggregate-return -Wwrite-strings
CFLAGS += -Wvla -Wfloat-equal

VFLAGS += --leak-check=full --track-origins=yes

SRC_DIR := src
OBJ_DIR := obj
DOCS_DIR := docs
DATA_DIR := data

SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# executable
BIN := potter

all: $(BIN)

grade: $(BIN)
	./$(BIN)

debug: CFLAGS += -g3
debug: $(BIN)
# 	@gdb ./$(BIN)

valgrind: CFLAGS += -g3
valgrind: clean $(BIN)
	@valgrind $(VFLAGS) ./$(BIN)

clean: 
	@rm -rf $(BIN) $(OBJ_DIR)

# creates object files from .c files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $@

$(OBJS): | $(OBJ_DIR)

# creates executable from object
$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@
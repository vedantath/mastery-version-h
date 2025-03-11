# Compiler and flags
CC = gcc
CFLAGS = -Wall
DEBUG_FLAGS = -g -DDEBUG

#dirs
OUTPUT_DIR = outputs
BIN_DIR = bin

# Source and object files
SRC = main.c parser.c grind.c
OBJ = $(patsubst %.c,$(BIN_DIR)/%.o,$(SRC))
EXEC = $(BIN_DIR)/a.out
REFERENCE_EXEC = ref.out

# Default target (the executable)
$(EXEC): $(BIN_DIR) $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Pattern rule for compiling .c files into .o files
$(BIN_DIR)/%.o: %.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Debug target (compiles with debug flags)
debug: CFLAGS += $(DEBUG_FLAGS)
debug: $(EXEC)

# Checks all outputs for all test cases
check: $(EXEC)
	@for testfile in testcases/*; do \
		echo "Running $$testfile..."; \
		./$(EXEC) -t $$testfile; \
	done

# compare target compares output with ref.out
comp: $(EXEC)
	@mkdir -p $(OUTPUT_DIR)
	@for testfile in testcases/*; do \
		base_name=$$(basename $$testfile); \
		./$(EXEC) -t $$testfile > $(OUTPUT_DIR)/$$base_name.out; \
		./$(REFERENCE_EXEC) -t $$testfile > $(OUTPUT_DIR)/$$base_name.ref; \
		if diff $(OUTPUT_DIR)/$$base_name.out $(OUTPUT_DIR)/$$base_name.ref > /dev/null; then \
			echo "🌟 PASSED $$testfile"; \
		else \
			echo "🚨 FAILED $$testfile"; \
			echo "Diff:"; \
			diff $(OUTPUT_DIR)/$$base_name.out $(OUTPUT_DIR)/$$base_name.ref; \
		fi; \
	done


# Clean target to remove compiled files
clean:
	rm -f $(EXEC) $(OBJ)

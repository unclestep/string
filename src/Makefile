CFLAGS = -Wall -Werror -Wextra -std=c11 -g
CC = gcc
LIBS = -lcheck
ifeq ($(shell uname), Linux)
	LIBS += -lm -lpthread -lsubunit -lr
endif 

BUILD_DIR = build
TARGET = s21_string
TARGET_LIB = $(TARGET).a

INC = $(TARGET).h 
STD = std
SPRINTF = sprintf
SSCANF =  sscanf
BONUS = bonus
TEST = test

SRCS = $(wildcard $(STD)/*.c) \
       $(wildcard $(SPRINTF)/*.c) \
       $(wildcard $(SSCANF)/*.c) \
       $(wildcard $(BONUS)/*.c)
OBJS = $(patsubst %.c, $(BUILD_DIR)/%.o, $(SRCS))

TEST_SRCS = $(wildcard $(TEST)/*/*.c) \
	    $(wildcard $(TEST)/*.c)
TEST_OBJS = $(patsubst %.c, $(BUILD_DIR)/%.o, $(TEST_SRCS))

all: $(TARGET_LIB)

$(TARGET_LIB): $(OBJS)
	ar rcs $@ $^

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TEST_OBJS)
	gcc $(CFLAGS) --coverage -o $(BUILD_DIR)/$(TEST)/$(TEST).out $(SRCS) $(TEST_OBJS) $(LIBS)
	./$(BUILD_DIR)/$(TEST)/$(TEST).out

gcov_report: $(TEST)
	lcov --capture --directory . --output-file $(BUILD_DIR)/$(TEST)/coverage.info
	genhtml $(BUILD_DIR)/$(TEST)/coverage.info --output-directory $(BUILD_DIR)/coverage

clean:
	rm -rf $(BUILD_DIR)

check-clang:
	find . -name *.c -o -name *.h | xargs clang-format -n -style=Google

clang:
	find . -name *.c -o -name *.h | xargs clang-format -i -style=Google

valgrind:
	valgrind --leak-check=full --tool=memcheck ./$(BUILD_DIR)/$(TEST)/test.out > $(BUILD_DIR)/$(TEST)/memory_report.txt 2>&1
	less $(BUILD_DIR)/$(TEST)/memory_report.txt
	
print-test-srcs:
	@echo $(TEST_SRCS)

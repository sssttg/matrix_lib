# Матричная библиотека на C — сборка
#   make            — собрать CLI build/matcalc (с санитайзерами)
#   make test       — собрать и запустить тесты (с санитайзерами)
#   make valgrind   — тесты под valgrind (без ASan: они не совместимы)
#   make clean      — удалить build/

CC      := gcc
CFLAGS  := -std=c11 -Wall -Wextra -Wpedantic -Wshadow -g -Iinclude
SAN     := -fsanitize=address,undefined -fno-omit-frame-pointer
LDLIBS  := -lm

LIB_SRC  := src/matrix.c
APP_SRC  := src/main.c
TEST_SRC := tests/test_matrix.c
HEADERS  := include/matrix.h

BUILD := build

.PHONY: all test valgrind clean

all: $(BUILD)/matcalc

$(BUILD)/matcalc: $(APP_SRC) $(LIB_SRC) $(HEADERS) | $(BUILD)
	$(CC) $(CFLAGS) $(SAN) $(APP_SRC) $(LIB_SRC) -o $@ $(LDLIBS)

$(BUILD)/test_matrix: $(TEST_SRC) $(LIB_SRC) $(HEADERS) | $(BUILD)
	$(CC) $(CFLAGS) $(SAN) $(TEST_SRC) $(LIB_SRC) -o $@ $(LDLIBS)

# Запуск из корня репозитория — пути вида tests/data/a.txt работают
test: $(BUILD)/test_matrix
	./$(BUILD)/test_matrix

valgrind: | $(BUILD)
	$(CC) $(CFLAGS) $(TEST_SRC) $(LIB_SRC) -o $(BUILD)/test_matrix_vg $(LDLIBS)
	valgrind --leak-check=full --error-exitcode=1 ./$(BUILD)/test_matrix_vg

$(BUILD):
	mkdir -p $(BUILD)

clean:
	rm -rf $(BUILD)

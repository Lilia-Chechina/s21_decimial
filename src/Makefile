# Флаги компиляции
FLAGS := -Wall -Werror -Wextra -std=c11
BUILD_DIR := ./build
LIBRARY := s21_decimal.a
TEST_EXEC := test_decimal
TEST_SOURCE := test_s21_decimal.c
UNAME_S := $(shell uname -s)

# Директории с исходниками
SRC_DIRS := arithmetic comparison additional converters other
FUNC_SOURCES := $(wildcard $(addsuffix /*.c, $(SRC_DIRS)))
FUNC_OBJECTS := $(patsubst %.c, $(BUILD_DIR)/%.o, $(FUNC_SOURCES))

# Определение ОС
ifeq ($(UNAME_S),Linux)
    OPEN_CMD = xdg-open
    CFLAGS = -lcheck -lsubunit -lm -lrt -lpthread -D_GNU_SOURCE
endif
ifeq ($(UNAME_S),Darwin)
    OPEN_CMD = open
    CFLAGS = -lcheck -lpthread -lm
endif

# ======= Основные цели =======

all: clean $(LIBRARY)

# Очистка
clean:
	rm -f $(LIBRARY)
	rm -rf $(BUILD_DIR)
	rm -f ./test.out
	rm -rf ./logs
	rm -rf *.gcov *.gcda *.gcno
	rm -f $(TEST_EXEC)

# Создание директории для сборки
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Компиляция объектных файлов
$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	mkdir -p $(dir $@)
	gcc $(FLAGS) -c $< -o $@

# Создание статической библиотеки
$(LIBRARY): $(FUNC_OBJECTS)
	ar rc $(LIBRARY) $^

# ======= Тестирование =======

test: $(LIBRARY)
	gcc $(FLAGS) -fprofile-arcs -ftest-coverage $(FUNC_SOURCES) $(TEST_SOURCE) $(CFLAGS) -o $(TEST_EXEC)
	./$(TEST_EXEC)

# ======= Генерация покрытия кода (gcov) =======

gcov_report: test
	mkdir -p logs
	gcovr --html-details -e "test_s21_decimal.c" -o logs/report.html
	$(OPEN_CMD) logs/report.html

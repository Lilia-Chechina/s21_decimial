
OUT_FILE = meow.out
FILES = *.c other/*.c additional/*.c comparison/*.c comparison/additional/*.c arithmetic/*.c arithmetic/additional/*.c

all:
	gcc $(FILES) -o $(OUT_FILE) -std=c11 -Wall -Werror -Wextra

no-flags:
	gcc $(FILES) -o $(OUT_FILE) -std=c11

clean:
	rm $(OUT_FILE)
CC = tester.c
all:
	gcc $(CC)
	./a.exe
	rm -f a.exe
CC = tester.c
all:
	gcc $(CC)
	./a.exe
	rm -f a.exe
gitify:
	git add .
	git commit -m "commit-V"
	git push -u origin main
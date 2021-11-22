
main : helloGTK.c
	gcc -g helloGTK.c -o t.out `pkg-config --cflags --libs gtk+-2.0`
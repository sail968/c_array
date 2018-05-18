run: tests c_array
	gcc main.c tests.o c_array.o -o run

tests: c_array
	gcc -c tests/tests.c -o tests.o

c_array:
	gcc -c src/array.c -o c_array.o

clean:
	rm tests.o c_array.o


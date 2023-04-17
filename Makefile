todoapp: todo.o command.o lib.o
	gcc todo.o command.o lib.o -o todoapp

todo.o: todo.c command.h lib.h
	gcc todo.c -c

command.o: command.c model.h lib.h
	gcc command.c -c

lib.o: lib.c lib.h model.h
	gcc lib.c -c

.PHONY: clean cmake

clean:
	rm -f *.o todoapp

todoapp: todo.o command.o lib.o
	gcc todo.o command.o lib.o -o todoapp -g

todo.o: todo.c command.h lib.h
	gcc todo.c -c -g

command.o: command.c model.h lib.h
	gcc command.c -c -g

lib.o: lib.c lib.h model.h
	gcc lib.c -c -g

.PHONY: clean

clean:
	rm -f *.o todoapp

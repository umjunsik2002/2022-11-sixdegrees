all: sixdegrees

sixdegrees: sixdegrees.o 1-tree.o 2-list.o 3-free.o 4-bfs.o
	gcc sixdegrees.o 1-tree.o 2-list.o 3-free.o 4-bfs.o -o sixdegrees
	rm -f sixdegrees.o 1-tree.o 2-list.o 3-free.o 4-bfs.o

sixdegrees.o: sixdegrees.c sixdegrees.h
	gcc -c sixdegrees.c -o sixdegrees.o

1-tree.o: 1-tree.c sixdegrees.h
	gcc -c 1-tree.c

2-list.o: 2-list.c sixdegrees.h
	gcc -c 2-list.c

3-free.o: 3-free.c sixdegrees.h
	gcc -c 3-free.c

4-bfs.o: 4-bfs.c sixdegrees.h
	gcc -c 4-bfs.c

clean:
	rm -f sixdegrees

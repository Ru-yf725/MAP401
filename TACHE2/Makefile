CC = clang -c

all: test_geom2d

test_geom2d.o: test_geom2d.c types.h
	$(CC) $<
geom2d.o: geom2d.c geom2d.h
	$(CC) $<

test_geom2d: geom2d.o test_geom2d.o
	clang $^ -o $@

clean:
	rm test_geom2d *.o

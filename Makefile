OBJS = ftgrays.c matrix.c render.c SDL_svg.c
TEST_OBJS = svgtest.cpp
CC = clang
CXX = clang++
LIBOBJ = libSDL_SVG.a
TESTOBJ = svgtest

INCLUDE = -I./ -I./libsvg
LDFLAGS = -L./ -lSDL_SVG -lSDL2 -L./libsvg -lsvg -L./libsvg/libxml2/.libs -lxml2

lib:
	$ $(CC) -c $(OBJS)
	ar cr $(LIBOBJ) *.o

test:
	$ $(CXX) $(TEST_OBJS) $(INCLUDE) $(LDFLAGS) -o $(TESTOBJ)

clean:
	rm -f *.o *.so *.a $(TESTOBJ) $(LIBOBJ)

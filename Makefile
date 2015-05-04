OBJS = ftgrays.c matrix.c render.c SDL_svg.c
TEST_OBJS = svgtest.cpp
CC = clang
CXX = clang++
LIBOBJ = libSDL_SVG.a
TESTOBJ = svgtest

INCLUDE = -I./
LDFLAGS = -lSDL2 -L./ -lsvg -lxml2 -lSDL_SVG

lib:
	$ $(CC) -c $(OBJS)
	ar cr $(LIBOBJ) *.o

test:
	$ $(CXX) $(TEST_OBJS) $(LDFLAGS) -o $(TESTOBJ)

clean:
	rm -f *.o *.so *.a $(TESTOBJ) $(LIBOBJ)

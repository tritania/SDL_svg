OBJS = svg.c \
	svg_ascii.c \
	svg_attribute.c \
	svg_color.c \
	svg_element.c \
	svg_gradient.c \
	svg_group.c \
	svg_length.c \
	svg_paint.c \
	svg_parser.c \
	svg_path.c \
	svg_pattern.c \
	svg_str.c \
	svg_style.c \
	svg_text.c \
	svg_transform.c
CC = gcc
CFLAGS = -O2 -Wall -fPIC -I/usr/include/libxml2
LIBOBJ = libsvg.a


lib:
	git clone git://git.gnome.org/libxml2
	cd libxml2 && sh autogen.sh --without-iconv --without-zlib --without-lzma --without-python --disable-shared && make
	$ $(CC) $(CFLAGS) -c $(OBJS)
	ar cr $(LIBOBJ) *.o
	rm *.o

clean:
	rm -f *.o *.so *.a $(LIBOBJ)

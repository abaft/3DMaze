#the flags you want to pass to the C compiler & linker
AM_CFLAGS = --pedantic -Wall -std=c11 -O3 -lSDL2 -lGL -lGLU
AM_LDFLAGS =
AUTOMAKE_OPTIONS = subdir-objects

# this lists the binaries to produce, the (non-PHONY, binary) targets in
# the previous manual Makefile
bin_PROGRAMS = 3DMaze
3DMaze_SOURCES = graphics.c map_gen/gen_utils.c map_gen/gen_utils.h map_gen/rbt.c\
map_gen/dun.c

# A simple Makefile for compiling small SDL projects

# set the compiler
CC := gcc

# set the compiler flags
CFLAGS := `sdl2-config --libs --cflags` -ggdb3 -O0 --std=c99 -Wall -lSDL2_image -lm

# add header files here
HDRS := c_trees/inc/c_trees.h c_trees/c_structures/inc/c_structures.h inc/search_algorithms.h

# define main file (used for clean function, in order to build, use make MAIN=<dir>/<file>.c)
MAIN := examples/dfs_example.c
# add source files here
SRCS := $(wildcard c_trees/src/*.c) $(wildcard c_trees/c_structures/src/*.c) src/render.c src/convert.c src/search.c $(MAIN) 

TEST_SRCS := $(filter-out $(MAIN),$(SRCS)) src/test.c

# generate names of object files
OBJS := $(SRCS:.c=.o)

TEST_OBJS := $(TEST_SRCS:.c=.o)

# name of executable
EXEC := main

# default recipe
all: $(EXEC)

# recipe for building the final executable
$(EXEC): $(OBJS) $(HDRS) Makefile
	$(CC) -o $@ $(OBJS) $(CFLAGS)

test: $(TEST_OBJS) $(HDRS) Makefile
	$(CC) -o $@ $(TEST_OBJS) $(CFLAGS)


# recipe for building object files
# $(OBJS): $(@:.o=.c) $(HDRS) Makefile
# 	$(CC) -o $@ $(@:.o=.c) -c $(CFLAGS)

# $(OBJDIR)/%.o: %.c
# 	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

# recipe to clean the workspace
clean:
	rm -f test $(EXEC) $(OBJS) $(TEST_OBJS)

.PHONY: all clean

# use "gcc" to compile source files.
CC = gcc
# the linker is also "gcc". It might be something else with other compilers.
LD = gcc
# Compiler flags go here.
CFLAGS = -g -Wall -Iinclude
# Linker flags go here. Currently there aren't any, but if we'll switch to
# code optimization, we might add "-s" here to strip debug info and symbols.
LDFLAGS =
# use this command to erase files.
RM = /bin/rm -f
# list of generated object files.
OBJS = main.o emulate.o
# program executable file name.
PROG = emulate_rcpu

$(PROG): $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $(PROG)

# now comes a meta-rule for compiling any "C" source file.
%.o: %.c
	$(CC) $(CFLAGS) -c $<

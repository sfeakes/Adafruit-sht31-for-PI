# define the C compiler to use
CC = gcc

# define any compile-time flags
CFLAGS = -Wall -g -O


# define the C source files
SRCS = main.c sht31-d.c

# define the C object files 
OBJS = $(SRCS:.c=.o)

# define the executable file 
MAIN = sht31-d



.PHONY: depend clean

all:    $(MAIN)
  @echo: $(MAIN) have been compiled

$(MAIN): $(OBJS) 
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	$(RM) *.o *~ $(MAIN)

depend: $(SRCS)
	makedepend $(INCLUDES) $^

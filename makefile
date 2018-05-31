FCC = gcc
LDC = gcc
LD_FLAGS= -fopenmp
FLAGS= -Wall -fopenmp
PROG = mandelbrot
RM = /bin/rm
OBJS = mandel.o

#all rule
all: $(PROG)

$(PROG): $(OBJS)
	$(LDC) $(LD_FLAGS) $(OBJS) -o $(PROG)

%.o: %.c
	$(FCC) $(FLAGS) -c $<

#clean rule
clean:
	$(RM) -rf *.o $(PROG) *.mod

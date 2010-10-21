UNAME := $(shell uname -s)

OBJS=jsbm.o timer.o engine.o format.o stats.o
TARG=jsbm

CFLAGS=-I. -Iv8/include -DXP_UNIX -m32
LFLAGS=-m32

ALL : $(TARG)

%.o : %.cc
	g++ -c -Wall -o $@ $(CFLAGS) $<

$(TARG) : $(OBJS)
ifeq ($(UNAME),Darwin)
	g++ -Wall -o $@ -framework CoreServices $(LFLAGS) $(OBJS) v8/libv8.a 
else
	g++ -Wall -o $@ -lpthread $(LFLAGS) $(OBJS) v8/libv8.a 
endif

clean:
	rm -f $(TARG) $(OBJS)


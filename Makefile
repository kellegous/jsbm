UNAME := $(shell uname -s)

OBJS=jsbm.o timer.o engine.o format.o stats.o
TARG=jsbm

CFLAGS=-I. -Iv8/include -DXP_UNIX -m32
ifeq ($(UNAME),Darwin)
LFLAGS=-framework CoreServices -m32
else
LFLAGS=-m32 -lrt -lpthread
endif

ALL : $(TARG)

%.o : %.cc
	g++ -c -Wall -o $@ $(CFLAGS) $<

$(TARG) : $(OBJS)
	g++ -Wall -o $@ $(LFLAGS) $(OBJS) v8/libv8.a 

clean:
	rm -f $(TARG) $(OBJS)


#CC=g++ -m32
CC=g++

LIB_NAME=libProto.a

SRCS=$(wildcard *.cc)

OBJS=$(SRCS:%.cc=%.o)

INCLUDES=

CFLAGS=-D __LINUX__  -Wno-deprecated -finline -fPIC

LIB_PATHS=

LIBS=

$(LIB_NAME):$(OBJS)
	ar r  $(LIB_NAME) $(OBJS)
	ctags -R
	$(RM) *.o

$(OBJS):%.o:%.cc
	@echo ; echo "$< ------------> $@"
	$(CC) $(CFLAGS) $(INCLUDES) -c $<
clean:
	$(RM) *.o *.a

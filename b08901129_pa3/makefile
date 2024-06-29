CC = g++
CFLAGS = -c
OPTFLAGS = -O3
ARFLAGS = rcv

all : bin/cb
	@echo -n "building project\n"

# optimized version
bin/cb : main_opt.o cycleBreaker_opt.o lib
			$(CC) $(OPTFLAGS) main_opt.o cycleBreaker_opt.o -ltm_usage -Llib -o bin/cb
main_opt.o : src/main.cpp lib/tm_usage.h
			$(CC) $(CFLAGS) $< -Ilib -o $@
cycleBreaker_opt.o : src/cycleBreaker.cpp src/cycleBreaker.h
			$(CC) $(CFLAGS) $(OPTFLAGS) $< -o $@ 

lib: lib/libtm_usage.a

lib/libtm_usage.a: tm_usage.o
	$(AR) $(ARFLAGS) $@ $<
tm_usage.o: lib/tm_usage.cpp lib/tm_usage.h
	$(CC) $(CFLAGS) $<

#clean all the .o and exexutable files
clean:
		rm -rf*.o lib/*.a lib/*.o bin/

# My Makefile

MAIN =

CPP_FILES = $(wildcard src/*.cpp)
OBJS = $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))

#OPTFLAG = -fexternal-templates
OPTFLAG = -O1 -march=core2
CPPFLAGS = -std=c++11 -I./include
LIBS =

all: main.exe

clean:
	rm $(OBJS) $(MAIN)

main.exe: $(OBJS) $(MAIN)
	g++ $(LIBS) $^

obj/%.o: src/%.cpp
	g++ $(OPTFLAG) $(CPPFLAGS) -c -o $@ $<

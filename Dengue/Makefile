#############################################################
# My Makefile
# for use when there is multiple main files in this directory
# Put the name of all the main cpp files in 'MAINS'
# each main can then be made by 'make <main>'
# DEFAULTMAIN gives the default in case of 'make'
#
# MAKE syntax
# -----------
#
# the syntax <targets>:%: <prerequisites>
#	<command>
# '%' matches the target name, % in prerequisites expands to
# target name and $@ in command expands to target name
#
# $(patsubst %,%.o,$(MAINS)) pattern-substitutes all
# occurences of wildcard % in MAINS with %.o
#
# (c) Daniel Tang 2008
#
#############################################################
#
#
#############################################################


DEFAULTMAIN = main
MAINS = main

OBJS = Agent.o ImmuneState.o Population.o PopulationDistribution.o
#OPTFLAG = -O3
CPPFLAGS = -std=c++11
# -L../include -I../include
#LIBS = -lphd

all: $(DEFAULTMAIN)

$(MAINS):%: $(OBJS) %.o
	g++ $(OPTFLAG) $(CPPFLAGS) $(OBJS) $@.o $(LIBS)

clean:
	rm $(OBJS) $(patsubst %,%.o,$(MAINS))

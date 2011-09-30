##
## This is a makefile for building this Pin tools outside
## of the Pin environment.  This makefile is suitable for
## building with the Pin kit, not a Pin source development tree.
##
## To build the tool, execute the make command:
##
##      make
## or
##      make PIN_HOME=<top-level directory where Pin was installed>
##
## After building your tool, you would invoke Pin like this:
## 
##      $PIN_HOME/pin -t MyPinTool -- /bin/ls
##
##############################################################
#
# User-specific configuration
#
##############################################################

#
# 1. Change PIN_HOME to point to the top-level directory where
#    Pin was installed. This can also be set on the command line,
#    or as an environment variable.
#
PIN_HOME ?= /home/tamsyn/local/pin-2.10-43611


##############################################################
#
# Set up and include *.config files
#
##############################################################

PIN_KIT=$(PIN_HOME)
KIT=1
TESTAPP=$(OBJDIR)cp-pin.exe

TARGET_COMPILER?=gnu
ifdef OS
    ifeq (${OS},Windows_NT)
        TARGET_COMPILER=ms
    endif
endif

ifeq ($(TARGET_COMPILER),gnu)
    include $(PIN_HOME)/source/tools/makefile.gnu.config
    CXXFLAGS ?= -Wall -Werror -Wno-unknown-pragmas $(DBG) $(OPT)
    PIN=$(PIN_HOME)/pin
endif

ifeq ($(TARGET_COMPILER),ms)
    include $(PIN_HOME)/source/tools/makefile.ms.config
    DBG?=
    PIN=$(PIN_HOME)/pin.bat
endif

CXXFLAGS+=-ggdb

##############################################################
#
# Tools - you may wish to add your tool name to TOOL_ROOTS
#
##############################################################


TOOL_ROOTS = MemCheck

TOOLS = $(TOOL_ROOTS:%=$(OBJDIR)%$(PINTOOL_SUFFIX))


##############################################################
#
# Build rules
#
##############################################################

all: tools example
tools: $(OBJDIR) mem_libc.o $(TOOLS) $(OBJDIR)cp-pin.exe
test: $(OBJDIR) $(TOOL_ROOTS:%=%.test)

MemCheck.test: $(OBJDIR)cp-pin.exe
	$(MAKE) -k -C MemCheck PIN_HOME=$(PIN_HOME)

$(OBJDIR)cp-pin.exe:
	$(CXX) $(PIN_HOME)/source/tools/Tests/cp-pin.cpp $(APP_CXXFLAGS) -o $(OBJDIR)cp-pin.exe

$(OBJDIR):
	mkdir -p $(OBJDIR)

mem_libc.o: mem_libc.cpp
	$(CXX) -c $(CXXFLAGS) $(PIN_CXXFLAGS) mem_libc.cpp

mem_posix.o: mem_posix.cpp
	$(CXX) -c $(CXXFLAGS) $(PIN_CXXFLAGS) mem_posix.cpp

shadow.o: shadow.cpp
	$(CXX) -c $(CXXFLAGS) $(PIN_CXXFLAGS) shadow.cpp

$(OBJDIR)%.o : %.cpp
	$(CXX) -c $(CXXFLAGS) $(PIN_CXXFLAGS) ${OUTOPT}$@ $<

$(TOOLS): $(PIN_LIBNAMES)

$(TOOLS): %$(PINTOOL_SUFFIX) : %.o mem_libc.o shadow.o mem_posix.o
	${PIN_LD} $(PIN_LDFLAGS) $(LINK_DEBUG) ${LINK_OUT}$@ $< mem_libc.o shadow.o mem_posix.o ${PIN_LPATHS} $(PIN_LIBS) $(DBG)

example: test.c valid_test.c
	gcc -O0 -o test test.c
	gcc -O0 -o valid_test valid_test.c
	gcc -m32 -O0 -o test_32 test.c
	gcc -m32 -O0 -o valid_test_32 valid_test.c

## cleaning
clean:
	-rm -rf $(OBJDIR) *.out *.tested *.failed makefile.copy mem_libc.o shadow.o

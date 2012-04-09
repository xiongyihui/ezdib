
default_target: all

#-------------------------------------------------------------------
# Input
#-------------------------------------------------------------------

#PR := i586-mingw32msvc-

# Output file
OUTFILE := test_ezdib

# Input files
CCFILES := $(wildcard *.c)
PPFILES := $(wildcard *.cpp)

# Intermediate files
TMPPATH := tmp

# Object files
DEPENDS := $(foreach f,$(CCFILES),$(TMPPATH)/c/$(f:.c=.obj)) \
		   $(foreach f,$(PPFILES),$(TMPPATH)/cpp/$(f:.cpp=.obj))

#-------------------------------------------------------------------
# Tools
#-------------------------------------------------------------------

# Paths tools
RM := rm -f
MD := mkdir -p

# GCC
PP := $(PR)g++ -c
CC := $(PR)gcc -c
LD := $(PR)g++
AR := $(PR)ar -cr
RC := $(PR)windres

# 'c++' Flags
PP_FLAGS := -shared -fPIC

# 'c' Flags
CC_FLAGS := -shared -fPIC

# Linker flags
LD_FLAGS := -fPIC

# -mwindows

#-------------------------------------------------------------------
# Build
#-------------------------------------------------------------------

# Create 'c++' object file path
$(TMPPATH)/cpp :
	- $(MD) $@

# Create 'c' object file path
$(TMPPATH)/c :
	- $(MD) $@

# How to build a 'c++' file
$(TMPPATH)/cpp/%.obj : %.cpp $(TMPPATH)/cpp
	$(PP) $< $(PP_FLAGS) -o $@

# How to build a 'c' file
$(TMPPATH)/c/%.obj : %.c $(TMPPATH)/c
	$(CC) $< $(CC_FLAGS) -o $@

# Build the output
$(OUTFILE) : $(DEPENDS)
	- $(RM) $@
	$(LD) $(LD_FLAGS) $(DEPENDS) -o "$@"

# Default target
all : $(OUTFILE)

clean :
	- $(RM) -R $(TMPPATH)

rebuild : clean all


default_target: all
_END_ := 1

#-------------------------------------------------------------------
# Configure
#-------------------------------------------------------------------

ifneq ($(findstring debug,$(TGT)),)
	CFG_DBG := 1
endif
		   
ifneq ($(findstring windows,$(TGT)),)
	CFG_WIN := 1
	CFG_SYSTEM := windows
else
	CFG_SYSTEM := posix
endif

ifneq ($(findstring static,$(TGT)),)
	CFG_STATIC := 1
endif

ifdef CFG_WIN
	PR := i586-mingw32msvc-
endif

#-------------------------------------------------------------------
# Input / Output
#-------------------------------------------------------------------

BINPATH := ../bin/$(CFG_SYSTEM)
OUTNAME := test_ezdib

ifdef CFG_DBG
	BINPATH := $(BINPATH)-debug
endif

# Output file
ifdef CFG_WIN
	OUTFILE := $(BINPATH)/$(OUTNAME).exe
else
	OUTFILE := $(BINPATH)/$(OUTNAME)
endif

# Input files
CCFILES := $(wildcard *.c)
PPFILES := $(wildcard *.cpp)


# Object files
DEPENDS := $(foreach f,$(CCFILES),$(BINPATH)/c/$(f:.c=.obj)) \
		   $(foreach f,$(PPFILES),$(BINPATH)/cpp/$(f:.cpp=.obj))

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

PP_FLAGS :=
CC_FLAGS :=

ifdef CFG_STATIC
	PP_FLAGS := $(PP_FLAGS) -shared
	CC_FLAGS := $(CC_FLAGS) -shared
else
	PP_FLAGS := $(PP_FLAGS) -shared
	CC_FLAGS := $(CC_FLAGS) -shared
endif

ifndef CFG_WIN
	PP_FLAGS := $(PP_FLAGS) -fPIC
	CC_FLAGS := $(CC_FLAGS) -fPIC
	LD_FLAGS := $(LD_FLAGS) -fPIC
endif

ifdef CFG_DBG
	PP_FLAGS := $(PP_FLAGS) -g -DDEBUG -D_DEBUG
	CC_FLAGS := $(CC_FLAGS) -g -DDEBUG -D_DEBUG
	LD_FLAGS := $(LD_FLAGS) -g
else
	PP_FLAGS := $(PP_FLAGS) -O2
	CC_FLAGS := $(CC_FLAGS) -O2
endif


#-------------------------------------------------------------------
# Build
#-------------------------------------------------------------------

# Create 'c++' object file path
$(BINPATH)/cpp :
	- $(MD) $@

# Create 'c' object file path
$(BINPATH)/c :
	- $(MD) $@

# How to build a 'c++' file
$(BINPATH)/cpp/%.obj : %.cpp $(BINPATH)/cpp
	$(PP) $< $(PP_FLAGS) -o $@

# How to build a 'c' file
$(BINPATH)/c/%.obj : %.c $(BINPATH)/c
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

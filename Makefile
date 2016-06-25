
#---------------------------
# Compiler options

CC	:= g++
CFLAGS  := -std=c++11


#---------------------------
# Environment configuration

SRCDIR := src
BUILDDIR := build
BINDIR := bin
LIBDIR := lib
STRUCTUREDIR := structures
TINDEX_SRCDIR := $(SRCDIR)/tindex
TINDEX_BUILDDIR := $(BUILDDIR)/tindex
#SRCDIRUTILS = utils
#SRCDIRLIBCDS = ./src/libcds

SRCEXT := cpp

#SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
#OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
TINDEX_SOURCES := $(shell find $(TINDEX_SRCDIR) -type f -name *.$(SRCEXT))
TINDEX_OBJECTS := $(patsubst $(TINDEX_SRCDIR)/%,$(TINDEX_BUILDDIR)/%,$(TINDEX_SOURCES:.$(SRCEXT)=.o))
TINDEX_LIB := $(LIBDIR)/tindex.a

EXECUTABLES := codeToInt createIndex useIndex

#CFLAGS := -g # -Wall
#LIB := -pthread -lmongoclient -L lib -lboost_thread-mt -lboost_filesystem-mt -lboost_system-mt
LIB := -L $(LIBDIR)
INC := -I include

#---------------------------

all: clean allTIndex $(EXECUTABLES)

#---------------------------
# TIndex library creation
allTIndex: tindex
	@echo " Creating static library $(TINDEX_LIB)"
	@echo " ar rcvs $(TINDEX_LIB)  $(TINDEX_OBJECTS)" ; ar rcvs $(TINDEX_LIB)  $(TINDEX_OBJECTS)

# dependencies

tlistreader: $(TINDEX_BUILDDIR)/tlistreader.o
tlist: tlistreader $(TINDEX_BUILDDIR)/tlist.o
tindex: tlist $(TINDEX_BUILDDIR)/tindex.o

$(TINDEX_BUILDDIR)/%.o: $(TINDEX_SRCDIR)/%.$(SRCEXT)
	@echo "COMPILING 2: $@ $<"
	@mkdir -p $(TINDEX_BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

#-----------------------------
# Executables

codeToInt: $(BINDIR)/codeToInt
createIndex: allTIndex $(BINDIR)/createIndex
useIndex: allTIndex $(BINDIR)/useIndex

$(BINDIR)/%: $(SRCDIR)/%.$(SRCEXT)
	@echo "COMPILING 3: $@ $<"
	@mkdir -p $(BINDIR)
	@echo " $(CC) $(CFLAGS) $(INC) $(LIB) -o $@ $<"; $(CC) $(CFLAGS) $(INC) $(LIB) -o $@ $< $(TINDEX_LIB)

#-----------------------------

clean:
	@echo " Cleaning..."; 
	@echo " $(RM) -r $(BUILDDIR) $(BINDIR)"; $(RM) -r $(BUILDDIR) $(BINDIR)
	@echo " DONE"

cleanIndex:
	@echo " Cleaning indexes..."; 
	@echo " $(RM) -r $(STRUCTUREDIR)"; $(RM) -r $(STRUCTUREDIR)
	@echo " DONE"

cleanAll:
	@echo " Cleaning binaries, objects and indexes..."; 
	@echo " $(RM) -r $(BUILDDIR) $(BINDIR) $(STRUCTUREDIR)"; $(RM) -r $(BUILDDIR) $(BINDIR) $(STRUCTUREDIR)
	@echo " DONE"

.PHONY: clean
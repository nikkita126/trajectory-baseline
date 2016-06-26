
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

EXECUTABLES := codeToInt createIndex queryIndex

#CFLAGS := -g # -Wall
#LIB := -pthread -lmongoclient -L lib -lboost_thread-mt -lboost_filesystem-mt -lboost_system-mt
LIB := -L $(LIBDIR)
INC := -I include

#---------------------------

all: clean allTIndex $(EXECUTABLES)

#---------------------------
# TIndex library creation
allTIndex: tindex
	@mkdir -p $(LIBDIR)
	@echo "Creating static library $(TINDEX_LIB)"
	@echo "\t\t ar rcvs $(TINDEX_LIB)  $(TINDEX_OBJECTS)"; ar rcvs $(TINDEX_LIB)  $(TINDEX_OBJECTS)
	@echo " DONE"
	@echo ""

# dependencies

tlistreader: $(TINDEX_BUILDDIR)/tlistreader.o
tlist: tlistreader $(TINDEX_BUILDDIR)/tlist.o
tindex: tlist $(TINDEX_BUILDDIR)/tindex.o

$(TINDEX_BUILDDIR)/%.o: $(TINDEX_SRCDIR)/%.$(SRCEXT)
	@echo "COMPILING: $@ $<"
	@mkdir -p $(TINDEX_BUILDDIR)
	@echo "\t\t $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<
	@echo " DONE"
	@echo ""

#-----------------------------
# Executables

codeToInt: $(BINDIR)/codeToInt
createIndex: allTIndex $(BINDIR)/createIndex
queryIndex: allTIndex $(BINDIR)/queryIndex

$(BINDIR)/%: $(SRCDIR)/%.$(SRCEXT)
	@echo "COMPILING: $@ $<"
	@mkdir -p $(BINDIR)
	@echo "\t\t $(CC) $(CFLAGS) $(INC) $(LIB) -o $@ $< $(TINDEX_LIB)"; $(CC) $(CFLAGS) $(INC) $(LIB) -o $@ $< $(TINDEX_LIB)
	@echo " DONE"
	@echo ""


#-----------------------------

clean:

	@echo " Cleaning..."; 
	@echo "\t\t $(RM) -r $(BUILDDIR) $(BINDIR)"; $(RM) -r $(BUILDDIR) $(BINDIR)
	@echo " DONE"
	@echo ""

cleanIndex:
	@echo " Cleaning indexes..."; 
	@echo "\t\t $(RM) -r $(STRUCTUREDIR)"; $(RM) -r $(STRUCTUREDIR)
	@echo " DONE"
	@echo ""

cleanAll:
	@echo " Cleaning binaries, objects and indexes..."; 
	@echo "\t\t $(RM) -r $(BUILDDIR) $(BINDIR) $(STRUCTUREDIR)"; $(RM) -r $(BUILDDIR) $(BINDIR) $(STRUCTUREDIR)
	@echo " DONE"
	@echo ""

.PHONY: clean
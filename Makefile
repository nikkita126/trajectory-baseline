
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

UTILITIES_LIB_LIST	:= $(LIBDIR)/stop_encoding.a $(LIBDIR)/distance_graph.a

EXECUTABLES := codeToInt createIndex queryIndex encode_distances calc_reachability
LIBRARIES 	:= stop_encoding distance_graph
#CFLAGS := -g # -Wall
#LIB := -pthread -lmongoclient -L lib -lboost_thread-mt -lboost_filesystem-mt -lboost_system-mt
LIB := -L $(LIBDIR)
INC := -I include

#---------------------------

all: clean allTIndex $(LIBRARIES) $(EXECUTABLES)

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

#---------------------------
# Other Libraries

stop_encoding: $(LIBDIR)/stop_encoding.a

distance_graph: $(LIBDIR)/distance_graph.a

$(LIBDIR)/%.a: $(BUILDDIR)/%.o
	@echo "Creating static library $@"
	@echo "\t\t ar rcvs $@  %<"; ar rcvs $@  $<
	@echo " DONE"
	@echo ""

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@echo "COMPILING: $@ $<"
	@mkdir -p $(BUILDDIR)
	@echo "\t\t $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<
	@echo " DONE"
	@echo ""
	

#-----------------------------
# Executables

codeToInt: stop_encoding $(BINDIR)/codeToInt
createIndex: allTIndex $(BINDIR)/createIndex
queryIndex: allTIndex $(BINDIR)/queryIndex
encode_distances: stop_encoding $(BINDIR)/encode_distances
calc_reachability: distance_graph $(BINDIR)/calc_reachability

$(BINDIR)/%: $(SRCDIR)/%.$(SRCEXT)
	@echo "COMPILING: $@ $<"
	@mkdir -p $(BINDIR)
	@echo "\t\t $(CC) $(CFLAGS) $(INC) $(LIB) -o $@ $< $(UTILITIES_LIB_LIST) $(TINDEX_LIB)"; $(CC) $(CFLAGS) $(INC) $(LIB) -o $@ $< $(UTILITIES_LIB_LIST) $(TINDEX_LIB)
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
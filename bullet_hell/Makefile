CC:=g++
CFLAGS=-Wall -std=c++11
DEBUGF:=-g
RELEASEF:=-O2

LIBS:=-lsfml-graphics -lsfml-window -lsfml-system
CEXT:=cpp
HEXT:=hpp

INCDIR:=include
SRCDIR:=src
OBJDIR:=obj
BINDIR:=bin
DEPDIR:=deps

EXECSRC:=execsrc
TESTSRC:=testsrc
TESTBIN:=testbin

DEBUG_POST:=-d
RELEASE_POST:=

# Auto dependency, executable sources and tests sources finder

OBJS:=$(patsubst $(SRCDIR)/%.$(CEXT), $(OBJDIR)/%.o, $(wildcard $(SRCDIR)/*.$(CEXT)))
TESTS:=$(patsubst $(TESTSRC)/%.$(CEXT), $(TESTBIN)/%, $(wildcard $(TESTSRC)/*.$(CEXT)))
EXECS:=$(patsubst $(EXECSRC)/%.$(CEXT), $(BINDIR)/%, $(wildcard $(EXECSRC)/*.$(CEXT)))

SRCS:=$(wildcard $(SRCDIR)/*.$(CEXT))
SRCS+=$(wildcard $(TESTSRC)/*.$(CEXT))
SRCS+=$(wildcard $(EXECSRC)/*.$(CEXT))

# Don't erase dependency and object files

.PRECIOUS: $(OBJDIR)/%$(RELEASE_POST).o
.PRECIOUS: $(OBJDIR)/%$(DEBUG_POST).o

.PRECIOUS: $(DEPDIR)/%$(RELEASE_POST).d
.PRECIOUS: $(DEPDIR)/%$(DEBUG_POST).d

# Make rules

release: CFLAGS+=$(RELEASEF)
release: dependencies
release: execs$(RELEASE_POST)
release: tests$(RELEASE_POST)

debug: CFLAGS+=$(DEBUGF)
debug: dependencies
debug: execs$(DEBUG_POST)
debug: tests$(DEBUG_POST)

# Make executables

execs$(RELEASE_POST): $(patsubst %, %$(RELEASE_POST), $(EXECS))
execs$(DEBUG_POST): $(patsubst %, %$(DEBUG_POST), $(EXECS))

$(BINDIR)/%$(RELEASE_POST): $(OBJDIR)/%$(RELEASE_POST).o $(patsubst %, %$(RELEASE_POST), $(OBJS))
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

$(BINDIR)/%$(DEBUG_POST): $(OBJDIR)/%$(DEBUG_POST).o $(patsubst %, %$(RELEASE_POST), $(OBJS))
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

# Make tests

tests$(RELEASE_POST): $(patsubst %, %$(RELEASE_POST), $(TESTS))
tests$(DEBUG_POST): $(patsubst %, %$(DEBUG_POST), $(TESTS))

$(TESTBIN)/%$(RELEASE_POST): $(OBJDIR)/%$(RELEASE_POST).o $(patsubst %, %$(RELEASE_POST), $(OBJS))
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

$(TESTBIN)/%$(DEBUG_POST): $(OBJDIR)/%$(DEBUG_POST).o $(patsubst %, %$(RELEASE_POST), $(OBJS))
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

# Make dependencies

dependencies: $(DEPS)

# General rules

# For release

$(OBJDIR)/%$(RELEASE_POST).o: $(SRCDIR)/%.$(CEXT) $(INCDIR)/%.$(HEXT)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INCDIR)

$(OBJDIR)/%$(RELEASE_POST).o: $(SRCDIR)/%.$(CEXT)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INCDIR)

$(OBJDIR)/%$(RELEASE_POST).o: $(TESTSRC)/%.$(CEXT)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INCDIR)

$(OBJDIR)/%$(RELEASE_POST).o: $(EXECSRC)/%.$(CEXT)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INCDIR)

# For debug

$(OBJDIR)/%$(DEBUG_POST).o: $(SRCDIR)/%.$(CEXT) $(INCDIR)/%.$(HEXT)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INCDIR)

$(OBJDIR)/%$(DEBUG_POST).o: $(SRCDIR)/%.$(CEXT)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INCDIR)

$(OBJDIR)/%$(DEBUG_POST).o: $(TESTSRC)/%.$(CEXT)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INCDIR)

$(OBJDIR)/%$(DEBUG_POST).o: $(EXECSRC)/%.$(CEXT)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INCDIR)

# For dependencies

$(DEPDIR)/%.d: $(SRCDIR)/%.$(CEXT)
	$(CC) $(CFLAGS) $< -MM -MT $(OBJDIR)/$(patsubst $(DEPDIR)/%.d,%,$@).o -o $@ -I$(INCDIR)

$(DEPDIR)/%.d: $(TESTSRC)/%.$(CEXT)
	$(CC) $(CFLAGS) $< -MM -MT $(OBJDIR)/$(patsubst $(DEPDIR)/%.d,%,$@).o -o $@ -I$(INCDIR)

$(DEPDIR)/%.d: $(EXECSRC)/%.$(CEXT)
	$(CC) $(CFLAGS) $< -MM -MT $(OBJDIR)/$(patsubst $(DEPDIR)/%.d,%,$@).o -o $@ -I$(INCDIR)

# Including dependencies

# Upload to git

upload: clean
	git add --all
	git commit
	git push

# Clean binaries

clean:
	rm -rf $(OBJDIR)/*.o
	rm -rf $(BINDIR)/*
	rm -rf $(TESTBIN)/*

# Configure folder structure

configure: clang
	mkdir -p $(INCDIR)
	mkdir -p $(SRCDIR)
	mkdir -p $(OBJDIR)
	mkdir -p $(BINDIR)
	mkdir -p $(DEPDIR)
	mkdir -p $(EXECSRC)
	mkdir -p $(TESTSRC)
	mkdir -p $(TESTBIN)

# Make clang_complete file
clang:
	echo "-I$(INCDIR)" > .clang_complete

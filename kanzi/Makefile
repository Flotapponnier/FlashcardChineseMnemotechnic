# Variables
CC = gcc
CFLAGS = -Iincludes -Wall -Wextra -Werror
SRCDIR = src
INCLUDEDIR = includes
OBJDIR = obj
BINDIR = bin
TARGET = $(BINDIR)/kanzi

# Source and Object files
SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Rules
all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJDIR)

cleanall: clean
	rm -rf $(BINDIR)

# Phony targets
.PHONY: all clean cleanall

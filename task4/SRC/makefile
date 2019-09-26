OBJ= curve.o main.o
TARGET=program
BUILDDIR = ./BUILD
SRCDIR = ./SRC
INCLUDEDIR = ./INCLUDES
OBJDIR= $(patsubst %,$(BUILDDIR)/%,$(OBJ) )

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	gcc -c -o -I $(INCLUDEDIR) $@ $<

$(TARGET): $(BUILDDIR)/%.o
	gcc -o $@ $^

#This is a comment

#main.o: main.c
#	gcc -c -o main.o main.c

#statistics.o: statistics.c
#	gcc -c -o statistics.o stastics.c


#program: main.o statistics.o
#	gcc -o program main.o stastics.o

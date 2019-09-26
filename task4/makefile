OBJ= curve.o main.o stats.o
TARGET=program
#BUILDDIR = ./BUILD
#SRCDIR = ./SRC
#INCLUDEDIR = ./INCLUDES
#OBJDIR= $(patsubst %,$(BUILDDIR)/%,$(OBJ) )

%.o: %.c
	gcc -c -o $@ $<

$(TARGET): $(OBJ)
	gcc -o $@ $^

#This is a comment

#main.o: main.c
#	gcc -c -o main.o main.c

#statistics.o: statistics.c
#	gcc -c -o statistics.o stastics.c


#program: main.o statistics.o
#	gcc -o program main.o stastics.o

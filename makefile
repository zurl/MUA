OUTDIR = ./output
SOURCEDIR = ./MUA
CC     = gcc
LINK   = gcc -o
CFLAG  = -c -O2 -std=c99 -Wall -o
OBJECTS=  $(OUTDIR)/Main.o $(OUTDIR)/Arithmetic.o $(OUTDIR)/Function.o $(OUTDIR)/HashMap.o $(OUTDIR)/Input.o $(OUTDIR)/Value.o $(OUTDIR)/Symbol.o $(OUTDIR)/Runtime.o

all : $(OUTDIR) mua

$(OUTDIR) :
            mkdir $@

mua : $(OBJECTS)
            $(LINK) $@ -lm $(OBJECTS)

$(OUTDIR)/%.o : $(SOURCEDIR)/%.c
            $(CC) $(CFLAG) $@ $<

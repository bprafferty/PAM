##################################################################
#                   -- Program Assignment #2 -- 
#          Brian Rafferty -- cssc0852 -- redID: 816988452
#						CS 570, Summer 2019
#							 makefile
##################################################################
COMPILER=g++
FLAGS=-c -Wall

SRCFILE=pam.cpp
OBJFILE=$(SRCFILE:.cpp=.o)
EXE=pam

all: $(SRCFILE) $(EXE)
	
$(EXE): $(OBJFILE)
	$(COMPILER) $(OBJFILE) -o $@

.cpp.o:
	$(COMPILER) $(FLAGS) $< -o $@

clean:
	rm *.o $(OBJFILE)

#######################[ EOF: makefile ]##########################
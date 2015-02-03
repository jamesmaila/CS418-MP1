# Object files
OBJS = mp1.o

# EXE name 
EXENAME = mp1

# Macro assignments
CC = g++
CCOPTS = -c -g -O0 -Wall 
LINK = g++
LINKOPTS = -o

all : $(EXENAME)

# The main compiling step
$(EXENAME) : $(OBJS)
	$(LINK) $(LINKOPTS) $(EXENAME) $(OBJS) -lGL -lGLU -lglut 

# Compiles object files
mp1.o : mp1.cpp 
	$(CC) $(CCOPTS) mp1.cpp
	
# Clean
clean : 
	rm -f *.o $(EXENAME) 2>/dev/null

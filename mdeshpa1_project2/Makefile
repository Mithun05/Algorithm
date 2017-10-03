
#specify the compiler options or flags, linking libraries
# and any debugging information flags as a variables
CC = gcc
VV = c99
LL = lm

# Specify the target
all: target


# Specify how the executables should be created from source files
target: 
	$(CC) strassen.c -std=$(VV) -o strassen.out -$(LL)
	$(CC) tromino.c  -std=$(VV) -o tromino.out  -$(LL)

# Specify the object files and executables that are generated
# and need to be removed to re-compile the whole thing
clean:
	rm -f strassen.out
	rm -f tromino.out

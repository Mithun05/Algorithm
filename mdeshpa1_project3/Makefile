

# Specify the compiler options or flags, linking libraries
# and any debugging information flags as a variables
CC = gcc

#
# Specify the target
all: project3


# Specify how the executables should be created from source files
project3: 
	$(CC) -std=c99 Q2_dijikstra.c -o Q2_dijikstra
	$(CC) -std=c99 Q1-1_brute_force_knapsack.c -o Q1-1_brute_force_knapsack -lm
	$(CC) -std=c99 -g Q1-3_dynamic_programming_knapsack.c -o Q1-3_dynamic_programming_knapsack -lm
	$(CC) -std=c99 Q1-2_greedy_algorithm.c -o Q1-2_greedy_algorithm -lm

# Specify the object files and executables that are generated
# and need to be removed to re-compile the whole thing
clean:
	rm -f Q2_dijikstra Q1-1_brute_force_knapsack Q1-3_dynamic_programming_knapsack Q1-2_greedy_algorithm





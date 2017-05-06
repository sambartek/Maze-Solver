CFLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror
COVFLAGS = -fprofile-arcs -ftest-coverage
#PROFFLAG = -pg
GCC = gcc $(CFLAGS) $(COVFLAGS) #$(PROFFLAG)
OBJS = pa10.o maze.o path.o solver.o list.o mazehelper.o

pa10: $(OBJS) path.h maze.h solver.h list.h mazehelper.h
	$(GCC) $(OBJS) -o pa10

pa10.o: pa10.c path.h maze.h solver.h list.h mazehelper.h
	$(GCC) -c pa10.c -o pa10.o

path.o: path.c path.h maze.h solver.h list.h mazehelper.h
	$(GCC) -c path.c -o path.o

maze.o: maze.c path.h maze.h solver.h list.h mazehelper.h
	$(GCC) -c  maze.c -o maze.o

solver.o: solver.c path.h maze.h solver.h list.h mazehelper.h
	$(GCC) -c solver.c -o solver.o

list.o: list.c path.h maze.h solver.h list.h mazehelper.h
	$(GCC) -c list.c -o list.o

mazehelper.o: mazehelper.c path.h maze.h solver.h list.h mazehelper.h
	$(GCC) -c mazehelper.c -o mazehelper.o

tester2: test2.o
	$(GCC) test2.o -o tester2

test2.o: test2.c
	$(GCC) -c test2.c -o test2.o

tester3: path.h maze.h solver.h list.h mazehelper.h test3.o list.o mazehelper.o path.o
	$(GCC) list.o mazehelper.o path.o test3.o -o tester3

test3.o: test3.c
	$(GCC) -c test3.c -o test3.o

# "make test" will run the three input files
test: pa10
	./pa10 inputs/maze1 output1
	./pa10 inputs/maze2 output2
	./pa10 inputs/maze3 output3
	./pa10 inputs/maze4 output4

spec: pa10
	./pa10 inputs/maze4 output4

test2: tester2
	./tester2

test3: tester3
	./tester3
# "make memory" calls valgrind to check memory errors
memory: pa10
	valgrind --leak-check=full --show-reachable=yes -v ./pa10 inputs/maze1 output1
	valgrind --leak-check=full --show-reachable=yes -v ./pa10 inputs/maze2 output2
	valgrind --leak-check=full --show-reachable=yes -v ./pa10 inputs/maze3 output3
  valgrind --leak-check=full --show-reachable=yes -v ./pa10 inputs/maze4 output4
clean:
	/bin/rm -f *.o
	/bin/rm -f testgen
	/bin/rm -f *.gcda *.gcno gmon.out *gcov
	/bin/rm -f *.out
	/bin/rm -f output1 output2 output3 tester3

CC = g++
FLAGS = -std=c++17 -O3
CFLAGS = -I ./src -c
LFLAGS = -I ./build

build/basics/utility.o: src/basics/utility.cpp
	$(CC) $(FLAGS) $(CFLAGS) -o build/basics/utility.o src/basics/utility.cpp
	
build/model/expression.o: src/model/expression.cpp
	$(CC) $(FLAGS) $(CFLAGS) -o build/model/expression.o src/model/expression.cpp
	
build/model/op_impl.o: src/model/op_impl.cpp
	$(CC) $(FLAGS) $(CFLAGS) -o build/model/op_impl.o src/model/op_impl.cpp
	
build/model/constraint.o: src/model/constraint.cpp
	$(CC) $(FLAGS) $(CFLAGS) -o build/model/constraint.o src/model/constraint.cpp
	
build/model/numeric_constraint.o: src/model/numeric_constraint.cpp
	$(CC) $(FLAGS) $(CFLAGS) -o build/model/numeric_constraint.o src/model/numeric_constraint.cpp
	
build/model/combinatoric_constraint.o: src/model/combinatoric_constraint.cpp
	$(CC) $(FLAGS) $(CFLAGS) -o build/model/combinatoric_constraint.o src/model/combinatoric_constraint.cpp
	
build/algorithm/solver.o: src/algorithm/solver.cpp
	$(CC) $(FLAGS) $(CFLAGS) -o build/algorithm/solver.o src/algorithm/solver.cpp
	
build/algorithm/simple_hill_climbing.o: src/algorithm/simple_hill_climbing.cpp
	$(CC) $(FLAGS) $(CFLAGS) -o build/algorithm/simple_hill_climbing.o src/algorithm/simple_hill_climbing.cpp

build/capi/model.o: src/capi/model.cpp
	$(CC) $(FLAGS) $(CFLAGS) -o build/capi/model.o src/capi/model.cpp
	
build/capi/algorithm.o: src/capi/algorithm.cpp
	$(CC) $(FLAGS) $(CFLAGS) -o build/capi/algorithm.o src/capi/algorithm.cpp

build/test/main.o: src/test/main.cpp
	$(CC) $(FLAGS) $(CFLAGS) -o build/test/main.o src/test/main.cpp
	
build/test/cmain.o: src/test/cmain.c
	$(CC) $(FLAGS) $(CFLAGS) -o build/test/cmain.o src/test/cmain.c	

test: build/test/cmain.o build/basics/utility.o build/model/expression.o build/model/op_impl.o build/model/constraint.o build/model/numeric_constraint.o build/model/combinatoric_constraint.o build/algorithm/solver.o build/algorithm/simple_hill_climbing.o build/capi/model.o build/capi/algorithm.o
	$(CC) $(FLAGS) $(LFLAGS) -o build/testmain build/test/cmain.o build/basics/utility.o build/model/expression.o build/model/op_impl.o build/model/constraint.o build/model/numeric_constraint.o build/model/combinatoric_constraint.o build/algorithm/solver.o build/algorithm/simple_hill_climbing.o build/capi/model.o build/capi/algorithm.o

clean:
	rm -f build/*/*
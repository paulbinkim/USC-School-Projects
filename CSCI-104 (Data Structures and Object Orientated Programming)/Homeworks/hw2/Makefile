CXX = g++ -std=c++17

all: interpreter

interpreter: interpreter.cpp LetStatement.o EndStatement.o GosubStatement.o GotoStatement.o If.o MathOperators.o PrintAllstatement.o PrintStatement.o ProgramState.o Return.o
	$(CXX) -g -Wall $^ -o $@

ProgramState.o: ProgramState.cpp ProgramState.h
	g++ -g -c $< -o $@

LetStatement.o: LetStatement.cpp LetStatement.h ProgramState.h
	g++ -g -c $< -o $@

EndStatement.o: EndStatement.cpp EndStatement.h ProgramState.h
	g++ -g -c $< -o $@

GosubStatement.o: GosubStatement.cpp GosubStatement.h ProgramState.h
	g++ -g -c $< -o $@

GotoStatement.o: GotoStatement.cpp GotoStatement.h ProgramState.h
	g++ -g -c $< -o $@

If.o: If.cpp If.h ProgramState.h
	g++ -g -c $< -o $@

MathOperators.o: MathOperators.cpp MathOperators.h ProgramState.h
	g++ -g -c $< -o $@

PrintAllstatement.o: PrintAllstatement.cpp PrintAllstatement.h ProgramState.h
	g++ -g -c $< -o $@

PrintStatement.o: PrintStatement.cpp PrintStatement.h ProgramState.h
	g++ -g -c $< -o $@

Return.o: Return.cpp Return.h ProgramState.h
	g++ -g -c $< -o $@

.PHONY: clean

clean:
	rm -rf *.o
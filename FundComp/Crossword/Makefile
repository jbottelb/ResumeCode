
CMP = g++
CLASS = board
MAIN = crossword
EXEC = crossword

$(EXEC): $(CLASS).o $(MAIN).o
	$(CMP) $(CLASS).o $(MAIN).o -o $(EXEC)

$(CLASS).o: $(CLASS).cpp $(CLASS).h
	$(CMP) -c  $(CLASS).cpp -std=c++11 -o $(CLASS).o

$(MAIN).o: $(MAIN).cpp $(CLASS).h
	$(CMP) -c $(MAIN).cpp -std=c++11 -o $(MAIN).o

clean:
	rm *.o
	rm $(EXEC)


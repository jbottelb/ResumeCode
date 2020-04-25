
CMP = g++
CLASS = snake
MAIN = project
EXEC = play

$(EXEC): $(CLASS).o $(MAIN).o
	$(CMP) $(CLASS).o $(MAIN).o gfx2.o -lX11 -o $(EXEC) 

$(CLASS).o: $(CLASS).cpp $(CLASS).h
	$(CMP) -c  $(CLASS).cpp -std=c++11 -o $(CLASS).o 

$(MAIN).o: $(MAIN).cpp $(CLASS).h
	$(CMP) -c $(MAIN).cpp -std=c++11 -o $(MAIN).o 

clean:
	rm $(EXEC)


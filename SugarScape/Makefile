CXX = g++
CXXFLAGS=  -std=gnu++11  -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -fopenmp
TARGET= Sugarscape




ALL: *.o
	$(CXX) *.o -o $(TARGET)  $(CXXFLAGS)


DEBUG: *.o
	$(CXX) -g *.o -o  $(TARGET) $(CXXFLAGS)

CLEAN:
	rm *.o

%.o : %.cpp %.h
	$(CXX)  -c *.cpp  $(CXXFLAGS)
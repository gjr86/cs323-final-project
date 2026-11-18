CXX = g++
CXXFLAGS = -std=c++17 -Wall 
LDFLAGS  = -L/opt/homebrew/lib -lmatplot

schrodinger1D: schrodinger1D.cpp
	$(CXX) $(CXXFLAGS) -I /usr/local/include/eigen3/ -I /usr/local/include/matplotplusplus/1.2.2/include/ $(LDFLAGS) -o schrodinger1D schrodinger1D.cpp

clean:
	rm -f schrodinger1D output.txt

run: schrodinger1D
	./schrodinger1D
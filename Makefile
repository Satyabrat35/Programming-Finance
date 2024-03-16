CXX = g++
CXXFLAGS = -std=c++11
MATLAB_INCLUDE = -I/Applications/MATLAB_R2023b.app/extern/include/
MATLAB_LIB = -L/Applications/MATLAB_R2023b.app/bin/maca64 -leng -lmx -lm
RPATH = -Wl,-rpath,/Applications/MATLAB_R2023b.app/bin/maca64

SRC_FILES = Account_SatyabratBhol.cpp BankAccount_SatyabratBhol.cpp BubbleSort_SatyabratBhol.cpp DoublyLinkedList_SatyabratBhol.cpp Helper_SatyabratBhol.cpp \
            main_SatyabratBhol.cpp Node_SatyabratBhol.cpp SelectionSort_SatyabratBhol.cpp SortStratergy_SatyabratBhol.cpp StockAccount_SatyabratBhol.cpp StockAccountMatlab_SatyabratBhol.cpp

EXECUTABLE = accmgm

all: $(EXECUTABLE)

$(EXECUTABLE): $(SRC_FILES)
	$(CXX) $(CXXFLAGS) $(SRC_FILES) -o $(EXECUTABLE) $(MATLAB_INCLUDE) $(MATLAB_LIB) $(RPATH)

clean:
	rm -f $(EXECUTABLE)

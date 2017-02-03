SRC = src
INC = include
OBJ = obj
LIB = lib
BIN = bin
CXX = g++ -std=c++11
AR = ar rvs
AR_MACOSX = libtool -static -o  # Para MACs
CPPFLAGS = -Wall -g -I$(INC) -c



all: $(BIN)/prueba

# ************ Generación de documentación ******************
#documentacion:
#doxygen doc/doxys/doxPractica.txt


## ************ Compilación de módulos ************
$(BIN)/prueba: $(OBJ)/prueba.o $(LIB)/libNmer.a $(INC)/ktree.h
	$(CXX) -o $(BIN)/prueba $(OBJ)/prueba.o -I$(INC) -L$(LIB) -lNmer

$(OBJ)/prueba.o: $(SRC)/prueba.cpp
	$(CXX) $(CPPFLAGS)  -o $(OBJ)/prueba.o $(SRC)/prueba.cpp

$(LIB)/libNmer.a: $(OBJ)/Nmer.o
	$(AR_MACOSX) $(LIB)/libNmer.a $(OBJ)/Nmer.o

$(OBJ)/Nmer.o: $(SRC)/Nmer.cpp $(INC)/Nmer.h
	$(CXX) $(CPPFLAGS)  -o $(OBJ)/Nmer.o $(SRC)/Nmer.cpp

# ************ Limpieza ************
clean :
	-rm $(OBJ)/*

mrproper : clean
	-rm $(BIN)/*

clean_doc : clean
	-rm doc/html/* doc/latex/*

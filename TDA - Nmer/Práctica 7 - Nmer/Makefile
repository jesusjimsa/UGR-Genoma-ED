OBJ = obj
BIN = bin
INC = include
SRC = src
CPPFLAGS = g++ -std=c++11 -c -O3 -g

#Creación de ejecutables

$(BIN)/principal : $(OBJ)/principal.o $(OBJ)/enfermedad.o $(OBJ)/mutacion.o $(OBJ)/clinvar.o
	g++ -std=c++11 -g -O3 -o $(BIN)/principal $(OBJ)/principal.o $(OBJ)/enfermedad.o $(OBJ)/mutacion.o $(OBJ)/clinvar.o

#Creación de archivos objeto

$(OBJ)/principal.o: $(SRC)/principal.cpp
	$(CPPFLAGS) $(SRC)/principal.cpp -o $(OBJ)/principal.o -Iinclude/

$(OBJ)/enfermedad.o: $(SRC)/enfermedad.cpp
	$(CPPFLAGS) $(SRC)/enfermedad.cpp -o $(OBJ)/enfermedad.o -Iinclude/

$(OBJ)/mutacion.o: $(SRC)/mutacion.cpp
	$(CPPFLAGS) $(SRC)/mutacion.cpp -o $(OBJ)/mutacion.o -Iinclude/

$(OBJ)/clinvar.o: $(SRC)/clinvar.cpp
	$(CPPFLAGS) $(SRC)/clinvar.cpp -o $(OBJ)/clinvar.o -Iinclude/

#Limpieza de archivos objeto, ejecutables y bibliotecas

clean:
	echo "Limpiando..."
	rm $(OBJ)/*
mrproper: clean
	rm $(BIN)/*

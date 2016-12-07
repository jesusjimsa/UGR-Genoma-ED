//
//  principal.cpp
//  TDA - Clinvar
//
//  Created by Jesús Jiménez Sánchez on 7/12/16.
//  Copyright © 2016 Jesús Jiménez Sánchez. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <algorithm>
#include "mutacion.h"


using namespace std;
using namespace std::chrono;

bool load(vector<mutacion> &  vm, const string & s) {
	ifstream fe;
	string cadena;
	
	cout << "Abrimos "<< s << endl;
	
	fe.open(s.c_str(), ifstream::in);
	
	if(fe.fail()){
		cerr << "Error al abrir el fichero " << s << endl;
	}
	else{
		//leo la cabecera del fichero (líneas que comienzan con #)
		do{
			getline(fe,cadena,'\n');
		}while(cadena.find("#") == 0 && !fe.eof());
		
		//leo la tabla de mutaciones, una línea cada vez
		int i = 1;
		while (!fe.eof()){
			cout << "leo:: " << cadena << endl;
			cout << "\nLineas leidas: " << i << endl;
			
			i++;
			
			// Invoco el constructor de mutación que recibe una cadena completa, la parsea y crea la mutación.
			mutacion mut = mutacion(cadena);
			
			// Insertar mutación en el vector
			vm.push_back(mut);
			getline(fe,cadena,'\n');
		}
		fe.close();
		
		return true;
	} // else
	
	fe.close();
	
	return false;
}



int main(int argc, char *argv[]){
	vector<mutacion> vectorSNPs;
	string query_str;
	
	if (argc>1){
		query_str = argv[1];      //Término de búsqueda indicado por el usuario
	}else{
		query_str = "cancer";     //Default query: "cancer"
	}
	
	//Cargar las mutaciones en vectorSNPs
	load(vectorSNPs, "clinvar_20160831.vcf");
	
	//Imprimir número de elementos almacenados en vectorSNPs (130867 mutaciones totales)
	cout << "Lectura del fichero finalizada. Mutaciones cargadas: " << vectorSNPs.size() << endl;
	
	return 0;

	return 0;
}

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

int main(int argc, char *argv[]){
	vector<Mutacion> vectorSNPs;
	string query_str;
	
	if (argc>1){
		query_str = argv[1];      //Término de búsqueda indicado por el usuario
	}else{
		query_str = "cancer";     //Default query: "cancer"
	}
	
	//Cargar las mutaciones en vectorSNPs
	//load(vectorSNPs, "clinvar_20160831.vcf");
	
	//Imprimir número de elementos almacenados en vectorSNPs (130867 mutaciones totales)
	cout << "Lectura del fichero finalizada. Mutaciones cargadas: " << vectorSNPs.size() << endl;
	
	return 0;

	return 0;
}

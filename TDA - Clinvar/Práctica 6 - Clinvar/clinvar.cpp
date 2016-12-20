//
//  clinvar.cpp
//  TDA - Clinvar
//
//  Created by Jesús Jiménez Sánchez on 19/12/16.
//  Copyright © 2016 Jesús Jiménez Sánchez. All rights reserved.
//

#include "clinvar.h"
#include "enfermedad.h"
#include "mutacion.h"
#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <set>
#include <list>
#include <fstream>

using namespace std;

//Es basicamente lo mismo que hemos estado usando en principal.cpp en las anteriores prácticas
void Clinvar::load (string nombreDB){
	ifstream archivo;
	string cadena;
	set<Mutacion>::iterator it = mutDB.begin();
	list< set<Mutacion>::iterator > listilla;
	
	archivo.open(nombreDB);
	
	if(archivo.fail()){
		cerr << "Error al abrir el fichero " << nombreDB << endl;
	}
	else{
		//leo la cabecera del fichero (líneas que comienzan con #)
		do{
			getline(archivo,cadena,'\n');
		}while(cadena.find("#") == 0 && !archivo.eof());
		
		//leo la tabla de mutaciones, una línea cada vez
		int i = 1;
		while (!archivo.eof()){
			cout << "leo:: " << cadena << endl;
			cout << "\nLineas leidas: " << i << endl;
			
			i++;
			
			// Invoco el constructor de mutación que recibe una cadena completa, la parsea y crea la mutación.
			Mutacion mut = Mutacion(cadena);
			
			// Insertar mutación en el vector
			mutDB.insert(mut);
			IDm_map[mut.getID()] = it;
			
			for(int i = 0; i < mut.getGenes().size(); i++){
				gen_map[mut.getGenes()[i]].push_back(it);	//Este mapa contiene una lista
			}
			
			//Mapa con la lista de mutaciones, el ID se asocia
			for(int i = 0; i < mut.getEnfermedades().size(); i++){
				EnfDB[mut.getEnfermedades().at(i).getID()] = mut.getEnfermedades().at(i);
			}
			
			//Cada enfermedad se asocia a una mutación
			for(int i = 0; i < mut.getEnfermedades().size(); i++){
				IDenf_mmap.insert(pair<IDenf, set<Mutacion>::iterator>(mut.getEnfermedades().at(i).getID(), it));
			}
			
			++it;
			getline(archivo,cadena,'\n');
		}
		archivo.close();
		
	} // else
	
	archivo.close();
}

void Clinvar::insert (const Mutacion & x){
	
}

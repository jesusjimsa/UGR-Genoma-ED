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
#include <queue>
#include <unordered_set>

using namespace std;

//Es basicamente lo mismo que hemos estado usando en principal.cpp en las anteriores prácticas
void Clinvar::load (string nombreDB){
	ifstream archivo;
	string cadena;
	
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
			
			insert(mut);	//Inserto la posición en Clinvar
			
			getline(archivo,cadena,'\n');
		}
		archivo.close();
		
	} // else
	
	archivo.close();
}

void Clinvar::insert (const Mutacion & x){
	set<Mutacion>::iterator it;
	
	mutDB.insert(x);
	it = mutDB.find(x);		//Guardo la posición en la que se ha insertado
	
	IDm_map[x.getID()] = it;
	
	for(int i = 0; i < x.getGenes().size(); i++){
		gen_map[x.getGenes()[i]].push_back(it);	//Este mapa contiene una lista de iteradores
	}
	
	for(int i = 0; i < x.getEnfermedades().size(); i++){
		//Mapa con la lista de mutaciones, el ID se asocia
		EnfDB[x.getEnfermedades().at(i).getID()] = x.getEnfermedades().at(i);
		
		//Cada enfermedad se asocia a una mutación
		IDenf_mmap.insert(pair<IDenf, set<Mutacion>::iterator>(x.getEnfermedades().at(i).getID(), it));
	}
}

bool Clinvar::erase (IDmut ID){
	bool borrado = false;
	int mutaciones_asociadas[20];	//Suponiendo que haya 20 enfermedades como mucho por mutación
	set<Mutacion>::iterator it = IDm_map[ID];
	vector<Enfermedad> fuera = (*it).getEnfermedades();
	
	if(IDm_map.count(ID) > 0){	//Compruebo si la mutación existe
		for(int i = 0; i < 20; i++){
			mutaciones_asociadas[i] = 0;
		}
		
		for(int i = 0; i < fuera.size(); i++){
			for(auto ite = IDenf_mmap.begin(); ite != IDenf_mmap.end(); ++ite){
				if(ite->first == fuera[i].getID()){
					mutaciones_asociadas[i]++;
				}
			}
		}
		
		for(auto ite = IDenf_mmap.begin(); ite != IDenf_mmap.end(); ++ite){
			if(ite->second == IDm_map[ID]){
				ite = IDenf_mmap.erase(ite);
				/*
				 Como cada entrada del multimapa tendrá un iterador a una mutación, solo se borrará
				 una enfermedad, aunque haya varias con el mismo ID
				*/
			}
		}
		
		for(int i = 0; i < 20; i++){
			if (mutaciones_asociadas[i] == 1){
				EnfDB.erase((*it).getEnfermedades().at(i).getID());
			}
		}
		
		for(auto ite = gen_map.begin(); ite != gen_map.end(); ++ite){
			for(auto list_ite = gen_map[ite->first].begin(); list_ite != gen_map[ite->first].end(); ++list_ite){
				if((*list_ite) == IDm_map[ID]){
					list_ite = gen_map[ite->first].erase(list_ite);
				}
			}
		}
		
		mutDB.erase(it);
		IDm_map.erase(ID);
		
		borrado = true;
	}
	
	return borrado;
}

Clinvar::iterator Clinvar::find_Mut(IDmut ID){
	iterator it = end();
	
	if(IDm_map.count(ID) > 0){	//Compruebo si la mutación existe
		it = iterator(IDm_map[ID]);
	}
	
	return it;
}

Clinvar::enfermedad_iterator Clinvar::find_Enf(IDenf ID){
	enfermedad_iterator it = eend();
	
	if(EnfDB.count(ID) > 0){	//Compruebo si la enfermedad existe
		it = EnfDB.find(ID);
	}
	
	return it;
}

vector<Enfermedad> Clinvar::getEnfermedades(Mutacion & mut){
	return mut.getEnfermedades();
}

list<IDenf> Clinvar::getEnfermedades(string keyword){
	list<IDenf> lista_enf;
	
	for(auto it = EnfDB.begin(); it != EnfDB.end(); ++it){
		if((it->second).nameContains(keyword)){
			lista_enf.push_back(it->first);
		}
	}
	
	return lista_enf;
}

set<IDmut> Clinvar::getMutacionesEnf (IDenf ID){
	set<IDmut> conjunto_mut;
	
	for(auto it = IDenf_mmap.begin(); it != IDenf_mmap.end(); ++it){
		if(it->first == ID){
			conjunto_mut.insert((*(it->second)).getID());
		}
	}
	
	return conjunto_mut;
}

set<IDmut> Clinvar::getMutacionesGen (IDgen ID){
	set<IDmut> conjunto_mut;
	
	if(gen_map.count(ID) > 0){
		list< set<Mutacion>::iterator > mutaciones = gen_map[ID];
		
		for(int i = 0; i < mutaciones.size(); i++){
			conjunto_mut.insert( (*(mutaciones.back())).getID() );
			
			mutaciones.pop_back();
		}
	}
	
	return conjunto_mut;
}

set<Mutacion, Clinvar::ProbMutaciones> Clinvar::topKMutaciones (int k, string keyword){
	set<Mutacion, Clinvar::ProbMutaciones> topk;
	list<IDenf> enfermedades = getEnfermedades(keyword);
	set<IDmut> conj_mutaciones;
	priority_queue<IDmut, vector<IDmut>, ProbMutaciones> cola_p;
	unordered_set<IDmut> comprueba_repes;
	
	for(int i = 0; !enfermedades.empty(); i++){
		conj_mutaciones = getMutacionesEnf(enfermedades.back());
		
		for(auto it = conj_mutaciones.begin(); it != conj_mutaciones.end(); ++it){
			comprueba_repes.insert((*it));
			
			if(comprueba_repes.count((*it)) == 1){
				cola_p.push((*it));
			}
		}
		
		enfermedades.pop_back();
	}
	
	for(int i = 0; i < k; i++){
		topk.insert(cola_p.top());
		
		cola_p.pop();
	}
	
	return topk;
}

Clinvar::iterator Clinvar::begin(){
	auto aux = mutDB.begin();
	iterator it(aux);
	
	return it;
}

Clinvar::iterator Clinvar::end(){
	auto aux = mutDB.end();
	iterator it(aux);
	
	return it;
}

Clinvar::enfermedad_iterator Clinvar::ebegin(){
	return EnfDB.begin();
}

Clinvar::enfermedad_iterator Clinvar::eend(){
	return EnfDB.end();
}

Clinvar::gen_iterator Clinvar::gbegin(){
	auto gen_it = gen_map.begin();
	auto inside_gen_it = ((*gen_it).second).begin();
	
	return gen_iterator(gen_it, inside_gen_it, this);
}

Clinvar::gen_iterator Clinvar::gend(){
	auto gen_it = gen_map.end();
	auto inside_gen_it = ((*gen_it).second).end();
	
	return gen_iterator(gen_it, inside_gen_it, this);
}

Clinvar::iterator Clinvar::lower_bound(string cromosoma, unsigned int posicion){
	iterator lower(mutDB.end());
	bool encontrada = false;
	
	for(auto it = mutDB.begin(); it != mutDB.end() && !encontrada; ++it){
		if(stoi(cromosoma) >= stoi((*it).getChr()) ||
		   ((*it).getChr() == "X" && (cromosoma == "X" || cromosoma == "Y" || cromosoma == "MT")) ||
		   ((*it).getChr() == "Y" && (cromosoma == "Y" || cromosoma == "MT")) ||
		   ((*it).getChr() == "MT" && cromosoma == "MT")){
			if(posicion >= (*it).getPos()){
				encontrada = true;
				lower = iterator(it);
			}
		}
	}
	
	return lower;
}

Clinvar::iterator Clinvar::upper_bound(string cromosoma, unsigned int posicion){
	iterator upper(mutDB.end());
	bool encontrada = false;
	
	for(auto it = mutDB.begin(); it != mutDB.end() && !encontrada; ++it){
		if(stoi(cromosoma) > stoi((*it).getChr()) ||
		   ((*it).getChr() == "X" && (cromosoma == "Y" || cromosoma == "MT")) ||
		   ((*it).getChr() == "Y" && cromosoma == "MT")){
			if(posicion > (*it).getPos()){
				encontrada = true;
				upper = iterator(it);
			}
		}
	}
	
	return upper;
}

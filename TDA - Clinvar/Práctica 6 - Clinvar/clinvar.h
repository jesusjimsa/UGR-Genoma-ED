//
//  clinvar.h
//  TDA - Clinvar
//
//  Created by Jesús Jiménez Sánchez on 19/12/16.
//  Copyright © 2016 Jesús Jiménez Sánchez. All rights reserved.
//

#ifndef clinvar_hpp
#define clinvar_hpp

#include <stdio.h>
#include <string>
#include <set>
#include <list>
#include <map>
#include <unordered_map>
#include "mutacion.h"
#include "enfermedad.h"

using namespace std;

typedef string IDgen;
typedef string IDmut;
typedef string IDenf;

class Clinvar{
private:
	set<Mutacion> mutDB;
	unordered_map<IDmut,set<Mutacion>::iterator> IDm_map;
	map<IDgen, list< set<Mutacion>::iterator> > gen_map;
	map<IDenf,Enfermedad> EnfDB;
	multimap<IDenf, set<Mutacion>::iterator> IDenf_mmap;
public:
	/*
	 @brief iterador sobre mutaciones en orden creciente de cromosoma/posicion
	 */
	class iterator {
	private:
		set<Mutacion>::iterator it;
	public:
		const Mutacion & operator*(); //const - no se puede modificar la mutacion y alterar el orden del set
	};
	
	/* @brief iterador sobre enfermedades
	 */
	// Nos vale utilizar el iterador del map
	typedef map<IDenf, Enfermedad>::iterator enfermedad_iterator;
	
	/*
	 @brief iterador sobre mutaciones considerando el orden creciente del ID del gen
	 */
	class gen_iterator {
	public:
		const Mutacion & operator*(); //const - no se puede modificar la mutacion y alterar el orden delset
	private:
		map<IDgen, list< set<Mutacion>::iterator> > >::iterator itmap;
		list< set<Mutacion>::iterator > >::iterator itlist;
		Clinvar *ptrclinvar;
	};
	
	void load (string nombreDB);
	void insert (const Mutacion & x);
	bool erase (IDmut ID);
	
	iterator find_Mut (IDmut ID);
	enfermedad_iterator find_Enf(IDenf ID);
	
	vector<Enfermedad> getEnfermedades(Mutacion & mut);
	list<IDenf> getEnfermedades(string keyword);
	set<IDmut> getMutacionesEnf (IDenf ID);
	set<IDmut> getMutacionesGen (IDgen ID);
	
	set<Mutacion, ProbMutaciones> topKMutaciones (int k, string keyword);
	
	/* Métodos relacionados con los iteradores */
	iterator begin();
	iterator end();
	iterator lower_bound(string cromosoma, unsigned int posicion);
	iterator upper_bound(string cromosoma, unsigned int posicion);
	enfermedad_iterator ebegin();
	enfermedad_iterator eend();
	gen_iterator gbegin();
	gen_iterator gend();
};

//Functor
class ProbMutaciones{
private:
	bool hola;
public:
	ProbMutaciones(){
		
	}
};

#endif /* clinvar_h */

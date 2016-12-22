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
	/**
	 @brief iterador sobre mutaciones en orden creciente de cromosoma/posicion
	*/
	class iterator {
	private:
		set<Mutacion>::iterator it;
	public:
		/**
		 @brief Constructor por defecto
		*/
		iterator(){
		
		}
		
		/**
		 @brief Constructor a partir de un iterador de set
		 @param ite Iterador de set<Mutacion>
		 
		 Construye un iterator a partir de un iterador de set<Mutacion>
		*/
		iterator(set<Mutacion>::iterator ite){
			it = ite;
		}
		
		/**
		 @brief Operador de acceso
		 @return Mutación de la posición que indica it
		*/
		const Mutacion & operator*(){ //const - no se puede modificar la mutacion y alterar el orden del set
			return (*it);
		}
		
		/**
		 @brief Operador de asignación
		 @param otro Otro objeto de la clase iterator
		 @return El iterador asignado
		 */
		iterator & operator=(iterator otro){	//Operador de asignación
			if(this != &otro){
				it = otro.it;
			}
			
			return *this;
		}
	};
	
	/**
	 @brief iterador sobre enfermedades
	*/
	// Nos vale utilizar el iterador del map
	typedef map<IDenf, Enfermedad>::iterator enfermedad_iterator;
	
	/**
	 @brief iterador sobre mutaciones considerando el orden creciente del ID del gen
	 */
	class gen_iterator {
	public:
		const Mutacion & operator*(); //const - no se puede modificar la mutacion y alterar el orden del set
	private:
		map<IDgen, list< set<Mutacion>::iterator> >::iterator itmap;
		list< set<Mutacion>::iterator >::iterator itlist;
		Clinvar *ptrclinvar;
	};
	
	//Functor
	class ProbMutaciones{
	public:
		bool operator()(Mutacion a, Mutacion b){
			return a < b;
		}
	};
	
	/**
	 @brief Lee los elementos de un fichero
	 @param nombreDB Nombre del fichero
	 
	 Se encarga de leer los elementos de un fichero dado por el argumento nombreDB, e insertar toda la
	 información en ClinVar.
	*/
	void load (string nombreDB);
	
	/**
	 @brief Inserta una nueva mutación
	 @param x Mutación a insertar
	 
	 Este método se encarga de insertar una nueva mutación en ClinVar. Esto implica actualizar todas las estructuras
	 necesarias para mantener la coherencia interna de la representación propuesta.
	 */
	void insert (const Mutacion & x);
	
	/**
	 @brief Borra una mutación de la base de datos dado su ID.
	 @param ID ID de la mutación
	 @return Devuelve true si la ha conseguido borrar, false en el caso contrario
	 
	 No sólo borra la mutación del repositorio principal de datos sino que además se encarga de borrar toda referencia
	 a dicho elemento dentro de él.
	 En el caso de que una enfermedad estuviese asociada únicamente a la mutación que está siendo eliminada, esta
	 enfermedada también debe eliminarse de ClinVar.
	*/
	bool erase (IDmut ID);
	
	/**
	 @brief Busca una mutación
	 @param ID ID de la mutación
	 @return Un iterador a la mutación
	 
	 Busca la mutación con identificador ID dentro de ClinVar, si no lo encuentra devuelve end()
	*/
	iterator find_Mut(IDmut ID);
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
	
	//Clases amigas
private:
	friend class iterator;
	friend class gen_iterator;
	friend class ProbMutaciones;
};



#endif /* clinvar_h */

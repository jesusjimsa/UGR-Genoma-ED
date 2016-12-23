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
	set<Mutacion> mutDB;	//Base de datos que contiene toda la información asociada a una mutacion
	unordered_map<IDmut, set<Mutacion>::iterator> IDm_map;	// Asocia IDmutacion con mutación
	map<IDgen, list< set<Mutacion>::iterator> > gen_map;	// Asocia genes con mutaciones
	map<IDenf, Enfermedad> EnfDB;	// Base de datos de enfermedades
	multimap<IDenf, set<Mutacion>::iterator> IDenf_mmap;	// Asocia enfermedad con mutaciones
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
		
		/**
		 @brief Operador de incremento
		 @return Iterador incrementado
		 */
		iterator &operator++(){
			it++;
			
			return (*this);
		}
		
		/**
		 @brief Operador de decremento
		 @return Operador decrementado
		 */
		iterator &operator--(){
			it--;
			
			return (*this);
		}
		
		/**
		 @brief Operador de comparación
		 @param otro Otro iterador
		 @return ture si son iguales, false en caso contrario
		 */
		bool operator==(iterator otro){
			return it == otro.it;
		}
		
		/**
		 @brief Operador de diferencia
		 @param otro Otro iterador
		 @return true si son distintos, falso en caso contrario
		 */
		bool operator!=(iterator otro){
			return it != otro.it;
		}
	};
	
	/**
	 @brief iterador sobre enfermedades
	*/
	typedef map<IDenf, Enfermedad>::iterator enfermedad_iterator;	// Nos vale utilizar el iterador del map
	
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
	
	/**
	 @brief Busca una enfermedad
	 @param ID ID de la enfermedad
	 @return Iterador a la enfermedad
	 
	 Busca la enfermedad con identificador ID dentro de ClinVar, si no lo encuentra devuelve eend()
	 */
	enfermedad_iterator find_Enf(IDenf ID);
	
	/**
	 @brief Consultor de enfermedades
	 @param mut Mutación a investigar
	 @return Vector de enfermedades
	 
	 Devuelve un vector con todas las enfermedades asociadas a una mutación en la base de
	 datos clinvar.
	 */
	vector<Enfermedad> getEnfermedades(Mutacion & mut);
	
	/**
	 @brief Consultor de identificadores de enfermedad
	 @param keyword Palabra clave
	 @return Identificadores de las enfermedades que contienen la palabra
	 
	 Devuelve una lista de los identificadores de enfermedad que contienen la palabra keyword como
	 parte del nombre de la enfermedad.
	 */
	list<IDenf> getEnfermedades(string keyword);
	
	/**
	 @brief Consultor de mutaciones asociadas a una enfermedad
	 @param ID ID de una enfermedad
	 @return Conjunto de mutaciones asociadas a una enfermedad
	 
	 Devuelve un conjunto ordenado (en orden creciente de IDmut) de todas las mutaciones que se encuentran asociadas
	 a la enfermedad con identificador ID. Si no tuviese ninguna enfermedad asociada, devuelve el conjunto
	 vacío.
	 */
	set<IDmut> getMutacionesEnf (IDenf ID);
	
	/**
	 @brief Consultor de mutaciones asociadas a un gen
	 @param ID ID de un gen
	 @return Conjunto de mutaciones asociadas a un gen
	 
	 Devuelve un conjunto de todas las mutaciones que se encuentran asociadas a un gen determinado dado por ID.
	 Si no tuviese ninguno, devuelve el conjunto vacío.
	 */
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

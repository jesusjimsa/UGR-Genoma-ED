
/**
 * @file Nmer.h
 * @brief TDA Nmer
 *   Representa un conjunto de Nmer subsecuencias de tamaño 1 hasta N que se pueden obtener a partir de una cadena de ADN
 * @author alumno
 * @bug Por espeficicar
 */
#ifndef __NMER_H
#define __NMER_H

#include "ktree.h"
#include <string>
#include <set>

using namespace std;

class Nmer {
public:
	typedef unsigned int size_type;
	
	/**
	 @brief Constructor primitivo .
	 Crea un Nmer de longitud maxima 0, con el valor ('-',0) en la raíz
  */
	Nmer();
	
	/**
	 * @brief lectura fichero serializado
	 * @param nombre_fichero fichero serializado con extension .srl
	 *
	 * Genera a partir del fichero el ktree que contiene todos los kmers asociados a una cadena de ADN
	 *
	 * La cadena original viene descrita en el fichero serializado
	 */
	bool loadSerialized(const string & nombre_fichero);
	
	
	/** 
	 * @brief Imprime los Nmers
	 * @todo Debemos de implementar este método de forma que nos garantizemos que se imprimen todos los Nmers.
	 */
	void list_Nmer() const;
	
	/**
	 @brief Árbol asocidado a una cadena
	 @param adn subcadena
	 @return Devuelve el Nmer (subarbol) asociado a un prefijo
	 Por ejemplo, si adn es "ACT", devuelve el Nmer que representa todas las subcadenas que empiezan por "ACT" (ACT*)
	 */
	Nmer Prefix(string adn);
	
	/** @brief Máxima longitud de los Nmers almacenados
	 */
	unsigned int length()const;
	
	
	/**
	 @brief Número de Nmers almacenados
	 */
	size_type size() const;
	
	/**
	 @brief Calcula el máximo de cuatro números
	 @param first Primer valor
	 @param second Segundo valor
	 @param third Tercer valor
	 @param fourth Cuarto valor
	 @return El máximo
	 */
	int maxi(int first, int second, int third, int fourth);
	
	/**
	 @brief Calcula la profundidad máxima de un árbol
	 @param hola nodo del que se parte
	 @return profundidad máxima
	 */
	unsigned int profundidadMax(ktree<pair<char,int>, 4>::node nodo);
	
	/**
	 @brief Construir Nmer a partir de una cadena de ADN
	 @param tama Tamaño de la cadena
	 @param adn Cadena de ADN
	 */
	void sequenceADN(unsigned int tama, const string & adn);
	
	/**
	 @brief Functor para ordenar por frecuencia creciente un Nmer
	 
	 Se utiliza en rareNmer
	 */
	class OrdenCre{
	public:
		bool operator()(pair<string,int> a, pair<string, int> b){
			return a.second > b.second;
		}
	};
	
	/**
	 @brief Functor para ordenar por frecuencia decreciente un Nmer
	 
	 Se utiliza en rareNmer
	 */
	class OrdenDecre{
	public:
		bool operator()(pair<string,int> a, pair<string, int> b){
			return a.second < b.second;
		}
	};
	
	/**
	 @brief Inserta el árbol de una cadena de ADN
	 @param cadena Cadena de ADN
	 */
	void insertar_cadena(const string & cadena);
	
	/**
	 @brief Lista de todas las subcadenas que aparecen menos de threshold veces
	 @param threshold Número de veces que se sepite el Nmer como mucho
	 @return Lista de todas las subcadenas que aparecen menos de threshold veces
	 
	 Devuelve la lista de todas las subcadenas (no prefijo) que aparecen menos
	 de threshold veces en el Nmer ordenadas en orden creciente de frecuencia
	 */
	set<pair<string,int>, OrdenCre> rareNmer(int threshold);
	
	set<pair<string,int>, OrdenDecre> commonNmer(int threshold);
	
	/**
	 @brief Este método nos devuelve únicamente los Nmers de longitud l
	 @param l Longitud del Nmer
	 @return Nmers de longitud l ordenados por frecuencia
	 */
	set<pair<string,int>, OrdenCre > level(int l);
	
	bool containsString(const string adn); // Devuelve true si la cadena adn está representada en el árbol.
	
	bool included(const Nmer reference) const; // Devuelve true si cada nodo de *this está también representado en reference, es decir, si todas las secuencias representadas en el árbol de *this están también incluidas en reference. False en otro caso.
	
	Nmer & operator=(const Nmer & a);	// operador de asignacion
private:
	ktree<pair<char,int>,4> el_Nmer; // subsecuencias
	unsigned int max_long; // Mayor longitud de la cadena representada, esto es, el nivel máximo del árbol
 
	/**
	 @brief Functor para convertir un string en un pair<char,int>
	 
	 Se utiliza en loadSerialized
	 */
	class String2Base {
	public:
		pair<char,int> operator()(const string & cad) {
			pair<char,int> salida;
			salida.first = cad[0];
			salida.second = stoi(cad.substr(1));
			return salida;
		}
	};
	
	/**
	 @brief Functor para convertir un pair<char,int> en un string
	 
	 Necesario para serializar un Nmer.
	 */
	class Base2String {
	public:
		string operator()(const pair<char,int> & x) {
			string salida = string(1, x.first) + " " + to_string(x.second);
			return salida;
		}
	};
};



#endif

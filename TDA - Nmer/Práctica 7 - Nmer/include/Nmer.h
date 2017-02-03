
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
	 @brief lectura fichero serializado
	 @param nombre_fichero fichero serializado con extension .srl
	 
	 Genera a partir del fichero el ktree que contiene todos los kmers asociados a una cadena de ADN
	 La cadena original viene descrita en el fichero serializado
	 */
	bool loadSerialized(const string & nombre_fichero);
	
	
	/**
	 @brief Imprime los Nmers
	 @todo Debemos de implementar este método de forma que nos garantizemos que se imprimen todos los Nmers.
	 */
	void list_Nmer() const;
	
	/**
	 @brief Árbol asocidado a una cadena
	 @param adn subcadena
	 @return Devuelve el Nmer (subarbol) asociado a un prefijo
	 Por ejemplo, si adn es "ACT", devuelve el Nmer que representa todas las subcadenas que empiezan por "ACT" (ACT*)
	 */
	Nmer Prefix(string adn);
	
	/**
	 @brief Máxima longitud de los Nmers almacenados
	 */
	unsigned int length()const;
	
	/**
	 @brief Comprueba si this está contenido en reference
	 @param reference Árbol que se comprueba
	 @return true si está incluido, false si no lo está
	 
	 Devuelve true si cada nodo de *this está también representado en reference, es decir, si todas las
	 secuencias representadas en el árbol de *this están también incluidas en reference. False en otro caso.
	 */
	bool included(const Nmer reference) const;
	
	/**
	 @brief Compara dos arboles a partir de un nodo de cada uno
	 @param uno Un árbol
	 @param otro Otro árbol
	 @return Devuelve true si otro contiene a uno, false en caso contrario
	 */
	bool compararNmers(ktree<pair<char,int>,4>::const_node uno, ktree<pair<char,int>,4>::const_node otro) const;
	
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
	 @return El máximo de los cuatro
	 */
	int maxi(int first, int second, int third, int fourth);
	
	/**
	 @brief Calcula la profundidad máxima de un árbol
	 @param nodo Nodo del que se parte
	 @return Profundidad máxima
	 */
	unsigned int profundidadMax(const ktree<pair<char,int>, 4>::node nodo);
	
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
	 @brief Rellena el conjunto que se devuelve en rareNmer
	 @param el_set Conjunto que se está cambiando
	 @param el_nodo Nodo actual
	 @param la_cadena El string del conjunto
	 @param threshold Número de veces que se repite el Nmer como mucho
	 */
	void rareSet(set<pair<string,int>, OrdenCre> &el_set, ktree<pair<char, int>, 4>::node el_nodo, string la_cadena, int threshold);
	
	/**
	 @brief Lista todas las subcadenas que aparecen menos de threshold veces
	 @param threshold Número de veces que se sepite el Nmer como mucho
	 @return Conjunto de todas las subcadenas que aparecen menos de threshold veces
	 
	 Devuelve la lista de todas las subcadenas (no prefijo) que aparecen menos
	 de threshold veces en el Nmer ordenadas en orden creciente de frecuencia.
	 */
	set<pair<string,int>, OrdenCre> rareNmer(int threshold);
	
	/**
	 @brief Rellena el conjunto que se devuelve en commonNmer
	 @param el_set Conjunto que se está cambiando
	 @param el_nodo Nodo actual
	 @param la_cadena El string del conjunto
	 @param threshold Número de veces que se repite el Nmer como mínimo
	 */
	void commonSet(set<pair<string,int>, OrdenDecre> &el_set, ktree<pair<char, int>, 4>::node el_nodo, string la_cadena, int threshold);
	
	/**
	 @brief Lista todas las subcadenas que aparecen más de threshold veces
	 @param threshold Número de veces que se repite el Nmer
	 @return Conjunto de todas las cadenas que aparecen más de threshold veces
	 
	 Devuelve el conjunto de las subcadenas de longitud mayor posible (sin ser prefijo) que aparecen un número
	 de veces mayor que de threshold veces en el Nmer, ordenadas en orden decreciente de frecuencia.
	 */
	set<pair<string,int>, OrdenDecre> commonNmer(int threshold);
	
	/**
	 @brief Rellena el conjunto que se devuelve en level
	 @param el_set Conjunto que se está cambiando
	 @param el_nodo Nodo actual
	 @param la_cadena El string del conjunto
	 @param l Longitud del Nmer
	 */
	void levelSet(set<pair<string,int>, OrdenCre> &el_set, ktree<pair<char, int>, 4>::node el_nodo, string la_cadena, int l);
	
	/**
	 @brief Este método nos devuelve únicamente los Nmers de longitud l
	 @param l Longitud del Nmer
	 @return Nmers de longitud l ordenados por frecuencia
	 */
	set<pair<string,int>, OrdenCre > level(int l);
	
	/**
	 @brief Comprueba si la cadena está en el Nmer
	 @param adn Cadena con un Nmer
	 @return True si está contenida, false en el caso contrario
	 */
	bool containsString(const string adn);
	
	/**
	 @brief Operador de asignación
	 @param a Otro Nmer
	 @return Guarda el a en this
	 */
	Nmer & operator=(const Nmer & a);
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

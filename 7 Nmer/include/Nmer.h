
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

using namespace std;

class Nmer {
public:
  typedef unsigned int size_type;
  
  /** @brief Constructor primitivo .
      Crea un Nmer de longitud maxima 0, con el valor ('-',0) en la raíz
  */
  Nmer();
  
  /** @brief lectura fichero serializado
   * @param nombre_fichero fichero serializado con extension .srl
   *
   * Genera a partir del fichero el ktree que contiene todos los kmers asociados a una cadena de ADN
   *
   * La cadena original viene descrita en el fichero serializado
   */ 
  bool loadSerialized(const string & nombre_fichero);
  
  
  /** @brief Imprime los Nmers
   * @todo Debemos de implementar este método de forma que nos garantizemos que se imprimen todos los Nmers.
   */ 
   void list_Nmer() const;
   
   
  /** @brief Máxima longitud de los Nmers almacenados
   */ 
   unsigned int length()const;
   
     
  /** @brief Número de Nmers almacenados
   */ 
   size_type size() const;
  
private:
  ktree<pair<char,int>,4> el_Nmer; // subsecuencias 
  unsigned int max_long; // Mayor longitud de la cadena representada, esto es, el nivel máximo del árbol
 
  /** @brief Functor para convertir un string en un pair<char,int>
   * se utiliza en loadSerialized
   */
  class String2Base {
   public:
    pair<char,int> operator()( const string & cad) {
	    pair<char,int> salida;
	    salida.first = cad[0];
	    salida.second = std::stoi(cad.substr(1)); 
	    return salida;
    }
  };

   /** @brief Functor para convertir un pair<char,int> en un string 
    * Necesario para serializar un Nmer.
   */
  class Base2String {
   public:
     string operator()( const pair<char,int> & x) {
       string salida = string(1,x.first) + " " +std::to_string(x.second); 
       return salida;
     }
  };
};

#endif

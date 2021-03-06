//
//  mutacion.h
//  TDA - Clinvar
//
//  Created by Jesús Jiménez Sánchez on 7/12/16.
//  Copyright © 2016 Jesús Jiménez Sánchez. All rights reserved.
//

#ifndef __MUTACION_H
#define __MUTACION_H

#include <string>
#include <iostream>
#include <vector>

#include "enfermedad.h"

using namespace std;
//! Clase mutacion, asociada a la definición de una mutación/SNP
/*! mutacion::mutacion,  .....
 *
 @todo Implementa esta clase, junto con su documentación asociada
 
 */


class Mutacion {
private:
	string ID;
	string chr;
	unsigned int pos;
	vector<string> ref_alt;
	vector<string> genes;
	bool common;
	vector<float> caf;
	vector<Enfermedad> enfermedades;
	vector<int> clnsig;
	
public:
	/**
	 @brief Inicia una mutacion vacía.
	 */
	Mutacion();
	
	/**
	 @brief Crea una mutación a partir de otra.
	 @param m 	mutación a copiar
	 
	 Copia los valores de la mutación pasada como argumento y crea una nueva a partir de ellos.
	 */
	Mutacion(const Mutacion& m);
	
	/**
	 @brief Crea una mutación a partir de un string.
	 @param str 	cadena string con los datos miembro de la clase
	 
	 Se le pasa un string como argumento y se recorre este guardando los correspondientes datos miembro.
	 */
	Mutacion(const string & str);   //para crear objeto mutacion a partir de la cadena que contiene una línea completa del fichero de entrada
	
	/**
	 @brief Cambia el valor de ID
	 @param id	id de la mutación
	 */
	void setID(const string & id);
	
	/**
	 @brief Cambia el valor del cromosoma
	 @param chr	nuevo cromosoma
	 */
	void setChr(const string & chr);
	
	/**
	 @brief Cambia el valor de la posición
	 @param pos	posicion nueva
	 */
	void setPos(const unsigned int & pos);
	
	/**
	 @brief Cambia el valor del genoma básico
	 @param ref_alt	vector de string que contiene el genoma tipo
	 */
	void setRef_alt(const vector<string> & ref_alt);
	
	/**
	 @brief Cambia el valor de los genes
	 @param genes	vector con los genes
	 */
	void setGenes (const vector<string> & genes);
	
	/**
	 @brief Cambia el valor del bool de si es común o no la mutación
	 @param common	nuevo bool
	 */
	void setCommon (const bool & common);
	
	/**
	 @brief Cambia el valor de la frecuencia de cada base
	 @param caf	nuevo vector con frecuencias
	 */
	void setCaf (const vector<float> & caf);
	
	/**
	 @brief Cambia el valor del vector de enfermedades
	 @param enfermedades	nuevo vector con enfermedades
	 */
	void setEnfermedades (const vector<Enfermedad> & enfermedades);
	
	/**
	 @brief Cambia la relevancia clínica.
	 @param clnsig	nuevo vector de enteros
	 */
	void setClnsig (const vector<int> & clnsig);
	
	/**
	 @brief Devuelve el ID de la mutación
	 @return ID	valor del id de la mutación
	 */
	string getID( ) const;
	
	/**
	 @brief Devuelve el identificador del cromosoma
	 @return chr	identificador del cromosoma
	 */
	string getChr( ) const;
	
	/**
	 @brief Devuelve la posición del cromosoma.
	 @return pos	posición del cromosoma
	 */
	unsigned int getPos( ) const;
	
	/**
	 @brief Devuelve el vector del genoma básico
	 @return ref_alt	vector del genoma básico
	 */
	const vector<string> & getRef_alt () const;
	
	/**
	 @brief Devuelve el vector de los genes.
	 @return genes	vector de los genes
	 */
	const vector<string> & getGenes () const;
	
	/**
	 @brief Devuelve si una mutación es común o no.
	 @return common	bool de si es común o no
	 */
	bool getCommon () const;
	
	/**
	 @brief Devuelve el vector de las frecuencias de cada base.
	 @return caf	vector de las frecuencias
	 */
	const vector<float> & getCaf () const;
	
	/**
	 @brief Devuelve el vector de las enfermedades.
	 @return enfermedad	vector de las enfermedades
	 */
	const vector<Enfermedad> & getEnfermedades () const;
	
	/**
	 @brief Devuelve el vector de enteros que conforman la relevancia clínica.
	 @return clnsig	vector de enteros con la relevancia clínica.
	 */
	const vector<int> & getClnsig () const;
	
	/**
	 @brief Devuelve la relevancia clínica convertida en el string hola
	 @return hola	string con la relevancia clínica.
	 */
	string imprime_Ref() const;	//Añado este método para imprimir el vector ref_alt
	
	/**
	 @brief Devuelve la referencia de los genes convertida en el string hola
	 @return hola	string con la referencia
	 */
	string imprime_Genes() const;	//Lo mismo para genes
	
	/**
	 @brief Devuelve la frecuencia de cada base.
	 @return hola	string con la frecuencia
	 */
	string imprime_Caf() const;	//eequilicuá
	
	/**
	 @brief Devuelve la las enfermedades asociadas
	 @return hola	string con las enfermedades
	 */
	string imprime_Enfermedades()const;	//Lo mismo
	
	/**
	 @brief Sobrecarga el operador = para ajustarlo a una mutación
	 @param m	mutación a la que se iguala
	 @return *this
	 */
	Mutacion & operator=(const Mutacion & m);
	
	/**
	 @brief Sobrecarga el operador == para compararlo con una mutación
	 @param m	mutación a comparar
	 @return iguales
	 */
	bool operator==(const Mutacion & m) const;
	
	/**
	 @brief ESobrecarga el operador < para comparar una mutación
	 @param m	mutación a comparar
	 @return menor
	 */
	bool operator<(const Mutacion & m) const;      //El orden viene determinado por Chr y pos. El primer criterio es el número de cromosoma. El orden para el número de cromosoma se rige por "1"<"2"<"3"<...<"22"<"X"<"Y"<"MT". Dos mutaciones del mismo cromosoma deben ordenarse según su posición, de menor posición a mayor (orden natural de enteros).
	
};

/**
 @brief Sobrecarga el operador << para imprimir mutaciones.
 @param os	flujo de salida
 @param m	mutación a imprimir
 @return os	flujo de impresión
 */
ostream& operator<< ( ostream& os, const Mutacion& m);   //Imprimir TODOS los campos del objeto mutación.

#endif

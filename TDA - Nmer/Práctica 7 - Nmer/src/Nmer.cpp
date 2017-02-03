#include "Nmer.h"
#include "ktree.h"
#include <fstream>
#include <iostream>
#include <set>
#include <string>

using namespace std;

template<typename T, int K>
extern void recorrido_preorden(typename ktree<T,K>::const_node n, string anterior);

Nmer::Nmer(){
	max_long = 0;
	el_Nmer = ktree<pair<char,int>,4>(pair<char,int>('-',0));
	
}

bool Nmer::loadSerialized(const string & fichero) {
	string cadena;
	ifstream fe;
	pair<char,int> nulo('x', -1);
	Nmer::String2Base stb;
 
	fe.open(fichero.c_str(), ifstream::in);
	if (fe.fail()){
		cerr << "Error al abrir el fichero " << fichero << endl;
	}
	else {
		//leo la cabecera del fichero (líneas que comienzan con #)
		
		do{
			getline(fe,cadena,'\n');
		} while (cadena.find("#") == 0 && !fe.eof());
	 
		// leemos Nmer_length
		max_long = stoi(cadena);
	 
		// leemos cadena serializada
		getline(fe,cadena,'\n');
		el_Nmer.deserialize(cadena,nulo,';',stb);
	 
		fe.close();
		return true;
	} // else
	fe.close();
	return false;
}

//Función para recorrer el árbol en preorden sacada de ejemploKtree.cpp
string recorrido_preorden(typename ktree<pair<char,int>, 4>::const_node n, string anterior){
	if(n.null()){
		string vacio;
		
		return vacio;
	}
	else{
		string cadenaA, cadenaG, cadenaC, cadenaT;
		
		cadenaA = cadenaG = cadenaC = cadenaT = anterior;
		
		for(int i = 0; i < 4; i++){
			if(!n.k_child(i).null()){
				switch (i) {
					case 0:
						cout << cadenaA << endl;
						cadenaA += "A";
						cadenaA += recorrido_preorden(n.k_child(i), cadenaA);
						break;
					case 1:
						cout << cadenaG << endl;
						cadenaG += "G";
						cadenaG += recorrido_preorden(n.k_child(i), cadenaG);
						break;
					case 2:
						cout << cadenaC << endl;
						cadenaC += "C";
						cadenaC += recorrido_preorden(n.k_child(i), cadenaC);
						break;
					case 3:
						cout << cadenaT << endl;
						cadenaT += "T";
						cadenaT += recorrido_preorden(n.k_child(i), cadenaT);
						break;
					default:
						break;
				}
			}
		}
		
		return anterior;
	}
}

void Nmer::list_Nmer() const {
	string cadena;
	// implmenentar el recorrido en preorden para el ktree de forma que nos devuelva los Nmers completos y no sólo el nodo.
	cout << "Arbol en preorden" << endl;
	recorrido_preorden(el_Nmer.root(), cadena);
}

unsigned int Nmer::length() const {
	return max_long;
}

Nmer::size_type Nmer::size() const{
	return el_Nmer.size() - 1;
}

void Nmer::sequenceADN(unsigned int tama, const string & adn){
	vector<string> cadenas;
	vector<char> cadena_aux;
	
	//Inicializamos el árbol poniendo la etiqueta (’-’,0) en el nodo raíz
	el_Nmer = ktree<pair<char,int>,4>(pair<char,int>('-',0));
	
	for(int i = 0; i < adn.size(); i++){
		//Se guardan los caracteres en un vector auxiliar
		for(int j = 0; j < tama; j++){
			cadena_aux.push_back(adn[j]);
		}
		
		//Se inicializa la posición en el vector definitivo
		cadenas.push_back("");
		
		//Se guardan los caracteres en el vector
		for(int j = 0; j < tama; j++){
			cadenas[i] += cadena_aux[j];
		}
		
		//Se limpia el vector de char auxiliar
		cadena_aux.clear();
		insertar_cadena(cadenas[i]);
	}
}

void Nmer::insertar_cadena(const string & cadena){
	ktree<pair<char,int>,4>::node n_act(el_Nmer.root());	//Posicionamos un nodo, n_act, en la raiz del arbol
	pair<char,int> etiqueta;
	int indice = 0;
	
	//Este nodo n lo utilizamos para descender por el arbol
	// cadena[i] nos indica el índice del nodo en el nivel i+1;
	// A -> hijo 0; G -> hijo 1; C-> hijo 2; T-> hijo 3
	
	for(int i = 0; i < cadena.length(); i++){
		//cadena[i] nos indica el índice del nodo en el nivel i+1
		switch (cadena[i]) {
			case 'A':
				indice = 0;
				break;
			case 'G':
				indice = 1;
				break;
			case 'C':
				indice = 2;
				break;
			case 'T':
				indice = 3;
				break;
			default:
				break;
		}
		
		if(!n_act.k_child(indice).null()){
			(*n_act.k_child(indice)).second++;
		}
		else{
			etiqueta.first = cadena[i];
			etiqueta.second = 1;
			
			el_Nmer.insert_k_child(n_act, indice, etiqueta);
		}
		
		
		//descendemos en el árbol, haciendo que n_act sea el nodo que representa cadena[i], esto es bajamos al
		//hijo correspondiente
		n_act = n_act.k_child(indice);
	}
	
	if(cadena.length() > max_long){
		max_long = (unsigned int)cadena.length();
	}
}


set<pair<string,int>, Nmer::OrdenCre> Nmer::rareNmer(int threshold){
	set<pair<string,int>, Nmer::OrdenCre> rare;
	
	/////////////////////////////////////////////////////////////
	
	return set<pair<string,int>, Nmer::OrdenCre>();
}

bool Nmer::containsString(const string adn){
	ktree<pair<char,int>, 4>::node n_act(el_Nmer.root());
	int indice = 0;
	
	for(int i = 0; i < adn.length(); i++){
		switch (adn[i]) {
			case 'A':
				indice = 0;
				break;
			case 'G':
				indice = 1;
				break;
			case 'C':
				indice = 2;
				break;
			case 'T':
				indice = 3;
				break;
			default:
				break;
		}
		
		n_act = n_act.k_child(indice);
		
		if(n_act.null()){
			return false;
		}
	}
	
	return true;
}

Nmer & Nmer::operator=(const Nmer & a){		//Operador de asignacion
	if(this != &a){
		this->el_Nmer = a.el_Nmer;
		this->max_long = a.max_long;
	}
	
	return (*this);
}

Nmer Nmer::Prefix(string adn){
	Nmer devolver;
	ktree<pair<char,int>, 4> arb_copia, arb_dest;
	ktree<pair<char,int>, 4>::node nodo(el_Nmer.root());
	int indice = 0;
	int num_hijos = 0;
	
	arb_copia = this->el_Nmer;
	
	for(int i = 0; i < adn.length(); i++){	//Me muevo al último nodo que indique la cadena
		switch (adn[i]) {
			case 'A':
				indice = 0;
				break;
			case 'G':
				indice = 1;
				break;
			case 'C':
				indice = 2;
				break;
			case 'T':
				indice = 3;
				break;
			default:
				break;
		}
		
		nodo = nodo.k_child(indice);
	}
	
	for(int i = 0; i < 4; i++){	//Calculo el número de hijos del nodo en el que estoy (necesario para prune_k_child)
		if(!nodo.k_child(i).null()){
			num_hijos++;
		}
	}
	
	arb_copia.prune_k_child(nodo, num_hijos, arb_dest);	//Corto la copia del árbol por donde sea necesario
	
	switch (adn[0]) {
		case 'A':
			indice = 0;
			break;
		case 'G':
			indice = 1;
			break;
		case 'C':
			indice = 2;
			break;
		case 'T':
			indice = 3;
			break;
		default:
			break;
	}
	
	//ktree<pair<char,int>,4> arb_Nmer;
	
	//arb_Nmer.insert_k_child(arb_Nmer.root(), indice, arb_dest);	//Inserto el árbol que hemos obtenido antes
	
	devolver.el_Nmer.insert_k_child(el_Nmer.root(), indice, arb_dest);
	
	//devolver.el_Nmer = arb_Nmer;	//Lo guardo en el Nmer
	devolver.max_long = profundidadMax(el_Nmer.root());	//Guardo la longitud de la cadena más larga
	
	return devolver;
}

int Nmer::maxi(int first, int second, int third, int fourth){
	int maximo = first;
	
	if(second > maximo){
		maximo = second;
	}
	if(third > maximo){
		maximo = third;
	}
	if(fourth > maximo){
		maximo = fourth;
	}
	
	return maximo;
}

unsigned int Nmer::profundidadMax(const ktree<pair<char,int>, 4>::node nodo){
	if(nodo.null()){
		return 0;
	}
	else{
		unsigned int profA, profG, profC, profT;
		
		profA = profG = profC = profT = 0;
		
		for(int i = 0; i < 4; i++){
			switch (i) {
				case 0:
					profA += profundidadMax(nodo.k_child(i));
					break;
				case 1:
					profG += profundidadMax(nodo.k_child(i));
					break;
				case 2:
					profC += profundidadMax(nodo.k_child(i));
					break;
				case 3:
					profT += profundidadMax(nodo.k_child(i));
					break;
				default:
					break;
			}
		}
		
		return 1 + maxi(profA, profG, profC, profT);
	}
}

bool Nmer::compararNmers(ktree<pair<char,int>,4>::const_node uno, ktree<pair<char,int>,4>::const_node otro) const{
	if(uno.null()){
		return true;
	}
	
	if(otro.null()){
		return false;
	}
	
	for(int i = 0; i < 4; i++){
		if(!compararNmers(uno.k_child(i), otro.k_child(i))){
			return false;
		}
	}
	
	return true;
}

bool Nmer::included(const Nmer reference) const{
	bool incluido = false;
	
	if(max_long < reference.max_long){
		incluido = compararNmers(el_Nmer.root(), reference.el_Nmer.root());
	}
	
	return incluido;
}



































#include "conjunto.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <algorithm>
#include "mutacion.h"


using namespace std;
using namespace std::chrono;

/*functor :conjunto de mutacion decreciente por cromosoma/posicion*/
class DecrecienteChrPos{
public:
    bool operator()( const mutacion &a, const mutacion &b){
	/* también podría ser : return !(a < b)*/
 		return ( ( a.getChr() < b.getChr() ) && ( a.getPos() < b.getPos() ) );
	}
};

/*functor :conjunto de mutacion creciente por cromosoma/posicion*/
class CrecienteChrPos{
public:
    bool operator()(const mutacion &a, const mutacion &b){
	/* también podría ser : return !(a < b)*/
 		return !( ( a.getChr() < b.getChr() ) && ( a.getPos() < b.getPos() ) );
	}
};

class CrecienteID{
public:
	bool operator()(const mutacion &a, const mutacion &b){
		return (a.getID() < b.getID()); // devuelve verdadero si el ID de a precede al ID de b
	}
};

class DecrecienteID{
public:
	bool operator()(const mutacion &a, const mutacion &b){
		return !(a.getID() < b.getID()); // devuelve verdadero si el ID de a precede al ID de b
	}
};

class CrecienteEnf{
public:
	bool operator()(const enfermedad &a, const enfermedad &b){
		return (a < b);
	}
};

class DecrecienteEnf{
public:
	bool operator()(const enfermedad &a, const enfermedad &b){
		return !(a < b);
	}
};


/** @brief lee un fichero de mutaciones, linea a linea
	@param[in] s nombre del fichero
 @param[in,out] cm objeto tipo conjunto sobre el que se almacenan las mutaciones
	@return true si la lectura ha sido correcta, false en caso contrario
	*/

template <typename T, typename CMP>

bool load(conjunto<T, CMP> &  cm, const string & s) {
	ifstream fe;
	string cadena;
	high_resolution_clock::time_point start,end;
	duration<double> tiempo_transcurrido;

	cout << "Abrimos "<< s << endl;
	fe.open(s.c_str(), ifstream::in);
	if (fe.fail()){
		cerr << "Error al abrir el fichero " << s << endl;
	}
	else {
		//leo la cabecera del fichero (líneas que comienzan con #)
		do{
			getline(fe,cadena,'\n');
		}while (cadena.find("#")==0 && !fe.eof());
		
		int i = 0;

		//leo la tabla de mutaciones, una línea cada vez
		while ( !fe.eof() ){
		 	cout << "Leo:: "<< cadena << endl;
		 	// Invoco el constructor de mutación que recibe una cadena completa, la parsea y crea la mutación.
			mutacion mut = mutacion(cadena);
			// Insertar mutación en el conjunto
			cerr << "Mutacion:" << endl;
			cerr << mut << endl;

			start =  high_resolution_clock::now();;
			cerr << "Inserto la mutacion en el conjunto...";
			cm.insert(mut);

			cerr << "Mutaciones insertadas: " << cm.size() << endl;

			cerr << " Done."<<endl;
			i++;
			cerr << "Se han cargado " << i << " mutaciones" << endl;

			end =  high_resolution_clock::now();;

			tiempo_transcurrido  = duration_cast<duration<double> >(end-start);
			cout << "\nTiempo insert : "<< tiempo_transcurrido.count() << endl;

			getline(fe,cadena,'\n');
	 }
	 fe.close();
	 return true;
 } // else
	fe.close();
	return false;
}


int main(int argc, char *argv[]){

	conjunto<mutacion, CrecienteID> conjuntoMutaciones;
	string query_str;
	high_resolution_clock::time_point start,end;
	duration<double> tiempo_transcurrido;

	//Cargar las mutaciones en vectorSNPs
	load(conjuntoMutaciones, "clinvar_20160831.vcf");
	cerr << "\nload:\t hecho" << endl;
	
	vector<mutacion> prueba(conjuntoMutaciones.size());
    prueba = conjuntoMutaciones.getVM();  //Se guarda para usarlo en el método fin y erase
	//cerr << "guardar una mutacion" << endl;

	mutacion find_erase;
	//cerr << "crear una mutacion" << endl;

	find_erase = prueba[2];
	
	//cerr << "mutacion auxiliar:\t hecho" << endl;

	//Imprimir número de elementos almacenados en conjuntoMutaciones
	cout << "Lectura del fichero finalizada. Mutaciones cargadas: " << conjuntoMutaciones.size() << endl;



	//Imprimir cuántas mutaciones están asociadas al cromosoma 1:
	cout << "Mutaciones asociadas a Chr 1: " << conjuntoMutaciones.lower_bound(prueba[2]) - conjuntoMutaciones.begin() << endl;


	/**@todo ¿Existe la mutación con ID "rs147165522"? Imprimir la mutación y las enfermedades asociadas */
	/*
	cout<< "la mutación y las enfermedades asociadas con ID: rs147165522" << conjuntoMutaciones.find("rs147165522").first << " " << conjuntoMutaciones.find("rs147165522").second << endl;


	 */


	/**@todo ¿Existe la mutación en chr/pos "14"/67769578? Imprimir la mutación y las enfermedades asociadas */
	start =  high_resolution_clock::now();;

	cout<< "la mutación y las enfermedades asociadas con char:14y pos: 67769578" << conjuntoMutaciones.find(find_erase) - conjuntoMutaciones.begin() << endl;

	end =  high_resolution_clock::now();;

	tiempo_transcurrido  = duration_cast<duration<double> >(end-start);
	cout << "\nTiempo find : "<< tiempo_transcurrido.count() << endl;

	/**@todo ¿Cómo podríamos calcular el número de mutaciones del cromosoma 3? (utiliza lower_bound / upper_bound) */
	/*
	cout<< "Número de mutaciones del cromosoma 3: " << conjuntoMutaciones.upper_bound("3",0) - conjuntoMutaciones.begin() << endl;
	*/

	//////////////Prueba de erase///////////////////

	start =  high_resolution_clock::now();;

	conjuntoMutaciones.erase(find_erase);

	end =  high_resolution_clock::now();;

	tiempo_transcurrido  = duration_cast<duration<double> >(end-start);
	cout << "\nTiempo erase : "<< tiempo_transcurrido.count() << endl;

	/**@todo Analiza la eficiencia teórica y empírica de las operaciones find, insert y erase */

	return 0;
}

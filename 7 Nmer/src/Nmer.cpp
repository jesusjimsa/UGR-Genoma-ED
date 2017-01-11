#include "Nmer.h"

#include <fstream>

template<typename T, int K>
extern void recorrido_preorden(typename ktree<T,K>::const_node n);


Nmer::Nmer() {
  max_long = 0;
  el_Nmer = ktree<pair<char,int>,4>(pair<char,int>('-',0));
  
}

bool Nmer::loadSerialized(const string & fichero) {
 string cadena;
 ifstream fe;
 pair<char,int> nulo('x',-1);
 Nmer::String2Base stb;
 
 fe.open(fichero.c_str(), ifstream::in);
 if (fe.fail()){
    cerr << "Error al abrir el fichero " << fichero << endl;
 } 
 else {
    //leo la cabecera del fichero (líneas que comienzan con #)
    do{ 
      getline(fe,cadena,'\n'); 
    } while (cadena.find("#")==0 && !fe.eof());
    // leemos Nmer_length
     max_long = std::stoi(cadena);
     // leemos cadena serializada
    getline(fe,cadena,'\n');
    el_Nmer.deserialize(cadena,nulo,';',stb); 
    fe.close();
    return true;
 } // else
 fe.close();
 return false;
}
 
void Nmer::list_Nmer() const {
    // implmenentar el recorrido en preorden para el ktree de forma que nos devuelva los Nmers completos y no sólo el nodo.
      recorrido_preorden<pair<char,int>,4>(el_Nmer.root());
}
 
unsigned int Nmer::length() const {
   return max_long;
}
 
Nmer::size_type Nmer::size() const{
  return el_Nmer.size()-1;
}

 


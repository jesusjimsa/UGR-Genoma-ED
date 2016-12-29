//
//  principal.cpp
//  TDA - Clinvar
//
//  Created by Jesús Jiménez Sánchez on 7/12/16.
//  Copyright © 2016 Jesús Jiménez Sánchez. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <algorithm>
#include "mutacion.h"
#include "enfermedad.h"
#include "clinvar.h"


using namespace std;
using namespace std::chrono;

int main(int argc, char *argv[]){
	Clinvar prueba;
	Mutacion insertar("1	1806509	rspueba_insertar	T	C	.	.	RS=869312823;RSPOS=1806509;RV;dbSNPBuildID=147;SSR=0;SAO=0;VP=0x050060400a05000002100100;GENEINFO=GNB1:2782;WGT=1;VC=SNV;PM;NSM;REF;U5;ASP;LSD;CLNALLE=1;CLNHGVS=NC_000001.11:g.1806509T>C;CLNSRC=OMIM_Allelic_Variant;CLNORIGIN=33;CLNSRCID=139380.0004;CLNSIG=5|5|5|5|5|5|5|5|5;CLNDSDB=Human_Phenotype_Ontology:MedGen|Human_Phenotype_Ontology:MedGen|Human_Phenotype_Ontology:MedGen|Human_Phenotype_Ontology:MedGen|Human_Phenotype_Ontology:MedGen|Human_Phenotype_Ontology:MedGen|Human_Phenotype_Ontology:MedGen|Human_Phenotype_Ontology:MedGen|MedGen:OMIM;CLNDSDBID=HP:0011198:CN166927|HP:0011968:C0232466|HP:0001263:CN001157|HP:0001510:CN001379|HP:0008947:CN007871|HP:0001252:CN001147|HP:0001250:C1959629|HP:0000486:C0038379|CN236792:616973;CLNDBN=EEG_with_generalized_epileptiform_discharges|Feeding_difficulties|Global_developmental_delay|Growth_delay|Infantile_muscular_hypotonia|Muscular_hypotonia|Seizures|Strabismus|Mental_retardation\x2c_autosomal_dominant_42;CLNREVSTAT=no_criteria|no_criteria|no_criteria|no_criteria|no_criteria|no_criteria|no_criteria|no_criteria|no_criteria;CLNACC=RCV000210269.1|RCV000210269.1|RCV000210269.1|RCV000210269.1|RCV000210269.1|RCV000210269.1|RCV000210269.1|RCV000210269.1|RCV000225134.2");
	
	prueba.load("/Users/jesusjimsa/Dropbox (Personal)/Documentos/Universidad/2 - Primer cuatrimestre/Estructuras de Datos/Prácticas/UGR-Genoma-ED/TDA - Clinvar/Práctica 6 - Clinvar/datos/clinvar_20160831.vcf");
	
	cerr << "Carga correcta" << endl;
	
	prueba.insert(insertar);
	
	cerr << "Insercion correcta" << endl;
	
	prueba.erase("rspueba_insertar");
	
	cerr << "Borrado correcto" << endl;
	
	auto find_mut_prueba = prueba.find_Mut("rs757498880");
	
	cerr << "find mut correcto" << endl;
	
	auto find_enf_prueba = prueba.find_Enf("HP:0011198:CN166927");
	
	cerr << "find enf correcto" << endl;
	
	prueba.insert(insertar);
	auto vec_enf = prueba.getEnfermedades(insertar);
	
	cerr << "getenfermedades 1 correcto" << endl;
	
	auto list_enf = prueba.getEnfermedades("muscular");
	
	cerr << "getenfermedades 2 correcto" << endl;
	
	auto set_enf = prueba.getMutacionesEnf("HP:0011198:CN166927");
	
	cerr << "getenfermedades 3 correcto" << endl;
	
	auto set_gen = prueba.getMutacionesGen(insertar.getGenes().at(0));
	
	cerr << "getenfermedades 4 correcto" << endl;
	
	auto top = prueba.topKMutaciones(10, "Multiple_sclerosis");
	
	cerr << "topkmutaciones correcto, a imprimir :(" << endl;
	
	for(auto it = top.begin(); it != top.end(); ++it){
		cout << "TopK: " << (*it) << endl;
	}
	
	return 0;
}

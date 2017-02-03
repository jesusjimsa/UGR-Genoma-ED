//
//  prueba.cpp
//  TDA - Nmer
//
//  Created by Jesús Jiménez Sánchez on 3/2/17.
//  Copyright © 2017 Jesús Jiménez Sánchez. All rights reserved.
//

#include <iostream>
#include "Nmer.h"

#define BLACK    "\033[0m"
#define RED      "\033[31m"
#define GREEN    "\033[32m"
#define YELLOW   "\033[33m"
#define BLUE     "\033[34m"
#define MAGENTA  "\033[35m"
#define CYAN     "\033[36m"
#define WHITE    "\033[37m"

using namespace std;

int main(){
	Nmer jeje;
	
	jeje.sequenceADN(4, "ATCGTAGCTGATCGATGTATCGTAGCTGTGGGATAGTC");
	jeje.sequenceADN(4, "CTGCGTAGCTAGCAGGCGATGCGATAGCGATCGCAGATACGCAG");
	jeje.sequenceADN(4, "TAGCAGCTACGATCGACTCGATCGCAGAAGCGCGTATATAGCCTATCTCTAG");
	jeje.sequenceADN(4, "GATCGATACGGCAGCTGACCGTATCGATC");
	cout << jeje.length() << endl;
	
	cout << "\nList Nmer" << endl;
	jeje.list_Nmer();
	
	auto rare = jeje.rareNmer(3);
	auto common = jeje.commonNmer(3);
	auto level = jeje.level(3);
	
	cout << "\nRare Nmer:" << BLUE << endl;
	for(auto it = rare.begin(); it != rare.end(); ++it){
		cout << "\t" << (*it).first << endl;
		cout << "\t" << (*it).second << endl;
		
	}
	
	cout << BLACK << "\nCommon Nmer" << GREEN << endl;
	for(auto it = common.begin(); it != common.end(); ++it){
		cout << "\t" << (*it).first << endl;
		cout << "\t" << (*it).second << endl;
	}
	
	cout << BLACK << "\nLevel" << RED << endl;
	for(auto it = level.begin(); it != level.end(); ++it){
		cout << "\t" << (*it).first << endl;
		cout << "\t" << (*it).second << endl;
	}
	
	cout << BLACK;
}

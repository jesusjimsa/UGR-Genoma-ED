//
//  prueba.cpp
//  TDA - Nmer
//
//  Created by Jesús Jiménez Sánchez on 3/2/17.
//  Copyright © 2017 Jesús Jiménez Sánchez. All rights reserved.
//

#include <iostream>
#include "Nmer.h"

using namespace std;

int main(){
	Nmer jeje;
	
	jeje.sequenceADN(4, "ATCGTAGCTGATCGATGTATCGTAGCTGTGGGATAGTC");
	cout << jeje.length() << endl;
}

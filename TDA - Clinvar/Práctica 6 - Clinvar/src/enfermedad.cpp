//
//  enfermedad.cpp
//  TDA - Clinvar
//
//  Created by Jesús Jiménez Sánchez on 7/12/16.
//  Copyright © 2016 Jesús Jiménez Sánchez. All rights reserved.
//

#include <string>
#include "enfermedad.h"
#include <iostream>
#include <vector>

using namespace std;

Enfermedad::Enfermedad(){
	name = "Ninguno";
	ID = "Ninguno";
	database = "Ninguno";
}

Enfermedad::Enfermedad(const string & name, const string & ID, const string & database){
	this -> name = name;
	this -> ID = ID;
	this -> database = database;
}

void Enfermedad::setName(const string & name){
	this -> name = name;
}

void Enfermedad::setID(const string & ID){
	this -> ID = ID;
}

void Enfermedad::setDatabase(const string & database){
	this -> database = database;
}

string Enfermedad::getName() const{
	return name;
}

string  Enfermedad::getID() const{
	return ID;
}

string Enfermedad::getDatabase() const{
	return database;
}

Enfermedad & Enfermedad::operator = (const Enfermedad & e){
	if (this != &e){
		this -> ID = e.getID();
		this -> name = e.getName();
		this -> database = e.getDatabase();
	}
	
	return *this;
}

string Enfermedad::toString() const {
	return this -> name + " : " + this -> ID + "\tDB: " + this -> database + "\n";
}

bool Enfermedad::operator == (const Enfermedad & e) const{
	bool igual = false;
	
	if(this != &e){
		if(name.size() == e.name.size() && ID.size() == e.ID.size() && database.size() == e.database.size() )
			igual = true;
	}
	else
		igual = true;
	
	return igual;
}


bool Enfermedad::operator != (const Enfermedad & e) const{
	return !(this == &e);
}

bool Enfermedad::operator<(const Enfermedad & e) const {
	return (name < e.getName());
}

bool Enfermedad::nameContains(const string & str) const{
	bool dentro = false;
	
	if (str == ""){
		dentro = true;
	}
	
	if(name.find(str) != string::npos){
		dentro = true;
	}
	
	return dentro;
}

string Enfermedad::imprime_Enf() const{
	string hola;
	
	hola = getName() + " " + getID() + " " + getDatabase();
	
	return hola;
}

ostream& operator << ( ostream& os, const Enfermedad & e){
	os << e.getName() << " " << e.getID() << "\n" << e.getDatabase() << endl;
	
	return os;
}

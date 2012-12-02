/*************************************************************************
                       cAnalog  -  Analyse Log Apache
                             -------------------
    debut                : 12 nov. 2012
    copyright            : (C) 2012 par pmdartus/kchouard
*************************************************************************/

//-------------------------------------------------------- Include systeme
//#define MAP
#include <iostream>
#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "cCommande.h"
#include "cJournal.h"

int main(int argc, char *argv[]) 
{
	// Création de la classe Commande et execution de celle ci
	//cCommande LectureCmd =cCommande(argc,&*argv);
	
	cJournal Journal = cJournal("C:\\Users\\MrKim\\Documents\\GitHub\\LogApache\\Debug\\test.log", false, -1, "", 10);
	int test;
	cin >> test;
}



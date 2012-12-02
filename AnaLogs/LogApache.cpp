/*************************************************************************
                       cAnalog  -  Analyse Log Apache
                             -------------------
    debut                : 12 nov. 2012
    copyright            : (C) 2012 par pmdartus/kchouard
*************************************************************************/

//-------------------------------------------------------- Include systeme
//#define MAP
#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "cCommande.h"
#include "cJournal.h"

int main(int argc, char *argv[]) 
{
#ifdef MAP
	cJournal Journal = cJournal("C:\\Users\\MrKim\\Documents\\GitHub\\LogApache\\Debug\\test.log", 0, "C:\\Users\\MrKim\\Documents\\GitHub\\LogApache\\Debug\\test.dot");
	Journal.dispLogs();
	int test;
	cin >> test;
#else
	// Création de la classe Commande et execution de celle ci
	cCommande LectureCmd =cCommande(argc,&*argv);
#endif;
}



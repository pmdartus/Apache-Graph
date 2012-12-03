/*************************************************************************
                    LogApache - Contient le main de analogs
                             -------------------
    debut                : 12 nov. 2012
    copyright            : (C) 2012 par pmdartus/kchouard
*************************************************************************/

//-------------------------------------------------------- Include systeme
#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "cCommande.h"
#include "cJournal.h"

int main(int argc, char *argv[]) 
{
	// Création de la classe Commande et execution de celle ci
	cCommande LectureCmd = cCommande(argc,&*argv);
}



/*************************************************************************
                           cChargement  -  description
                             -------------------
    d�but                : 12 nov. 2012
    copyright            : (C) 2012 par pmdartus
*************************************************************************/

//---------- R�alisation de la classe <cChargement> (fichier cChargement.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include syst�me
#include <iostream>
#include <sstream>
#include <fstream>

//------------------------------------------------------ Include personnel
#include "cChargement.h"

//------------------------------------------------------------- Constantes
#define MAP

//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types priv�s


//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- M�thodes publiques
	
void cChargement::AddReq (string cFic)
// Algorithme :
//
{
	ifstream fic(cFic);  //Ouverture d'un fichier en lecture

	if(fic)
	{
		string ligne; //variable dans laquelle on stock chaque ligne

		while(getline(fic, ligne))  //On lit ligne par ligne
		{
			istringstream motAmot(ligne);
			string mot;
			do
			{
				motAmot >> mot;
				cout << mot << endl;
			} while (mot != "\n");
		}
	}
	else
	{
#ifdef MAP
	cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
#endif
	}
}; //----- Fin de M�thode

	
void cChargement::Disp ()
// Algorithme :
//
{
}; //----- Fin de M�thode

	
void cChargement::Graph (string cFic)
// Algorithme :
//
{
}; //----- Fin de M�thode


//-------------------------------------------- Constructeurs - destructeur


cChargement::cChargement ( bool html, int heure )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <cChargement>" << endl;
#endif

	bOptionHtml = html;
	iOptionHeure = heure;
} //----- Fin de cChargement


cChargement::~cChargement ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <cChargement>" << endl;
#endif
} //----- Fin de ~cChargement


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- M�thodes prot�g�es

//------------------------------------------------------- M�thodes priv�es

	
    void cChargement::AddReq (int idRef, int idDest, int idHeure)
	// Algorithme :
	//
	{
	}; //----- Fin de M�thode

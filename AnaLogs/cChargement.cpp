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
#include "cIndex.h"

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
	ifstream fic(cFic, ios::in);  //Ouverture d'un fichier en lecture

	if(fic)
	{
		string ligne; //variable dans laquelle on stock chaque ligne

		while(getline(fic, ligne))  //On lit ligne par ligne
		{
			//Récupération des infos bruts depuis la ligne actuelle
			istringstream ligneActuelle(ligne);
			string useless, date, action, url, referer;
			int status;
			ligneActuelle >> useless >> useless >> useless >> date >> useless >> action >> url >> useless >> status >> useless >> referer;

			if (status == 200)
			{
				//Traitement de la date
				date.erase(0,13);
				date.erase(2);
				int heure = atoi(date.c_str());
			
				//Traitement de la requete
				action.erase(0,1);
			
				//Traitement du referer
				referer.erase(0,1);
				referer.erase(referer.length()-1,1);

				//Suppression de la basse pour le referer si l'on vient du site actuel (et pas de l'extérieur)
				size_t found;
				found = referer.find("http://intranet-if.insa-lyon.fr/");
				if (found!=string::npos)
				{
					referer.replace(0,31, "");
				}

				cout << "Heure : " << date << ", Action : " << action << ", URL : " << url << ", Referer : " << referer << endl;
			}
			else
			{
				#ifdef MAP
					cout << "Statut de la requete non pris en compte." << endl;
				#endif
			}
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

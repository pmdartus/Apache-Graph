/*************************************************************************
				cChargement  -  récupère les infos depuis le .log
                             -------------------
    début                : 12 nov. 2012
    copyright            : (C) 2012 par pmdartus
*************************************************************************/

//---------- Réalisation de la classe <cChargement> (fichier cChargement.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <sstream>
#include <fstream>

//------------------------------------------------------ Include personnel
#include "cChargement.h"
#define MAP2

//------------------------------------------------------------- Constantes


//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privés


//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- Méthodes publiques
	
void cChargement::FromFile (string cFic)
// Algorithme :
//
{

	ifstream fic(cFic, ios::in);  //Ouverture d'un fichier en lecture

	if(fic)
	{
		string ligne; //variable dans laquelle on stock chaque ligne

		while(getline(fic, ligne))  //On lit ligne par ligne
		{
			//Récupération des infos bruts depuis la ligne actuelle selon un schéma précis
			istringstream ligneActuelle(ligne);
			string useless, date, action, url, referer;
			int status;
			ligneActuelle >> useless >> useless >> useless >> date >> useless >> action >> url >> useless >> status >> useless >> referer;

			//Traitement de la requete
			action.erase(0,1);

			if (status == 200 && action=="GET")
			{
				bool bFichierHtml = false;

				//Traitement de la date
				date.erase(0,13);
				date.erase(2);
				int heure = atoi(date.c_str()); //transformation en int
			
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

				// Recherche de l'accès d'un fichier html | prise en compte du fichier racine
				found = url.find(".html");
				if (found!=string::npos || url=="/")
				{
					bFichierHtml=true;
				}

				// Ajout des Url à l'index
				if (heure==iOptionHeure || iOptionHeure==-1 )
				{
					if (bOptionHtml==true)
					{
						if (bFichierHtml==true)
						{
							addReq(url, referer, heure);
						}
					}
					else
					{
						addReq(url, referer, heure);
					}
				}
			}
			else
			{
#ifdef MAP
	cout << "Statut de la requete non pris en compte : " <<status<< " | "<<action<< endl;
#endif
			}
			
		}

#ifdef MAP // Affichage des différentes adresses stockés dans l'index, et la map
	int i=2;
	//Journal.OptionNbVisite(i);
	//Journal.dispLogs();
	Journal.dispIndex();
#endif

	}
	else
	{
#ifdef MAP
	cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
#endif
	}
}; //----- Fin de Méthode


//-------------------------------------------- Constructeurs - destructeur


cChargement::cChargement ( )
// Algorithme :
//
{
#ifdef MAP
	cout << "Appel au constructeur de <cChargement>" << endl;
#endif
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

//----------------------------------------------------- Méthodes protégées

//------------------------------------------------------- Méthodes privées
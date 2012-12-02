/*************************************************************************
                   cJournal  -  gère les données à importer
                             -------------------
    début                : 12 nov. 2012
    copyright            : (C) 2012 par pmdartus
*************************************************************************/

//---------- Réalisation de la classe <cJournal> (fichier cJournal.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <sstream>
#include <fstream>

//------------------------------------------------------ Include personnel
#include "cJournal.h"
#define MAXHITS 10

//------------------------------------------------------------- Constantes


//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privés


//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- Méthodes publiques

int cJournal::dispLogs()
// Algorithme :
//
{
	//Création et initialisation de la nouvelle structure de donnée
	vReqScreenOrd vReqS; 
	vReqGraphOrd vReqG;
	orderLogs(vReqS, vReqG);

	//Affichage des requetes à l'écran
	if (sGraphizFile != "")
	{
		graphVizOutput(vReqG, vReqS, sGraphizFile);
	}
	screenOutput(vReqS);

	return 0;
}; //----- Fin de Méthode


//TODO : Refondre le schmilblik :)
void cJournal::optionNbVisite(int iNbVisite)
// Algorithme :
// 
{
	itCible=mCible.begin();

	while (itCible != mCible.end())
	{
		//Initialisation des variables de parcourt
		int aNbVisite=0;
		itReferer = (*itCible->second).begin();

		//Récupération du nombre de visite
		while (itReferer != (*itCible->second).end() )
		{
			aNbVisite=itReferer->second[24]+aNbVisite;
			++itReferer;
		}

		//Supression de la mémoire allouée dans le cas ou le nombre de visite est inférieur au nombre requis
		if (aNbVisite<iNbVisite)
		{
			itReferer=(*itCible->second).begin();
			while (itReferer != (*itCible->second).end() )
			{
				int* tableau = itReferer->second;
				(*itCible->second).erase(itReferer++);
				delete tableau;
			}

			mCible.erase(itCible++);
		}

		//Sinon passer à la cible suivante
		else
		{
			++itCible;
		}
	}
}; //----- Fin de Méthode


int cJournal::dispIndex()
// Algorithme :
//
{
	Index.disp();

	return 0;
}; //----- Fin de Méthode
	


//-------------------------------------------- Constructeurs - destructeur


cJournal::cJournal ( string cFic, int aNbHits, string aGraphizFile, bool html, int heure )
// Algorithme :
//
{
#ifdef MAP
	cout << "Appel au constructeur de <cJournal>" << endl;
#endif

	bOptionHtml = html;
	iOptionHeure = heure;
	sGraphizFile = aGraphizFile;
	iNbHits = aNbHits;
	
	fromFile (cFic);
} //----- Fin de cJournal


cJournal::~cJournal ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <cJournal>" << endl;
#endif
} //----- Fin de ~cJournal


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

void cJournal::addReq(string sCible, string sReferer, int aHeure )
// Algorithme :
//
{
	//Obtention de l'index pour les Url
	int aCible = Index.addUrl(sCible);
	int aReferer = Index.addUrl(sReferer);

	//Recherche de l'existence de la cible
	itCible=mCible.find(aCible);

	if (itCible!=mCible.end()) //La cible est déjà stockée
	{
		itReferer= (*itCible->second).find(aReferer);

		if (itReferer!=(*itCible->second).end()) //Le Referer est déjà stocké 
		{
			//On incrément la case correspondant à l'heure et au compteur total
			itReferer->second[aHeure]++;
			itReferer->second [24]++;
		}
		
		else //le referer de la cible n'existe pas
		{
			//Création et initialisation du tableau des heures
			int* aTableauHorraire = new (tableauHorraire);
			for( int i=0; i<=24; i++)
			{
				aTableauHorraire[i] =0;
			}
			aTableauHorraire[aHeure]=1;
			aTableauHorraire[24]=1;

			//insertion du tableau dans la map referer associée
			(*itCible->second).insert ( pair<int,int*>(aReferer,aTableauHorraire) );
		}
	}

	else //La cible n'existe pas 
	{
		//Création de la map referer et association avec la cible.
		mapReferer * aMapReferer = new mapReferer;

		int* aTableauHorraire = new (tableauHorraire);
		for( int i=0; i<=24; i++)
		{
			aTableauHorraire [i] =0;
		}
		aTableauHorraire[aHeure]=1;
		aTableauHorraire[24]=1;

		(*aMapReferer).insert ( pair<int,int*>(aReferer,aTableauHorraire) );

		mCible.insert(pair<int,mapReferer*>(aCible,aMapReferer));
	}
}; //----- Fin de Méthode


void cJournal::traiterReq(int heure, string referer, string url, string statut)
// Algorithme :
//
{
	//Traitement du referer
	referer.erase(0,1);
	referer.erase(referer.length()-1,1);

	//Suppression de la base pour le referer si l'on vient du site actuel (et pas de l'extérieur)
	size_t found;
	if (referer.find("http://intranet-if.insa-lyon.fr")!=string::npos)
	{
		referer.erase(0,31);
	}
	else if (referer.find("http://if.insa-lyon.fr")!=string::npos)
	{
		referer.erase(0,22);
	}

	// Ajout des Url à l'index
	if (iOptionHeure == -1 || heure==iOptionHeure )
	{
		if (bOptionHtml==true)//Optimisation pour que l'on ne cherche que quand l'option html est active
		{
			// Recherche de l'accès d'un fichier à exclure
			found = url.find(".jpg");
			if(found==string::npos)
			{
				found = url.find(".jpeg");
				if(found==string::npos)
				{
					found = url.find(".png");
					if(found==string::npos)
					{
						found = url.find(".gif");
						if(found==string::npos)
						{
<<<<<<< HEAD
							found = url.find(".ico"); 
=======
							found = url.find(".ico");
>>>>>>> cJournal
							if(found==string::npos)
							{
								found = url.find(".css");
								if(found==string::npos)
								{
									found = url.find(".js");
									if(found==string::npos)
									{
										addReq(url, referer, heure);
									}
								}
							}
						}
					}
				}
			}
		}
		else
		{
			addReq(url, referer, heure);
		}
	}
}; //----- Fin de Méthode


//TODO : traiter le gmt
string cJournal::splitLog(string aLigne, int &aHeure, string &aRequete, string &aReferer, string &aStatut)
// Algorithme :
//
{
	//Récupération des infos bruts depuis la ligne actuelle selon un schéma précis
	istringstream ligneActuelle(aLigne);
	string useless, action;
	
	char date[3];
	ligneActuelle.seekg (aLigne.find_first_of(':')+1, ios_base::beg);
	ligneActuelle>>aHeure;
	ligneActuelle.seekg (15, ios_base::cur);
	ligneActuelle >> action >> aRequete;
	ligneActuelle.seekg (10, ios_base::cur);
	ligneActuelle >> aStatut >> useless >> aReferer;

	if ((aReferer.length()>=3)&&(aStatut=="200")) 
	{
		return action;
	}
	else
	{
#ifdef MAP
cerr << "Statut de la requete non pris en compte : " <<status<< " | "<<action<< endl;
#endif
		return "";
	}
}; //----- Fin de Méthode


//TODO : try catch du père fourra sur la récupération d'une ligne + compteur d'erreur
void cJournal::fromFile (string cFic)
// Algorithme :
//
{
	ifstream fic(cFic, ios::in);  //Ouverture d'un fichier en lecture

	if(fic)
	{
		string ligne; //variable dans laquelle on stock chaque ligne

		while(getline(fic, ligne))  //On lit ligne par ligne
		{

			string sRequete, sReferer, sStatut;
			int iHeure;

			if (splitLog(ligne, iHeure, sRequete, sReferer, sStatut) == "GET")
			{
				//Ajout des données
				traiterReq(iHeure, sReferer, sRequete, sStatut);
			}
			else
			{
#ifdef MAP
	cerr << "Syntaxe de la ligne non valide"<< endl;
#endif
			}
			
		}

#ifdef MAP // Affichage des différentes adresses stockés dans l'index, et la map
	dispLogs(10);
	cout << "Lecture terminée" <<endl;
#endif

	}
	else
	{
		cerr << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
	}
}; //----- Fin de Méthode

void cJournal::screenOutput(vReqScreenOrd aReqS)
// Algorithme :
//
{
	vector<sReqScreen>::reverse_iterator it;

	it=aReqS.rbegin();
	int i=0;
	while(it!=aReqS.rend()&&(i<MAXHITS)) //tant qu'on est pas arrivé au début et on que l'on à pas affiché les 10
	{
		cout<<Index.findUrl(it->url)<< " ("<<it->nbHits<<" vue(s))"<<endl;
		it++;
		i++;
	}
}; //----- Fin de Méthode


//TODO : si existe déjà, demandé si on écrase
//TODO : vérifier que l'on écrit bien tous les nodes, et qu'une seule fois. Lister pour un total de 10 noeuds.
void cJournal::graphVizOutput(vReqGraphOrd aReqG, vReqScreenOrd aReqS, string aDot)
// Algorithme :
//
{
	mapNodes aReqNodes; //noeud déjà affichés

	//Initialisation des itérateur et autres compteurs
	vector<sReqGraph>::reverse_iterator it;
	mapNodes::iterator itNodes;
	itNodes = aReqNodes.begin();
	int i=0;
	int actualNode = 0;
	
	//Découpage du graphViz
	stringstream sNodes;
	stringstream sNodesReferer;
	stringstream sArcs;

	vector<sReqScreen>::reverse_iterator itPop;
	itPop=aReqS.rbegin();
	int iPop=0;
	//On affiche et référence les 10 noeuds les plus populaires
	while(itPop!=aReqS.rend()&&(iPop<MAXHITS))
	{
		//On teste que le noeud est bien dans aReqG
		it=aReqG.rbegin();
		for ( ;it!=aReqG.rend(); it++) if ( it->url== itPop->url) break;

		if (it!=aReqG.rend())
		{
			sNodes<<"node"<<itPop->url<<" [label=\""<<Index.findUrl(itPop->url)<<"\"];"<<endl;
			aReqNodes.insert ( pair<int,bool>(itPop->url,true) );
			iPop++;
		}
		itPop++;
	}
	
	it=aReqG.rbegin();
	while(it!=aReqG.rend()) //parcours des noeuds graphViz
	{
		itNodes= aReqNodes.find(it->url);
		if ((itNodes!=aReqNodes.end())&&(itNodes->second)) //Le noeud existe et fait partit des 10 plus vus
		{
			itNodes= aReqNodes.find(it->referer);
			if (itNodes==aReqNodes.end()) //Le noeud referer n'a jamais été écrit
			{
				sNodesReferer<<"node"<<it->referer<<" [label=\""<<Index.findUrl(it->referer)<<"\"];"<<endl;
				aReqNodes.insert ( pair<int,bool>(it->referer,false) );
			}

			sArcs<<"node"<<it->referer<<" -> node"<<it->url<<" [label=\""<<(it->nbHits)<<"\"];"<<endl;
		}

		it++;
	}
	
	ofstream graphFile;
	graphFile.open(aDot, ios::out | ios::trunc);

	if (graphFile.is_open())
	{
		graphFile<<"digraph {"<<endl;
		graphFile<<sNodes.str()<<endl<<sNodesReferer.str()<<endl<<sArcs.str()<<endl;
		graphFile<<"}"<<endl;

		graphFile.close();
		cout<<"Dot-file "<<aDot<<" generated."<<endl;
	}
	else
	{
		cerr<<"Impossible d'écrire dans le fichier"<<endl;
	}
}; //----- Fin de Méthode

//TODO : optimiser si que 10 à afficher !!!
int cJournal::orderLogs(vReqScreenOrd &aReqS, vReqGraphOrd &aReqG)
// Algorithme :
//
{
	itCible=mCible.begin();

	while (itCible != mCible.end())
	{
		//Initialisation des variables de parcours
		int iNbVisite=0;
		int iActualVisites=0;
		itReferer = (*itCible->second).begin();

		//Récupération du nombre de visite
		while (itReferer != (*itCible->second).end() )
		{
			iActualVisites=itReferer->second[24];
			iNbVisite+=iActualVisites;

			//ajout d'une requete dans la structure le fichier graphfiz
			if (  (iNbHits==0)				//on a pas l'option -i
			    ||(iActualVisites>=iNbHits)) //ou on est dans la bonne fourchette de l'option -i
			{
				aReqG.push_back( sReqGraph(itCible->first, itReferer->first, iActualVisites) );
			}

			++itReferer;
		}

		//ajout d'une requete dans la structure pour la sortie à l'écran
		aReqS.push_back( sReqScreen(itCible->first, iNbVisite) );

		++itCible;
	}
	
	//tri des requetes
	sort(aReqS.begin(),aReqS.end());
	sort(aReqG.begin(),aReqG.end());

	return 0;
}; //----- Fin de Méthode

//------------------------------------------------------- Méthodes privées

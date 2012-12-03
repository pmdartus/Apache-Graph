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
// Crée les structures de données propre à la sortie.
// Execute ensuite les fonctions de sortie, selon les paramètres envoyés (-g ou non).
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


int cJournal::dispIndex()
// Algorithme :
// Trivial.
{
	Index.disp();

	return 0;
}; //----- Fin de Méthode
	


//-------------------------------------------- Constructeurs - destructeur


cJournal::cJournal ( string cFic, int aNbHits, string aGraphizFile, bool html, int heure )
// Algorithme :
// Transfert des paramètres de la fonction dans les attributs de la classe
// Puis chargement du fichier .log
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
// Détruit toutes les allocations mémoires dues au pointeurs.
{
#ifdef MAP
    cout << "Appel au destructeur de <cJournal>" << endl;
#endif
	
} //----- Fin de ~cJournal


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

void cJournal::addReq(string sCible, string sReferer, int aHeure )
// Algorithme :
// Voila l'algorithme détaillé :
// FONCTION addRq ( sCible, sReferer : chaine de caractère, aHeure : entier ) : RETOURNE rien
// DEBUT
// |     entier indexCible = Index.ajouterUrl (sCible)
// |     entier indexReferer = Index.ajouterUrl (sReferer)
// |
// |     iterateurCible = mapCible.trouver(indexCible)
// |
// |     SI (iterateur.trouver)
// |     |     iterateurReferer=mapCible->mapReferer.trouver(indexReferer)
// |     |
// |     |     SI (iterateurReferer.trouver)
// |     |     |     iterateurReferer->tableauHoraire[aHeure]=tableauHorraire[aHeure]+1
// |     |     |     iterateurReferer->tableauHoraire[24]=tableauHorraire[24]+1
// |     |     SINON
// |     |     |     creer TableauHorraire 
// |     |     |     TableauHorraire[24]=1      
// |     |     |     TableauHorraire[aHeure]=1    
// |     |     |     inserer dans mapCible->mapReferer(sReferer, TableauHorraire)
// |     |     FINSI
// |     SINON
// |     |     creer mapReferer
// |     |     creer TableauHoraire
// |     |     TableauHorraire[24]=1      
// |     |     TableauHorraire[aHeure]=1    
// |     |     inserer dans mapReferer (sReferer, TableauHorraire)
// |     |     inserer dans mapCible (mapReferer)
// |     FINSI
// FIN
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
// Traitement du referer avec suppression des " et des bases http:// du type intranet-if... et if.insa... pour avoir une cohérence dans les nom de noeuds.
// Ajout des données dans la map grace à la fonction addReq, si le log respècte les paramètres de la commande.
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
			// Si le fichier n'est pas un fichier à eclure.
			if ((url.find(".jpg")==string::npos)&&(url.find(".jpeg")==string::npos) && (url.find(".png")==string::npos) && (url.find(".gif")==string::npos) && (url.find(".ico")==string::npos) //images
				&& (url.find(".css")==string::npos) //css
				&& (url.find(".js")==string::npos)) //js
			{
				addReq(url, referer, heure);
			}
		}
		else
		{
			addReq(url, referer, heure);
		}
	}
}; //----- Fin de Méthode


string cJournal::splitLog(string aLigne, int &aHeure, string &aRequete, string &aReferer, string &aStatut)
// Algorithme :
// Utilise un stringstream pour parcourir la ligne. 
// Fait appelle à la recherche find_first_of pour se placer au bon endroit dans le cas de l'heure, de la requete et du statut. Cela permet de gagner en efficacité.
// Pour le referer, stocke d'abord le mot inutile situé entre aStatut et aReferer dans une variable tampon appellé useless. Nécessaire car taille du mot inutile variable.
// Vérifie la cohérence des données recu, puis on renvoie l'action si c'est bon.
// Sinon on affiche une erreur et on renvoie une chaine vide.
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
	//aStatut.erase(1,(aStatut.length()>=3)?2:0);

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


void cJournal::fromFile (string cFic)
// Algorithme :
// Démarre la lecture du .log.
// Si on peut lire le fichier : on split puis traite chaque ligne, en indiquant lorsque la ligne est invalide.
// Sinon on signale que le fichier n'est pas accessible.
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
// Parcours inversé sur 10 éléments de la structure crée par orderLogs pour afficher l'id des 10 plus pages les plus accédés.
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


void cJournal::graphVizOutput(vReqGraphOrd aReqG, vReqScreenOrd aReqS, string aDot)
// Algorithme détaillé :
// FONCTION graphVizOutput(aReqG : vReqGraphOrd, aReqS : vReqScreenOrd, aDot : chaine de caracère ) RETOURNE rien
// DEBUT
// |     créer mapNodes
// |     
// |     TANT QUE iterateurTop10 DANS aReqS
// |     |     SI iterateurTop10 DANS vReqGraphOrd
// |     |     |     insérer noeud[iterateurTop10->url] DANS ficher.dot COULEUR bleu clair
// |     |     |     insérer couple[iterateurTop10->idUrl, true] DANS mapNodes
// |     |     FINSI
// |     FIN TANT QUE
// |     
// |     TANT QUE iterateurGraph DANS aReqG
// |     |     SI (iterateurGraph->idUrl DANS mapNodes->clé) ET mapNodes->attribut EST true
// |     |     |     SI iterateurGraph->idReferer PAS DANS mapNodes->clé
// |     |     |     |     insérer noeud[iterateurGraph->idUrl] DANS fichier.dot COULEUR blanc
// |     |     |     |     insérer couple[iterateurGraph->idUrl, false] DANS mapNodes
// |     |     |     FINSI
// |     |     |     
// |     |     |     insérer arc[iterateurGraph->url , iterateurGraph->referer] DANS fichier.dot
// |     |     FIN SI
// |     FIN TANT QUE
// FIN
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
			sNodes<<"node"<<itPop->url<<" [label=\""<<Index.findUrl(itPop->url)<<"\",fillcolor=\"dodgerblue1\", style=\"filled,rounded\"];"<<endl;
			aReqNodes.insert ( pair<int,bool>(itPop->url,true) );
			iPop++;
		}
		itPop++;
	}
	
	it=aReqG.rbegin();
	while(it!=aReqG.rend()) //parcours des noeuds graphViz
	{
		itNodes= aReqNodes.find(it->url);
		if ((itNodes!=aReqNodes.end())&&(itNodes->second)) //Le noeud est dans le top 10
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


int cJournal::orderLogs(vReqScreenOrd &aReqS, vReqGraphOrd &aReqG)
// Algorithme :
// Parcours des maps contenant les infos des .logs.
// Pour chaque couple cible/referer, ajouts des infos dans la structure vReqGraphOrd, si cohérent avec l'option. Puis ajout du nombre de visites à la somme totale.
// Pour chaque cible, ajout des infos dans la structure vReqScreenOrd.
// Tri des 2 vecteurs à la fin du parcours (possible grace à la surchage du symbole < dans chaque structure.
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
			if (  (iNbHits==0)				//on a pas l'option -l
			    ||(iActualVisites>=iNbHits)) //ou on est dans la bonne fourchette de l'option -l
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

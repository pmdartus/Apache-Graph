/*************************************************************************
               cCommande  -  gère le lancement de la commande
                             -------------------
    début                : 12 nov. 2012
    copyright            : (C) 2012 par pmdartus
*************************************************************************/

//---------- Réalisation de la classe <cCommande> (fichier cCommande.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "cCommande.h"
#include "cJournal.h"

//------------------------------------------------------------- Constantes
//#define MAP


//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privés


//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- Méthodes publiques

//-------------------------------------------- Constructeurs - destructeur

//TODO : option -h pour afficher l'aide + le dire quand on propose une solution intelligente
cCommande::cCommande(int aNbArg,char ** aCommande)
// Algorithme :
//
{
#ifdef MAP
	cout << "Appel au constructeur de <cCommande>" << endl;
#endif
	
	bSyntaxError = false;
	bOptionHtml = false; 
	iOptionHeure = -1;
	iNbHit=0;
	nbArg=aNbArg;
	cmd=aCommande;

	exploitCmd();
}; //----- Fin de cCommande

cCommande::~cCommande(void)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <cCommande>" << endl;
#endif
}; //----- Fin de ~cCommande


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

bool cCommande::isaNumber (string str)
// Algorithme :
// Lecture de la string charactère / charactère et vérification si c'est un digit ou non
{
	for (int i = 0; i < str.length(); i++) 
	{
		if (!isdigit(str[i]))
		return false;
   }
	return true;
}; //----- Fin de Méthode


bool cCommande::parameterT (string aParameter)
// Algorithme :
// Verification de la paramètre suivant est un nombre
// Convertion de la string en int et vérification que l'heure est valide
{
	if(!isaNumber(aParameter))
	{
		cerr << "SYNTAXE ERROR : Le format n'est pas un nombre "<<endl;
		return true;
	}
	else 
	{
		iOptionHeure = atoi(aParameter.c_str());

		if (iOptionHeure < 0 || iOptionHeure>=24)
		{
			cerr<<"SYNTAXE ERROR : Format de l'heure non valide"<<endl;
			return true;
		}
	}
	return false;
}; //----- Fin de Méthode


bool cCommande::parameterL (string aParameter)
// Algorithme :
// Verification de la paramètre suivant est un nombre
// Convertion de la string en int et vérification que le nombre de hit est valide
{
	if(!isaNumber(aParameter))
	{
		cerr << "SYNTAXE ERROR : Le nombre de Hits n'est pas un nombre "<<endl;
		return true;
	}
	else
	{
		iNbHit = atoi(aParameter.c_str());

		if (iNbHit<0)
		{
			cerr << "SYNTAXE ERROR : le nombre de Hit est invalide : "<<endl;
			return true;
		}
	}

	return false;
}; //----- Fin de Méthode


bool cCommande::parameterG (string aFileName)
// Algorithme :
// Verification de la paramètre suivant est bien un fichier .dot
// Puis stockage du nom du fichier dans une varialbe locale
{
	size_t found;
	found = aFileName.find(".dot");

	if (found!=string::npos)
	{
		aGraphizFile=aFileName;
	}

	else
	{
		cerr << "SYNTAX ERROR: Le fichier de stockage du Graphiz n'est pas un .dot : "<<aFileName<<endl;
		return true;
	}
	return false;
}; //----- Fin de Méthode


void cCommande::gestionErreur (string aParameter)
// Algorithme :
// Recherche de commande connus pour proposer à l'utilisateur un correction intelligente
{
	if (aParameter.find("-t")!=string::npos)
	{
		cout<<"		Vous voulez dire : -t [heure]"<<endl;
	}

	else if (aParameter.find("-g")!=string::npos)
	{
		cout<<"		Vous voulez dire : -g [nomFichier.dot]"<<endl;
	}

	else if (aParameter.find("-l")!=string::npos)
	{
		cout<<"		Vous voulez dire : -l [nombreHits]"<<endl;
	}
}; //----- Fin de Méthode


void cCommande::cRCmd ()
// Algorithme :
{
	string OptionHtml;
	if(bOptionHtml) {
		OptionHtml="Prise en compte des fichier Html";
	} else {
		OptionHtml="Prise en compte de tous les fichier";
	}
				
	string OptionHeure;
	if(iOptionHeure==-1) {
		OptionHeure="Connection a toute les heures";
	} else {
		OptionHeure="Connection entre : "+to_string(iOptionHeure)+" h ";
	}


	string OptionHit = "Nb de hits nim : "+to_string(iNbHit);

	string OptionGraphiz;
	if (aGraphizFile.size()!=0) {
		OptionGraphiz="Creation d'un fichier Graphiz :"+aGraphizFile;
	} else {
		OptionGraphiz="Sans creation de fichier graphiz";
	}

	cout<<"Lecture du fichier de log :"<<aLogFile<<" avec les option :"<<endl;
	cout<<OptionHtml<<endl;
	cout<<OptionHeure<<endl;
	cout<<OptionHit<<endl;
	cout<<OptionGraphiz<<endl<<endl;
}; //----- Fin de Méthode

//TODO: débug ^^
bool cCommande::verifyDotFile ()
// Algorithme :
{
	ifstream fic(aGraphizFile);

	if(fic)
	{
		cout<<"Le fichier "<<aGraphizFile<<" existe deja vouslez vous l'effacer ? [O/N]";

		char  input;
		do
		{
			cin>>input;
		}
		while ( !cin.fail() && input!='O' && input!='N' );

		fic.close();

		if (input =='O')
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		return false;
	}

}



bool cCommande::exploitCmd()
// Algorithme :
// Lecture des paramètre, paramètre par paramètre jusque le fin
// Suivant le paramètre en cour appeler la fonction spécifique au traitement de celle ci
// Ou envoyer un message d'erreur du fait que le syntaxe n'est pas bonne
// Dans le cas contraire créer le cJournal pour commencer le sotckage des données pour le traitement

{
	int i=1;

	while (i<(nbArg) && bSyntaxError== false)
	{
		string aParameter = cmd[i];

		// ------------------ Récupère le chemin du fichier log (dernier argument) ------------------
		size_t found;
		found=aParameter.find(".log");
		if (found!=string::npos)
		{
			aLogFile=aParameter;

			if (i!=nbArg-1)
			{
				bSyntaxError = true;
				cout << "SYNTAX ERROR : Le fichier Log est le dernier parametre de la commande"<<endl;
			}
		}

		// ------------------ Récupère les info pour le Graphiz ( -g ) ------------------
		else if (aParameter == "-g" && aGraphizFile.size()==0)
		{
			bSyntaxError=parameterG (cmd[i+1]);
			if (!bSyntaxError)
			{
				bSyntaxError= verifyDotFile();

				if (!bSyntaxError)
				{
					i++;
				}
			}
		}

		// ------------------ Récupère les info pour le nombre de Hit ( -l )------------------
		else if (aParameter == "-l" && iNbHit==0)
		{
			bSyntaxError=parameterL (cmd[i+1]);
			if (!bSyntaxError)
			{
				i++;
			}
		}

		// ------------------ Eclusion de du Html ( -x )------------------
		else if (aParameter == "-x")
		{
			bOptionHtml=true;
		}

		// ------------------ Prise en compte de l'heure ( -t )------------------
		else if (aParameter == "-t" && iOptionHeure==-1)
		{
			bSyntaxError=parameterT (cmd[i+1]);
			if (!bSyntaxError)
			{
				i++;
			}
		}

		else
		{
			cerr << "Invalid Parameter n : "<< cmd[i]<<endl;
			gestionErreur(aParameter);
			bSyntaxError=true;
		}
		
		i++; // Passage au parametre suivant
	}

	// Verifier que si l'on appel l'option -l, on appelle aussi l'option -g
	if ((aGraphizFile.size()==0) && (iNbHit!=0))
	{
		bSyntaxError=true;
		cerr<<"SYNTAXE ERROR : il l'option -l n'est accessible qu'avec l'option -g"<<endl;
	}

	if (aLogFile.size()==0 && bSyntaxError==false)
	{
		bSyntaxError=true;
		cerr<<"SYNTAXE ERROR : Veuillez entrer un fichier log"<<endl;
	}


	// Gestion des cas de retour
	if (bSyntaxError == false)
	{
		#ifdef MAP
			cRCmd ();
		#endif

		cJournal Journal = cJournal(aLogFile, iNbHit, aGraphizFile, bOptionHtml, iOptionHeure );
		Journal.dispLogs();
	}
	else
	{
		cout<<"Execution Aborted."<<endl;
		return 0;
	}

	return 0;
}; //----- Fin de Méthode


//------------------------------------------------------- Méthodes privées



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
	// Stockage de ce paramètre dans un attribut de la classe.
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
// Convertion de la string en int et vérification que le nombre de hit est valide.
// Stockage de ce paramètre dans un attribut de la classe.
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
			cerr << "SYNTAXE ERROR : le nombre de Hits est invalide : "<<endl;
			return true;
		}
	}

	return false;
}; //----- Fin de Méthode


bool cCommande::parameterG (string aFileName)
// Algorithme :
// Verification que le paramètre suivant est bien un fichier .dot
// Puis stockage du nom du fichier dans un attribut de la classe
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


bool cCommande::parameterH ()
// Algorithme :
// Chargement de man.txt puis affichage s'il existe. Renvoie ensuite true.
// Renvoie false si le fichier n'existe pas.
{
	ifstream fic("man.txt", ios::in);  //Ouverture d'un fichier en lecture

	if(fic)
	{
		string ligne; //variable dans laquelle on stock chaque ligne

		while(getline(fic, ligne))  //On lit ligne par ligne
		{
			cout<<ligne<<endl;
		}

		return true;
	}
	else
	{
		return false;
	}
}; //----- Fin de Méthode


void cCommande::gestionErreur (string aParameter)
// Algorithme :
// Recherche de morceaux de commandes connues grace à find() (recherche de caractères), pour proposer à l'utilisateur un correction intelligente
{
	if ((aParameter.find("-t")!=string::npos)||(aParameter.find("t")!=string::npos)||(aParameter.find("h")!=string::npos))
	{
		cout<<"		Vous vouliez dire : -t [heure] ?"<<endl;
	}

	if ((aParameter.find("-g")!=string::npos)||(aParameter.find("g")!=string::npos)||(aParameter.find(".dot")!=string::npos))
	{
		cout<<"		Vous vouliez dire : -g [nomFichier.dot] ?"<<endl;
	}

	if ((aParameter.find("-l")!=string::npos)||(aParameter.find("l")!=string::npos)||(aParameter.find("hit")!=string::npos))
	{
		cout<<"		Vous vouliez dire : -l [nombreHits] ?"<<endl;
	}

	cout<<"Pour plus d'informations, affichez l'aide : analogs -h"<<endl;
}; //----- Fin de Méthode


void cCommande::cRCmd ()
// Algorithme :
// Pour chaque option, stock sa situation dans une string après un test.
// Retourne toutes les strings à la fin.
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

	string OptionHit = "Nb de hits min : "+to_string(iNbHit);

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


bool cCommande::verifyDotFile ()
// Algorithme :
// Essaye de lire le fichier. 
// S'il y arrive, demande à l'utilisateur s'il veut écraser le fichier.
//		Boucle jusqu'à avoir une réponse valide.
//		Si oui, cad la commande o ou O, il renvoie true.
//		sinon false.
// Sinon renvoie false (le fichier n'existe pas).
{
	ifstream fic(aGraphizFile);

	if(fic)
	{
		cout<<"Le fichier "<<aGraphizFile<<" existe deja voulez-vous l'effacer ? [O/N]";

		char  input;
		do
		{
			cin>>input;
		}
		while ( !cin.fail() && (input!='O'||input!='o') && (input!='N'||input!='n') );

		fic.close();

		if (input =='O'||input == 'o')
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
// Lecture des paramètres, paramètre par paramètre jusqu'au dernier
// Suivant le paramètre en cours, appelle la fonction spécifique au traitement de celle ci
// Ou envoye un message d'erreur du fait que le syntaxe n'est pas bonne. Il s'en suit une proposition de correction intelligente.
// Si -h comme paramètre, affiche l'aide contenu dans le fichier man.txt situé dans le dossier de l'exécutable.
// Dans le cas contraire et s'il l'utilisateur à bien spécifié un .log, créer le cJournal pour commencer le stockage des données pour le traitement
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

		// ------------------ Affichage du manuel (-h) ------------------
		else if (aParameter == "-h")
		{
			bSyntaxError=parameterH ();
			if (!bSyntaxError)
			{
				return 0;
			}
			else
			{
#ifdef MAP
	cerr << "Impossible de charger le manuel. Il doit y avoir man.txt dans le même dossier que l'exécutable."<< endl;
#endif
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

	//Vérifier le paramètre obligatoire : .log
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
		cerr<<"Execution Aborted."<<endl;
		return 0;
	}

	return 0;
}; //----- Fin de Méthode


//------------------------------------------------------- Méthodes privées



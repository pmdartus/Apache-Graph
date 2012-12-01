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
#include "cJournal.h"

//---------------------------------isaNumber---------------------------------
bool isaNumber (string str)
{
	for (int i = 0; i < str.length(); i++) 
	{
		if (!isdigit(str[i]))
		return false;
   }
	return true;
}

//---------------------------------Parametre -t---------------------------------
bool parameterT (string aParameter, int & aHeure)
{
	if(!isaNumber(aParameter))
	{
		cerr << "SYNTAXE ERROR : Le format n'est pas un nombre "<<endl;
		return true;
	}
	else 
	{
		aHeure = atoi(aParameter.c_str());

		if (aHeure < 0 || aHeure>=24)
		{
			cerr<<"SYNTAXE ERROR : Format de l'heure non valide"<<endl;
			return true;
		}
	}
	return false;
}

//---------------------------------Parametre -l---------------------------------
bool parameterL (string aParameter, int & aNbHit)
{
	if(!isaNumber(aParameter))
	{
		cerr << "SYNTAXE ERROR : Le nombre de Hits n'est pas un nombre "<<endl;
		return true;
	}
	else
	{
		aNbHit = atoi(aParameter.c_str());

		if (aNbHit<0)
		{
			cerr << "SYNTAXE ERROR : le nombre de Hit est invalide : "<<endl;
			return true;
		}
	}

	return false;
}

//---------------------------------Parametre -g---------------------------------
bool parameterG (string aFileName, string & aGraphizFile)
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
}

//---------------------------------gestionErreur---------------------------------
void gestionErreur (string aParameter)
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
}

//---------------------------------cRCmd---------------------------------
void cRCmd (bool bOptionHtml, int iOptionHeure, string aGraphizFile, int iNbHit, string aLogFile)
{
	string OptionHtml;
	if(bOptionHtml) {
		OptionHtml="Prise en compte des fichier Html";
	} else {
		OptionHtml="Prise en compte de tout les fichier";
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
	}

//---------------------------------main---------------------------------
int main(int argc, char *argv[]) {

	int i = 1;
	bool bSyntaxError = false;
	bool bOptionHtml = false; //booleen qui indique la nécessité de ne considérer que le HTML
	int iOptionHeure = -1; //integer qui indique la présence d'une tranche horaire
	int iNbHit=0; //integer qui représente le nb de hit minimum
	string aLogFile; //nom du fichier log
	string aGraphizFile; // nom du fichier graphiz
	


	/* Parcour de la liste des arguments avec argc arguments
	 * Le parcourt s'arrète au moment ou il trouve une erreur
	 */
	while (i<(argc) && bSyntaxError== false)
	{
		string aParameter = argv[i];

		// ------------------ Récupère le chemin du fichier log (dernier argument) ------------------
		size_t found;
		found=aParameter.find(".log");
		if (found!=string::npos)
		{
			aLogFile=aParameter;

			if (i!=argc-1)
			{
				bSyntaxError = true;
				cout << "SYNTAX ERROR : Le fichier Log est le dernier parametre de la commande"<<endl;
			}
		}

		// ------------------ Récupère les info pour le Graphiz ( -g ) ------------------
		else if (aParameter == "-g" && aGraphizFile.size()==0)
		{
			bSyntaxError=parameterG (argv[i+1], aGraphizFile);
			if (!bSyntaxError)
			{
				i++;
			}
		}

		// ------------------ Récupère les info pour le nombre de Hit ( -l )------------------
		else if (aParameter == "-l" && iNbHit==0)
		{
			bSyntaxError=parameterL (argv[i+1], iNbHit);
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
			bSyntaxError=parameterT (argv[i+1], iOptionHeure);
			if (!bSyntaxError)
			{
				i++;
			}
		}

		else
		{
			cerr << "Invalid Parameter n : "<< argv[i]<<endl;
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
			cRCmd (bOptionHtml,iOptionHeure, aGraphizFile, iNbHit, aLogFile);
		#endif

		cJournal Journal = cJournal(aLogFile, bOptionHtml, iOptionHeure, aGraphizFile);
	}
	else
	{
		cout<<"Execution Aborted."<<endl;
		return 0;
	}

	return 0;
}



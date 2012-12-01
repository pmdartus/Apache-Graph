#define MAP
#include <iostream>
#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;


#include "cCommande.h"
#include "cJournal.h"

bool cCommande::isaNumber (string str)
{
	for (int i = 0; i < str.length(); i++) 
	{
		if (!isdigit(str[i]))
		return false;
   }
	return true;
}

bool cCommande::parameterT (string aParameter)
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
}


bool cCommande::parameterL (string aParameter)
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
}


bool cCommande::parameterG (string aFileName)
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


void cCommande::gestionErreur (string aParameter)
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


void cCommande::cRCmd ()
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

bool cCommande::exploitCmd()
{
	int i=1;

	while (i<(nbArg) && bSyntaxError== false)
	{
		string aParameter = cmd[i];

		// ------------------ R�cup�re le chemin du fichier log (dernier argument) ------------------
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

		// ------------------ R�cup�re les info pour le Graphiz ( -g ) ------------------
		else if (aParameter == "-g" && aGraphizFile.size()==0)
		{
			bSyntaxError=parameterG (cmd[i+1]);
			if (!bSyntaxError)
			{
				i++;
			}
		}

		// ------------------ R�cup�re les info pour le nombre de Hit ( -l )------------------
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

		cJournal Journal = cJournal(aLogFile, bOptionHtml, iOptionHeure, aGraphizFile);
	}
	else
	{
		cout<<"Execution Aborted."<<endl;
		return 0;
	}

	return 0;
}

cCommande::cCommande(int aNbArg,char ** aCommande)
{
	bSyntaxError = false;
	bOptionHtml = false; 
	iOptionHeure = -1;
	iNbHit=0;
	nbArg=aNbArg;
	cmd=aCommande;

	exploitCmd();
}

cCommande::~cCommande(void)
{
}

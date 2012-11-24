#include "cJournal.h"

void cJournal::addReq(int aCible, int aReferer, int aHeure)
{
	itCible=mCible.find(aCible);

	if (itCible!=mCible.end()) //Si on a déjà une map de referer
	{
		itReferer=itCible->second.find(aReferer);

		if (itReferer!=itCible->second.end()) //Si on a aussi le referer
		{
			//On incrément la case correspondant à l'heure et au compteur total
			itReferer->second [aHeure]++;
			itReferer->second [24]++;
			cout<<"incremantation d'un tableau horaire existant"<<endl;
		}
		
		else
		{
			//Création et initialisation du tableau des heures
			int * aTableauHorraire = new (tableauHorraire);
			for( int i=0; i=24; i++)
			{
				aTableauHorraire [i] =0;
			}
			aTableauHorraire[aHeure]=1;

			itCible->second.insert ( pair<int,int*>(aReferer,aTableauHorraire) );

			cout<<"ajout d'une nouvelle Map de referer"<<endl;
		}
	}

	else //Si on à pas encore une map de referer
	{
		//Création de la map referer et association avec la cible.
		mapReferer aMapReferer;

		int * aTableauHorraire = new (tableauHorraire);
		for( int i=0; i==24; i++)
		{
			aTableauHorraire [i] =0;
		}
		aTableauHorraire[aHeure]=1;

		aMapReferer.insert ( pair<int,int*>(aReferer,aTableauHorraire) );

		mCible.insert(pair<int,mapReferer>(aCible,aMapReferer));

		cout<<"Ajout d'un nouvelle adresse"<<endl;

	}
}

cJournal::cJournal(void)
{
}


cJournal::~cJournal(void)
{
}

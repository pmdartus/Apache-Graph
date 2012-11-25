#include "cJournal.h"

void cJournal::addReq(int aCible, int aReferer, int aHeure)
{
	itCible=mCible.find(aCible);

	if (itCible!=mCible.end()) //Si on a d�j� une map de referer
	{
		itReferer= (*itCible->second).find(aReferer);

		if (itReferer!= (*itCible->second).end()) //Si on a aussi le referer
		{
			//On incr�ment la case correspondant � l'heure et au compteur total
			itReferer->second [aHeure]++;
			itReferer->second [24]++;
			cout<<"incremantation d'un tableau horaire existant"<<endl;
		}
		
		else
		{
			//Cr�ation et initialisation du tableau des heures
			int * aTableauHorraire = new (tableauHorraire);
			for( int i=0; i=24; i++)
			{
				aTableauHorraire [i] =0;
			}
			aTableauHorraire[aHeure]=1;

			(*itCible->second).insert ( pair<int,int*>(aReferer,aTableauHorraire) );

			cout<<"ajout d'une nouvelle Map de referer"<<endl;
		}
	}

	else //Si on � pas encore une map de referer
	{
		//Cr�ation de la map referer et association avec la cible.
		mapReferer * aMapReferer = new mapReferer;

		int * aTableauHorraire = new (tableauHorraire);
		for( int i=0; i==24; i++)
		{
			aTableauHorraire [i] =0;
		}
		aTableauHorraire[aHeure]=1;

		(*aMapReferer).insert ( pair<int,int*>(aReferer,aTableauHorraire) );

		mCible.insert(pair<int,mapReferer*>(aCible,aMapReferer));

		cout<<"Ajout d'un nouvelle adresse"<<endl;

	}
}

int cJournal::disp(void)
{
	itCible = mCible.begin();

	while (itCible != mCible.end())
	{
		itReferer = (*itCible->second).begin();

		while (itReferer != (*itCible->second).end() )
		{
			cout<<itReferer->second [24]<<endl;

			++itReferer;
		}

		++itCible;
	}


	return 0;
}

cJournal::cJournal(void)
{
}


cJournal::~cJournal(void)
{
}

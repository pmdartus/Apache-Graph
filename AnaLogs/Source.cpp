#include "cChargement.h"
using namespace std;
#include <iostream>

int mainOFF() 
{
	cChargement chargement = cChargement(false, -1);

	chargement.AddReq("test.log");

	int fin;
	cin>>fin;

	return 5;
};
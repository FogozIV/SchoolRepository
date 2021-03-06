//Honnêtement : c'est pas ouf X) Mais ça donne des idées

#include <iostream>
#include <string>
#include <ctime>
using namespace std;
void gameloop(int &nn, int &nv, int &nt, bool is_rand);
int askPickBall(int &nn, int &nv, int &nt, bool is_rand);
string getColorFromCode(int code);
int main()
{
	bool is_auto = true;
	srand(time(0)); //random seed
	int nn = 0, nv = 0, nt = 0; //Nombre de boule noire, Nombre de boule verte
	cout << "Voulez vous activer la selection automatique ? Entrez 0 pour non et 1 ou autre chiffre pour oui !" << endl; //To select weither it should be automatic or not
	int tmp; //Idk if it's necessary
	cin >> tmp; 
	is_auto = (tmp != 0);
	while (nn < 1 || nn >19) {
		cout << "Veuillez entrer le nombre de boule noire : "; //Loop that ask valid amount of balls
		cin >> nn;
		cout << endl;
	}
	while (nv < 1 || nv > 20 - nn) { //Loop that as valid amount of balls
		cout << "Veuillez entrer le nombre de boule verte : ";
		cin >> nv;
		cout << endl;
	}
	nt = nn + nv; //calculate the total amount of balls
	cout << "Il y a " << nn << " boules noires," << "\n" << nv << " boules vertes \net donc " << nt << " boules au total." << endl;
	for (int l = nt; l > 1; l--) { //loop that will itterate a given number of times proportional to the amount of balls
		gameloop(nn, nv, nt, is_auto); //Function working with pointeurs so that we can edit the value
	}
	cout << "Il reste uniquement une boule " << getColorFromCode(nv == 0) << endl; //Only to tell the final balls
	system("pause");
	return EXIT_SUCCESS;
}
//The code call when it loops it could be put in the loop but it's there to increase visibility not efficiency
void gameloop(int &nn, int &nv, int &nt, bool is_rand) {
	bool picked = false;
	int fPick = askPickBall(nn, nv, nt, is_rand); //first pick
	int sPick = askPickBall(nn, nv, nt, is_rand); //second pick
	nt++;
	if (fPick == sPick) {
		nn++;
	}
	else {
		nv++;
	}
	cout << "Vous avez tirer une boule " << getColorFromCode(fPick) << " et une boule " << getColorFromCode(sPick) << ". Donc une boule " << getColorFromCode((fPick == sPick) ? 1 : 0) << " a \x82" <<"t\x82 ajout\x82" <<"e." << endl; //Long line to display the picked colors and the result
}
//This is the logic behind the pick. This function has been created to avoid redundancy and to minimize the amount of lines.
int askPickBall(int &nn, int &nv, int &nt, bool is_rand) {
	while (true) { //AWFULL we should never use a while(true) but I guess it will be ok for this specific usage.
		int input;
		if (!is_rand) { //This function check if it's rand so that we can act the right way.
			cout << "Quelle boule voulez-vous tirer (0 pour verte, 1 pour noire) ? Il reste : " << nv << " boule(s) verte(s) et : " << nn << " boule(s) noire(s)." << endl;
			cin >> input;
		}
		else { 
			input = rand() % 2; //This is the code for random pick this will return either 1 or 0.
		}
		if ((input == 0 && nv == 0) || (input == 1 && nn == 0) || (input !=0 && input!= 1)) continue; //A function that check if the selected value is valid
		if (input == 0) {//This will apply the main game logic
			nv--;
		}
		else {
			nn--;
		}
		nt--;
		return input;
	}	
}
string getColorFromCode(int code) {
	switch (code) {
	case 0: return "Verte";
	case 1: return "Noire";
	default: return "Error";
	}
}
//NOTE that this code isn't very optimized but the main goal of this is to be recreational and to learn c++. 

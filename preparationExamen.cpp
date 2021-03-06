#include <iostream>
#include <string>
#include <iomanip>
#include <locale>

using namespace std;
const int MAX_BALL = 20;
const int MAX_ROBOT = 20;
const char colors[] = {'N','B','R'};

struct Ball{
    char color = 'N';
    int point = 8;
};

struct Robot{
    Ball balls[MAX_BALL];
    int NBALL = 0;
    int score = 0;
    string name = "V";
    char notPenalizingBall = 'R';
    bool calculated = false;
};

void showMenu();

void askRobot(Robot &robot);

void affichage(Robot robot);

void affichage(Robot robots[], int amountRobot);

void calculatePoint(Robot &robot);

void calculatePoint(Robot robots[], int amountRobot);

Robot retrieveWinner(Robot robots[], int amountRobot);

void retrieveRobot(Robot robots[], int &numberRobot, int index);

void removeFirstScore(Robot robots[], int numberRobot);

void calculateBlackBalls(Robot robots[], int numberRobot);

bool isColor(char c);

int main(){
    int amountRobot = 0; 
    Robot robots[MAX_ROBOT];
    int choice;
    Robot r;
    setlocale(LC_ALL, "fra");
    while(1){
        showMenu();
        cout << "Que voulez vous faire ? ";
        cin >> choice;
        if(amountRobot != 2&& choice != 1 && choice != 2&& choice!=5){
            cout << "Veuillez donc ajouter le(s) robots qu'il manque." << endl;
            continue;
        }
        switch(choice){
            case 1: 
                retrieveRobot(robots, amountRobot, 0);
                affichage(robots, amountRobot);
                break;
            case 2: 
                retrieveRobot(robots, amountRobot, 1);
                affichage(robots, amountRobot);
                break;
            case 3:
                calculateBlackBalls(robots, amountRobot);
                break;
            case 4: 
                r = retrieveWinner(robots, amountRobot);
                cout << "Le(s) robot " << r.name << " a(ont) eu le score " << r.score << endl;
                affichage(robots, amountRobot);
                break;
            case 5: 
                removeFirstScore(robots, amountRobot);
                affichage(robots, amountRobot);
                break;
            case 6:
                cout << "Au revoir" <<endl;
                system("pause");
                return EXIT_SUCCESS;
                break;
            default:
                cout << "Veuillez entrer un nombre valide ! Compris entre 1 et 6 " << endl;
        }

    }

}

void removeFirstScore(Robot robots[], int numberRobot){
    for(int i = 0; i < numberRobot; i++){
        if(robots[i].NBALL == 0)
            continue;
        robots[i].NBALL--;
        for(int j = 0; j < robots[i].NBALL;j ++){
            robots[i].balls[j] = robots[i].balls[j+1];
        }
        robots[i].calculated = false;
    }
}

void retrieveRobot(Robot robots[], int &numberRobot, int index){
    if(index > numberRobot){
        cout << "Vous ne pouvez pas ajouter ce robot si vous n'avez pas ajouté les précédents" << endl;
        return;
    }
    if(numberRobot == MAX_ROBOT) {
        cout << "Vous avez déjà atteint la limite de robot" << endl;
        return;
    }
    if(numberRobot < index+1){
        numberRobot = index+1;
    }
    Robot r;
    r.name = "V" + to_string(index+1); 
    askRobot(r);
    robots[index] = r;
}

void showMenu(){
    cout << "1. Saisie robot 1 et affichage" << endl;
    cout << "2. Saisie robot 2 et affichage" << endl;
    cout << "3. Comptez le nombre de boules N dans chaque robot" << endl;
    cout << "4. Qui est le gagnant ?" << endl;
    cout << "5. Supprimer le premier element de chacun des tableaux et affichage" << endl;
    cout << "6. Quitter" << endl;
}

Robot retrieveWinner(Robot robots[], int amountRobot){
    calculatePoint(robots[0]);
    Robot max = robots[0];
    bool equiv = false;
    string equivs = robots[0].name;
    for(int i = 1; i < amountRobot; i++){
        calculatePoint(robots[i]);
        if(max.score < robots[i].score){
            equiv = false;
            max = robots[i];
            equivs = robots[i].name + " ";
        }else if(max.score == robots[i].score){
            equiv = true;
            equivs += robots[i].name + " ";
        }
    }
    if(equiv){
        Robot temp;
        temp.score = max.score;
        temp.name = equivs;
        max = temp;
    }
    return max;
}

void calculatePoint(Robot &robot){
    if(robot.calculated)
        return;
    robot.calculated = true;
    robot.score = 0;
    for(int i = 0; i< robot.NBALL; i++){
        Ball b = robot.balls[i];
        robot.score += ((b.color == robot.notPenalizingBall) ? 1 : -1) * b.point;
    }
}

void calculatePoint(Robot robots[], int amountRobot){
    for(int i =0; i < amountRobot; i++){
        calculatePoint(robots[i]);
    }
}

void askRobot(Robot &robot){
    robot.calculated = false;
    cout << "Combien de balle le robot " << robot.name << " a rammassé ? ";
    cin >> robot.NBALL;
    while(robot.NBALL < 1 || robot.NBALL >= MAX_BALL){
        cout << "Veuillez entrer un nombre entre 1 et " << MAX_BALL << endl;
        cin >> robot.NBALL;
    }
    for(int i = 0; i< robot.NBALL; i++){
        Ball b;
        do{
            cout << "Quelle est la couleur de la balle " << i+1 << "? ";
            cin >> b.color;

        }while(!isColor(b.color));
        if(b.color != 'N'){
            cout << "Quelle est la valeur de la balle " << i + 1 << "? ";
            cin >> b.point;
        }
        cout << "Une balle de couleur " << b.color << " et de score " << b.point << " a bien été enregistrée !" << endl; 
        robot.balls[i] = b;
    }
    do{
        cout << "Quelle est la couleur de la balle que le robot doit ramasser ? ";
        cin >> robot.notPenalizingBall;
    }while(!isColor(robot.notPenalizingBall));
}

void affichage(Robot r){
    cout << "Robot : " + r.name << endl;

    if(r.calculated)
        cout << "Il possède " << r.score << " points" << endl;
    cout << "Il y a " << r.NBALL << " balles dans ce robot" << endl;
    for(int i =0; i < r.NBALL; i++){
        cout << setw(2) << r.balls[i].color << " "; 
    }
    cout << endl;
    for(int i = 0; i < r.NBALL; i++){
        cout << setw(2) << r.balls[i].point << " ";
    }
    cout << endl;
    cout << "Balle à ramasser : " << r.notPenalizingBall << endl;
}

void affichage(Robot robots[], int amountRobot){
    for(int i = 0; i< amountRobot; i++){
        affichage(robots[i]);
        cout << "\n" << endl; // 2\n
    }
}
void calculateBlackBalls(Robot robots[], int numberRobot){
    for(int i =0; i < numberRobot; i++){
        int blackBallAmount = 0;
        for(int j =0; j < robots[i].NBALL; j++){
            if(robots[i].balls[j].color == 'N')
                blackBallAmount+=1;
        }
        cout << "Le robot : " << robots[i].name << " possède " << blackBallAmount << " boules noires !" << endl;
    }
}

bool isColor(char c){
    for(char a : colors){
        if(a == c){
            return true;
        }
    }
    return false;
}

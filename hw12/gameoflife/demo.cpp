#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Map.hpp"
#include "Player.hpp"

using namespace std;

int rollDice() {
    return (rand()%10) + 1;
}

void PlayerForward(Map& map, Player& player, int numStep) {
    Square *current, *next;
    for (int i=0; i<numStep; i++) {
        current = player.Position();
        next = current->NextSquare();
        player.setPosition(next);
    }
}

//void turn

int main() {

    srand(time(NULL));

    //Start setting
    int people, age;
    cout << "Enter the number of players (2~6) :"; cin >> people;
    switch(people){
    case 2: age=40; break;
    case 3: age=50; break;
    case 4: age=60; break;
    case 5: age=70; break;
    case 6: age=80; break;
    }

    Map map;
    vector<Player> player(people);
    //Load map from Map.txt and print first ten squares
    map.LoadMap();
    map.CheckMap();
    /*
    Square *tmp = map.StartSquare();
    for (int i=0; i<10; i++) {
      cout << i << ". " << tmp->Description() << endl;
      tmp = tmp->NextSquare();
    }
    cout << endl;
    */

    //Start, College or Career
    for(int i=0; i<people; i++){
        cout << endl << "----------  Player " << i+1 << "'s turn ----------" << endl;
        //Place player to the start square
        Square *Start = map.StartSquare();
        if (Start == NULL) {
            cerr << "Cannot find Start square in the map...." << endl;
            return 1;
        }
        player[i].setPosition(Start);
        //Choose direction
        int choose;
        cout << "Player" << i+1 << " is at: " <<  player[i].Position()->Description() << endl;
        cout << "Which direction do you want to go? 1.College  2.Career: "; cin >> choose;
        //Roll a dice
        int numStep = rollDice();
        cout << "Player " << i+1 << " foward " << numStep << " steps!" << endl;
        //Make player foward
        switch(choose){
        case 1:
            //cout << "!!" << Start->NextSquare(1) << endl;
            player[i].setPosition(Start->NextSquare(1));
            //cout << "Player " << i+1 << " is at: " <<  player[i].Position()->Description() << endl;
            PlayerForward(map, player[i], numStep-1);
            break;
        case 2:
            //cout << "!!" <<  << endl;
            player[i].setPosition(Start->NextSquare(0));
            //cout << "Player " << i+1 << " is at: " <<  player[i].Position()->Description() << endl;
            PlayerForward(map, player[i], numStep-1);
            break;
        }
        cout << "Player " << i+1 << " is at: " <<  player[i].Position()->Description() << endl;
    }

    cin.ignore();

    //Roll a dice and make player foward
    while(age>0){
        for(int i=0; i<people&& age>0; i++){
            cout << endl << "----------  Player " << i+1 << "'s turn ----------" << endl;
            cout << "Press Enter to roll a dice!"; cin.ignore();
            int numStep = rollDice();
            if(numStep==10){
                age=age-10;
                cout << age << " years left till retire!" << endl;
            }
            else{
                cout << "Player " << i << " foward " << numStep << " steps!" << endl;
                PlayerForward(map, player[i], numStep);
                cout << "Player is at: " <<  player[i].Position()->Description() << endl;
                if(player[i].Position()->Type()==Square::GetMoney){
                    player[i].EarnMoney(player[i].Position()->Number());
                }
                cout << "The player now has ";
                cout << player[i].ComputeTotalValue() << endl;
            }
        }
    }

    /*
    //Demo other properties

    //Families
    player.GetMarry();
    player.HaveABaby();
    player.HaveABaby();
    player.GetAPet();
    player.GetAPet();
    cout << player.ComputeTotalValue() << endl;

    //Transport
    player.GetaVehicle(new Car);
    player.ReportValues();
    player.GetaVehicle(new Airplane);
    player.ReportValues();

    //Passport Stamp
    player.GetAStamp(Stamp::Beach);
    player.GetAStamp(Stamp::City);
    player.GetAStamp(Stamp::Snow);
    player.GetAStamp(Stamp::Jungle);
    cout << player.ComputeTotalValue() << endl;

    //House
    Square sq(Square::House, 0, "New House", 1000);
    player.BuyHouse(&sq);
    cout << player.ComputeTotalValue() << endl;

    //Get a Job
    player.GetaJob(new Explorer);
    cout << "My salary is " << player.GetSalary() << endl;

    //Education
    player.GotoCollage();
    //Switch job
    player.GetaJob(new Vet);
    cout << "My salary now is " << player.GetSalary() << endl;
    player.Promote();
    cout << "I got promoted and my salary now is " << player.GetSalary() << endl;
*/
    return 0;
}

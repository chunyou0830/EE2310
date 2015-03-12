#ifndef CARDS_H
#define CARDS_H
#include <string>
using namespace std;

string bla[10]={};

class cards{
private:
    int id;
    int action;
public:
    int getID();
    int getAction();
};

#endif // CARDS_H

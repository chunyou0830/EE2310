//============================================================================
// Name        : cards.cpp
//============================================================================

#include <iostream>
#include <cstdlib>
#include <vector>
#include <iomanip>
#include <ctime>
using namespace std;
char last;

class Card{
public:
	enum Suit {None, Club, Diamond, Heart, Spade};
	enum Rank {Unknown, Ace, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King};

	Card(){ my_suit=None; my_rank=Unknown;}
	Card(Suit s, Rank r){ my_suit=s; my_rank=r;}

	void set_suit(Suit s){ my_suit=s;}
	Suit suit() const { return my_suit;}
	string suit_name() const {return Suit_Names[my_suit];}

	void set_rank(Rank r){ my_rank=r;}
	Rank rank() const { return my_rank;}
	string rank_name() const { return Rank_Names[my_rank];}

private:
	Suit my_suit;
	Rank my_rank;
	static const string Suit_Names[];
	static const string Rank_Names[];
};

const string Card::Suit_Names[]={"None", "Club", "Diamond", "Heart", "Spade"};
const string Card::Rank_Names[]={"Unknown", "Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"};

class Deck{
public:
	Deck(){
		num=52;
		for(int i=1; i<5; i++){
			for(int j=1; j<14; j++){
				cards[(i-1)*13+(j-1)].set_suit(static_cast<Card::Suit>(i));
				cards[(i-1)*13+(j-1)].set_rank(static_cast<Card::Rank>(j));
			}
		}
	}

	void Shuffle(){ //Randomize the sequence of the cards
		int a, b;
		Card buffer;
		for(int i=1; i<1000; i++){
			srand(i*time(NULL));
			a=rand()%52;	b=rand()%52;
			buffer=cards[a];
			cards[a]=cards[b];
			cards[b]=buffer;
		}
	}

	Card& Deal(){ //Hand out the next card on top
		num--;
		return cards[num];
	}

	Card& card(int i){ return cards[i];}
	int Num(){ return num;}

private:
	Card cards[52]; //There are 52 cards in each deck
	unsigned int num; //How many cards are left in the deck
};

class Pack{
private:
	vector<Card> cards;
	bool builded, called;
	int calc;
public:
	Pack(){ cards.clear(); builded=false; called=false; calc=0;}
	Pack(int i){ cards.resize(i); builded=false; called=false; calc=0;}
	
	void push_back(Card in){ cards.push_back(in);}
	int size(){ return cards.size();}
	bool empty(){ return cards.empty();}
	
	void deal(Deck& d){
		cards.push_back(d.Deal());
		cards.push_back(d.Deal());
	}
	
	void print(){
		for(int i = 0 ; i < cards.size() ; i++){
			cout << i << " [" << cards[i].suit_name() << ", "  << cards[i].rank_name() << "]";
			cout << endl;
		}
	}
	Card card(int i){
		return cards[i];
	}
	
	Card extract(int choose){
		Card s=cards[choose];
		for(int i = choose ; i < cards.size() ; i++){
			cards[i] = cards[i+1];
		}
		cards.pop_back();
		return s;
	}
	
	void setBuild(bool target){ builded = target;}
	void setCall(bool target){ called = target;}
	bool getBuild(){ return builded;}
	bool getCall(){ return called;}
	
	void calcP(int i){ calc+=i;}
	int Gcalc(){ return calc;}
};

//----------Pair----------//
bool Pair(Pack& t, Pack& p, Pack& s, int choose){
	for(int i = 0 ; i < t.size() ; i++){
		if(p.card(choose).rank() == t.card(i).rank()){
			s.push_back(t.extract(i));
			s.push_back(p.extract(choose));
			return true;
		}
	}
	return false;
}

//----------Combine----------//
bool Combine(Pack& t, Pack& p, Pack& s, int choose){
	int minus;
	for(int i = 0 ; i < t.size() ; i++){
		if(p.card(choose).rank()>t.card(i).rank()){ minus=p.card(choose).rank()-t.card(i).rank();}
		else{ continue;}
		for(int j = 0 ; j < t.size() ; j++){
			if(minus == t.card(j).rank()){
				s.push_back(p.extract(choose));
				if(i > j){ s.push_back(t.extract(i)); s.push_back(t.extract(j));}
				else{ s.push_back(t.extract(j)); s.push_back(t.extract(i));}
				return true;
			}
		}
	}
	return false;
}

//----------Tailing----------//
bool Tailing(Pack& t, Pack& p, Pack& s, int choose){
	t.push_back(p.extract(choose));
}

//----------Build----------//
bool Build(Pack& t, Pack& p, Pack& s, int choose){
	bool paired = false, combined = false;
	for(int i = 0 ; i < t.size() ; i++){
		//Find pair
		if(p.card(choose).rank() == t.card(i).rank()) paired = true;
		//Find Combined
		int minus=p.card(choose).rank()-t.card(i).rank();
		for(int j = 0 ; j < t.size() ; j++){
			if(minus == t.card(j).rank()) combined = true;
		}
		//Found both
		if(paired&&combined) break;
	}
	//Second time and founded any
	if((paired||combined)&&p.getBuild()){
		if(paired)
			Pair(t,p,s,choose);
		else if(combined)
			Combine(t,p,s,choose);
		//Reset status
		p.setBuild(false);
	}
	//First time or cannot found any
	else{
		//Selected >> table
		Tailing(t,p,s,choose);
		//Set status
		p.setBuild(true);
		return true;
	}
}

//----------Call----------//
bool Call(Pack& t, Pack& p, Pack& s, int choose){
	bool paired = false, combined = false;
	for(int i = 0 ; i < t.size() ; i++){
		//Find Pair
		if(p.card(choose).rank() == t.card(i).rank()) paired = true;
		//Find Combined
		int minus=p.card(choose).rank()-t.card(i).rank();
		for(int j = 0 ; j < t.size() ; j++){
			if(minus == t.card(j).rank()) combined = true;
		}
		//Found both
		if(paired&&combined) break;
	}
	//Second time and founded both
	if(paired&&combined&&p.getCall()){
		//Push pair part 
		for(int i = 0 ; i < t.size() ; i++){
			if(p.card(choose).rank() == t.card(i).rank())
				s.push_back(t.extract(i));
		}
		//Push combine part 
		Combine(t,p,s,choose);
		//Reset status
		p.setCall(false);
		return true;
	}
	//First time or cannot found both
	else{
		//Selected >> table
		Tailing(t,p,s,choose);
		//Set status
		p.setCall(true);
		return true;
	}
}

void Play(Pack& t, Pack& p, Pack& s, char turn){
	int choose, act;
	bool NoAct=true;
	//Print Information
	system("CLS");
	cout << "----------PLAYER " << turn << "\'S TURN----------" << endl;
	cout << "Your cards:" << endl; p.print();
	cout << endl << "Table:" << endl; t.print();
	
	//Choose a card and an action
	cout << endl << "Choose a card from your cards? "; cin >> choose;
	while(NoAct){
		cout << endl << "Choose an action?\n0 Pair\n1 Combine\n2 Build\n3 Call\n4 Tailing  ";
		cin >> act;
		switch(act){
			case 0:
				if(Pair(t,p,s,choose)){ cout << endl << "Paired!" << endl; NoAct=false; last=turn; break;}
				else{ cout << endl << "You cannot do this!" << endl; break;}
			case 1:
				if(Combine(t,p,s,choose)){ cout << endl << "Combined!" << endl; NoAct=false; break;}
				else{ cout << endl << "You cannot do this!" << endl; break;}
			case 2:
				if(Build(t,p,s,choose)){ cout << endl << "Builded!" << endl; NoAct=false; break;}
				else{ cout << endl << "You cannot do this!" << endl; break;}
			case 3:
				if(Call(t,p,s,choose)){ cout << endl << "Called!" << endl; NoAct=false; break;}
				else{ cout << endl << "You cannot do this!" << endl; break;}
			case 4:
				Tailing(t,p,s,choose); cout << endl << "Tailing!" << endl; NoAct=false; break;
		}
	}
	cout << endl << "Your cards:" << endl; p.print();
	cout << "Your score:" << endl;
	if(t.empty())
		p.calcP(1);
	s.print();
	system("PAUSE");
}

void Calc(Pack& p){
	int spades=0;
	for(int i = 0 ; i < p.size() ; i++){
		if(p.card(i).suit()==4)
			spades++;
		if(p.card(i).rank()==1)
			p.calcP(1);
		if(p.card(i).rank()==2&&p.card(i).suit()==10)
			p.calcP(2);
		if(p.card(i).rank()==1&&p.card(i).suit()==2)
			p.calcP(1);
	} 
	if(p.size()>=27)
		p.calcP(3);
	if(spades>=7)
		p.calcP(1);
}

int main(){
	Deck d1;
	Pack p1, p2, table, s1, s2;
	
	d1.Shuffle();

	for(int i=0; i<2; i++){
		p1.deal(d1);
		p2.deal(d1);
		table.deal(d1);
	}
	
	while(1){
		if(p1.empty()&&p2.empty()){
			if(d1.Num()!=0){ p1.deal(d1); p2.deal(d1); p1.deal(d1); p2.deal(d1);}
			else{ break;}
		}
		Play(table,p1,s1,'A');
		Play(table,p2,s2,'B');
	}
	if(last=='A'){
		while(!table.empty()){
			s1.push_back(table.extract(0));
		}
	}
	else if(last=='B'){
		while(!table.empty()){
			s2.push_back(table.extract(0));
		}
	}
	Calc(p1);
	Calc(p2);
	cout << "Player1: " << p1.Gcalc() << endl << "Player2: " << p2.Gcalc();
	return 0;
}

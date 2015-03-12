//============================================================================
// Name        : cards.cpp
//============================================================================

#include <iostream>
#include <cstdlib>
#include <vector>
#include <iomanip>
#include <ctime>
using namespace std;

class Card{
public:
	enum Suit {None, Club, Diamond, Heart, Spade};
	enum Rank {Unknown, Ace, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King};

	Card(){
		my_suit=None;
		my_rank=Unknown;
	}

	Card(Suit s, Rank r){
		my_suit=s;
		my_rank=r;
	}

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

	Card& card(int i){
		return cards[i];
	}
	
	int Num(){
		return num;
	}

private:
	Card cards[52]; //There are 52 cards in each deck
	unsigned int num; //How many cards are left in the deck
};

class Pack{
private:
	vector<Card> cards;
	vector<bool> locked;
public:
	Pack(){ cards.clear(); locked.clear();}
	Pack(int i){ cards.resize(i); locked.resize(i);}
	
	void push_back(Card in){ cards.push_back(in);}
	int size(){ return cards.size();}
	bool empty(){ return cards.empty();}
	
	void deal(Deck& d){
		cards.push_back(d.Deal());
		cards.push_back(d.Deal());
		locked.push_back(false);
		locked.push_back(false);
	}
	
	void print(){
		for(int i = 0 ; i < cards.size() ; i++){
			cout << i << " [" << cards[i].suit_name() << ", "  << cards[i].rank_name() << "]";
			if(locked[i]){
				cout << " Locked";
			}
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
		locked.pop_back();
		return s;
	}
};

bool Pair(Pack& t, Pack& p, Pack& s, int choose){
	for(int i = 0 ; i < t.size() ; i++){
		if(p.card(choose).rank() == t.card(i).rank()){
			s.push_back(t.extract(i));
			s.push_back(p.extract(choose));
			cout << endl << p.size() << endl;
			return true;
		}
	}
	return false;
}

bool Combine(Pack& t, Pack& p, Pack& s, int choose){
	for(int i = 0 ; i < t.size() ; i++){
		int minus=p.card(choose).rank()-t.card(i).rank();
		for(int j = 0 ; j < t.size() ; j++){
			if(minus == t.card(j).rank()){
				s.push_back(p.extract(choose));
				if(i > j){
					s.push_back(t.extract(i)); s.push_back(t.extract(j));
				}
				else{
					s.push_back(t.extract(j)); s.push_back(t.extract(i));
				}
				return true;
			}
		}
	}
	return false;
}

bool Tailing(Pack& t, Pack& p, Pack& s, int choose){
	t.push_back(p.extract(choose));
}

void Play(Pack& t, Pack& p, Pack& s, char turn){
	int choose, act;
	bool NoAct=true;
	//Pick a card
	system("CLS");
	cout << "----------PLAYER " << turn << "\'S TURN----------" << endl;
	cout << "Your cards:" << endl; p.print();
	cout << endl << "Table:" << endl; t.print();
	cout << endl << "Choose a card from your cards? "; cin >> choose;
	while(NoAct){
		cout << endl << "Choose an action?\n0 Pair\n1 Combine\n2 Build\n3 Call\n4 Tailing  ";
		cin >> act;
		switch(act){
			case 0:
				if(Pair(t,p,s,choose)){ cout << endl << "Paired!"; NoAct=false; break;}
				else{ cout << endl << "You cannot do this!" << endl; break;}
			case 1:
				if(Combine(t,p,s,choose)){ cout << endl << "Combined!" << endl; NoAct=false; break;}
				else{ cout << endl << "You cannot do this!" << endl; break;}
			case 4:
				Tailing(t,p,s,choose);
				cout << endl << "Tailing!" << endl; NoAct=false; break;
		}
	}
	cout << endl << "Your cards:" << endl; p.print();
	cout << "Your score:" << endl; 
	s.print();
	system("PAUSE");
}


int main() {
	Deck d1;
	Pack p1, p2, table, s1, s2;
	
	d1.Shuffle();

	for(int i=0; i<2; i++){
		p1.deal(d1);
		p2.deal(d1);
		table.deal(d1);
	}
	
	while(d1.Num()!=0){
		if(p1.empty()&&p2.empty()){ p1.deal(d1); p2.deal(d1); p1.deal(d1); p2.deal(d1);}
		Play(table,p1,s1,'A');
		Play(table,p2,s2,'B');
	}
	return 0;
}

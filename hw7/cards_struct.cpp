//============================================================================
// Name        : cards_struct.cpp
//============================================================================

#include <iostream>
#include <cstdlib>
using namespace std;

struct Card{
	enum Suit {None, Club, Diamond, Heart, Spade};
	enum Rank {Unknown, Ace, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King};

	Suit my_suit;
	Rank my_rank;

	static const string Suit_Names[];
	static const string Rank_Names[];
};

const string Card::Suit_Names[]={"None", "Club", "Diamond", "Heart", "Spade"};
const string Card::Rank_Names[]={"Unknown", "Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"};

string Suit_name(Card c) {return Card::Suit_Names[c.my_suit];}
string Rank_name(Card c) {return Card::Rank_Names[c.my_rank];}

struct Deck{
	Card cards[52]; //There are 52 cards in each deck
	unsigned int num; //How many cards are left in the deck
};

void Shuffle(Deck& d){ //Randomize the sequence of the cards
	int a, b;
	Card buffer;
	for(int i=1; i<1000; i++){
		srand(i);
		a=rand()%52;	b=rand()%52;
		buffer=d.cards[a];
		d.cards[a]=d.cards[b];
		d.cards[b]=buffer;
	}
}

Card& Deal(Deck& d){ //Hand out the next card on top
	d.num--;
	return d.cards[d.num];
}

int main() {
	Deck d1;
	Card p1[4], p2[4], table[4];
	//Initialize d1 struct
	d1.num=52;
	for(int i=1; i<5; i++){
		for(int j=1; j<14; j++){
			d1.cards[(i-1)*13+(j-1)].my_suit=static_cast<Card::Suit>(i);
			d1.cards[(i-1)*13+(j-1)].my_rank=static_cast<Card::Rank>(j);
		}
	}
	
	Shuffle(d1);
	
	for(int i=0; i<52; i++){
		cout << "["<<Suit_name(d1.cards[i]) << ", " <<Rank_name(d1.cards[i]) << "]" <<endl;
	}
	
	//Dealing
	for(int i=0; i<2; i++){
		for(int j=0; j<2; j++){
			p1[i*2+j]=Deal(d1);
		}
		for(int j=0; j<2; j++){
			p2[i*2+j]=Deal(d1);
		}
		for(int j=0; j<2; j++){
			table[i*2+j]=Deal(d1);
		}
	}
	
	//Show the result of dealing
	cout << endl << "P1:" << endl;
	for(int i=0; i<4; i++){
		cout << "["<<Suit_name(p1[i]) << ", " <<Rank_name(p1[i]) << "]" <<endl;
	}
	cout << endl << "P2:" << endl;
	for(int i=0; i<4; i++){
		cout << "["<<Suit_name(p2[i]) << ", " <<Rank_name(p2[i]) << "]" <<endl;
	}
	cout << endl << "Table:" << endl;
	for(int i=0; i<4; i++){
		cout << "["<<Suit_name(table[i]) << ", " <<Rank_name(table[i]) << "]" <<endl;
	}
	return 0;
}

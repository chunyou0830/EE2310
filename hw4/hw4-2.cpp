#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main(){
	
	int temp=1, humid=1, outlook=1, windy=1, show=1;
	char fname[100];
	cout << "-----INSTRUCTION-----\nEnter what's the weather like and decide if a game will continue to play or not.\n\n-----DECISION TREE-----\n                                    |-- '=FALSE' -- 'yes'\n            |-- '=rainy' -- WINDY --|-- '=TRUE' -- 'no'\n  OUTLOOK --|-- '=overcast' -- 'yes'\n            |-- '=sunny' -- HUMIDITY --|-- '>75' -- 'no'\n                                       |-- '<=75' -- 'yes'\n\n";
	
	cout << "----------> TARGET FILE NAME <-----------\nEnter the target text file name you want. Add \".txt\" in the end.\n";
	cin >> fname;
	ofstream outfile;
	outfile.open(fname);
	
	cout << "----------> OPTION <-----------\nDo you want to print your decision on the screen? 0)NO  1)YES\n";
	do{cin >> show;}		while(show>1 || show<0);
	cout << "----------> OUTLOOK <-----------\n1)sunny  2)overcast  3)rainy\n";
	do{cin >> outlook;}		while(outlook>3 || outlook<1);
	cout << "----------> HUMIDITY <-----------\nEnter the value directly.\n";
	do{cin >> humid;}		while(humid>100 || outlook<1);
	cout << "----------> WINDY <-----------\n0)FALSE  1)TRUE.\n";
	do{cin >> windy;}		while(windy>1 || windy<0);
	
	system("cls");
	
	cout << "---------- RESULT ----------\n";
	if(show){
		cout << "outlook == ";
		if(outlook == 1) cout << "sunny";		else if(outlook == 2) cout << "overcast";		else cout << "rainy";
		cout << ", humidity == " << humid << ", windy == ";
		if(windy) cout << "TRUE\n\n";			else cout << "FALSE\n\n";
	}
	
	switch(outlook){
		case 2:
			outfile << "\"play\"==\"yes\"";
			break;
		case 1:
			if(humid<=75) outfile << "\"play\"==\"yes\"";
			else outfile << "\"play\"==\"no\"";
			break;
		case 3:
			if(windy) outfile << "\"play\"==\"no\"";
			else outfile << "\"play\"==\"yes\"";
			break;
	}
	cout << "The result has been saved to " << fname;
	
	outfile.close();
	return 0;
}

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

int main(){
	string outlook;
	int temp, humid;
	bool windy;

	cout << "Enter outlook, temp, humid and windy(bool): ";
	cin >> outlook >> temp >> humid >> windy;
	
	if(outlook=="sunny"){
		if(humid<=75){cout << "\"play\"=\"yes\"";}
		else{cout << "\"play\"=\"no\"";}
	}
	else if(outlook=="overcast"){
		cout << "\"play\"=\"yes\"";
	}
	else{
		if(windy==0){cout << "\"play\"=\"yes\"";}
		else{cout << "\"play\"=\"no\"";}
	}
	
	return 0;
}

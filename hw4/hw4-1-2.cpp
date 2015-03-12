#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

int main(){
	string outlook, play, ans, buf, windy;
	float temp, humid;
	int num;
	
	fstream file;
	file.open("hw4_weather_data.txt", ios::in);
	getline(file, buf);
	cout << left << setw(5) << "No." << setw(10) << "Outlook" << setw(6) << "Temp" << setw(7) << "Humid" << setw(7) << "Windy" << setw(6) << "Play" << "CorrectAns" << endl;

	while(file){
		file >> num >> outlook >> temp >> humid >> windy >> ans;
		
		if(outlook=="sunny"){
			if(humid<=75){play="yes";}
			else{play="no";}
		}
		else if(outlook=="overcast"){
			play="yes";
		}
		else{
			if(windy=="FALSE"){play="yes";}
			else{play="no";}
		}
		
		cout << left << setw(5) << num << setw(10) << outlook << setw(6) << temp << setw(7) << humid << setw(7) << windy << setw(6) << play << ans << endl;
	}
	
	file.close();

	/*
	cout << "Enter outlook, temp, humid and windy(bool): ";
	cin >> outlook >> temp >> humid >> windy;
	*/

	return 0;
}

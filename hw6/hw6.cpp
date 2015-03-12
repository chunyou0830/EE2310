#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
using namespace std;

int Population[2][4][4], times = 0;
double Birth[4][4]={0}, Death[4][4]={0}, Economic[4][4]={0}, Cost[4][4]={0};

void CPopulation(int i, int j){
	Population[1][i][j] = Population[0][i][j] + Birth[i][j] * Population[0][i][j] - Death[i][j] * Population[0][i][j];
}

void CEconomic(int i, int j){
	if(Economic[i][j] > Economic[i][j+1] && j < 3){
		Population[1][i][j] = Population[1][i][j] + (Economic[i][j] - Economic[i][j+1]) * Population[0][i][j+1];
		Population[1][i][j+1] = Population[1][i][j+1] - (Economic[i][j] - Economic[i][j+1]) * Population[0][i][j+1];
	}
	else if(Economic[i][j] < Economic[i][j+1] && j < 3){
		Population[1][i][j] = Population[1][i][j] - (Economic[i][j+1] - Economic[i][j]) * Population[0][i][j];
		Population[1][i][j+1] = Population[1][i][j+1] + (Economic[i][j+1] - Economic[i][j]) * Population[0][i][j];
	}
	
	if(Economic[i][j] > Economic[i+1][j] && i < 3){
		Population[1][i][j] = Population[1][i][j] + (Economic[i][j] - Economic[i+1][j]) * Population[0][i+1][j];
		Population[1][i+1][j] = Population[1][i+1][j] - (Economic[i][j] - Economic[i+1][j]) * Population[0][i+1][j];
	}
	else if(Economic[i][j] < Economic[i+1][j] && i < 3){
		Population[1][i][j] = Population[1][i][j] - (Economic[i+1][j] - Economic[i][j]) * Population[0][i][j];
		Population[1][i+1][j] = Population[1][i+1][j] + (Economic[i+1][j] - Economic[i][j]) * Population[0][i][j];
	}
}

void CCost(int i, int j){
	if(Cost[i][j] > Cost[i][j+1] && j < 3){
		Population[1][i][j] = Population[1][i][j] + (Cost[i][j] - Cost[i][j+1]) * Population[0][i][j+1];
		Population[1][i][j+1] = Population[1][i][j+1] - (Cost[i][j] - Cost[i][j+1]) * Population[0][i][j+1];
	}
	else if(Cost[i][j] < Cost[i][j+1] && j < 3){
		Population[1][i][j] = Population[1][i][j] - (Cost[i][j+1] - Cost[i][j]) * Population[0][i][j];
		Population[1][i][j+1] = Population[1][i][j+1] + (Cost[i][j+1] - Cost[i][j]) * Population[0][i][j];
	}
	
	if(Cost[i][j] > Cost[i+1][j] && i < 3){
		Population[1][i][j] = Population[1][i][j] + (Cost[i][j] - Cost[i+1][j]) * Population[0][i+1][j];
		Population[1][i+1][j] = Population[1][i+1][j] - (Cost[i][j] - Cost[i+1][j]) * Population[0][i+1][j];
	}
	else if(Cost[i][j] < Cost[i+1][j] && i < 3){
		Population[1][i][j] = Population[1][i][j] - (Cost[i+1][j] - Cost[i][j]) * Population[0][i][j];
		Population[1][i+1][j] = Population[1][i+1][j] + (Cost[i+1][j] - Cost[i][j]) * Population[0][i][j];
	}
}

void Simulate(int i, int j){
	CPopulation(i,j);
	CEconomic(i,j);
	CCost(i,j);
	if(Population[1][i][j]>0)
	cout << setw(8) << Population[1][i][j];
	else
	cout << setw(8) << 0;
}

void GenParameters(){
	srand(time(NULL));
	cout << "YEAR 0" << "--------------------------" << endl;
	for(int i = 0 ; i < 4 ; i++){
		for(int j = 0 ; j < 4 ; j++){
			Population[0][i][j] = (rand()%100000)+10000;
			Birth[i][j] = (rand()%100)/100.0;
			Death[i][j] = (rand()%100)/100.0;
			Economic[i][j] = (rand()%200)/100.0 - 1;
			Cost[i][j] = (rand()%200)/100.0 - 1;
			cout << setw(8) << Population[0][i][j];
		}
		cout << endl;
	}
}

void ReadParameters(ifstream& read){
	int buffer;
	cout << "YEAR 0" << "--------------------------" << endl;
	for(int i = 0 ; i < 4 ; i++){
		for(int j = 0 ; j < 4 ; j++){
			read >> Population[0][i][j] >> Birth[i][j] >> Death[i][j] >> Economic[i][j] >> Cost[i][j];
			cout << setw(8) << Population[0][i][j];
		}
		cout << endl;
	}
}

int main(){
	ifstream read;
	read.open("record.txt");
	
	int func;
	cout << "1)Generate 2)Read from file : ";
	cin >> func;
	cout << "Years to run : ";
	cin >> times;
	switch(func){
		case 1:
			GenParameters();
			break;
		case 2:
			ReadParameters(read);
			break;
	}
	
	for(int k = 0 ; k < times ; k++){
		cout << "YEAR " << k+1 << "--------------------------" << endl;
		for(int i = 0 ; i < 4 ; i++){
			for(int j = 0 ; j < 4 ; j++){
					Simulate(i,j);
			}
			cout << endl;
		}
		
		for(int i = 0 ; i < 4 ; i++){
			for(int j = 0 ; j < 4 ; j++){
					Population[0][i][j]=Population[1][i][j];
			}
		}
	}
	return 0;
}

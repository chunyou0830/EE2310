#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <time.h>

using namespace std;

int id=0, repairNum, returnNum, custCount=0, stepCount, usageCount, pairCount, returnCount, inqCount, randCount=0;

string modelName[3]={"Care Band","Safety Band","Deluxe Watch"};
string featureWord[5]={"Heart rate and blood pressure detection",
					   "Exercise Tracking and analysing",
					   "Sleeping status monitoring",
					   "Smartphone wireless conncection",
					   "Gyro/G sensing and safety alarming"};
string namePool[10]={"Allen","Betty","Chris","Danny","Ethan","Frances","George","Hellen","Ivan","Jason"};
int numberRange[3][2]={{19999,10001},{29999,20001},{39999,30001}};
bool feature[3][5]={{1,1,1,0,0},{1,1,0,0,1},{1,1,1,1,1}};

fstream sData;

int main();
int endMenu();
int productModel();
int productNumber(int model);

int Login(){		//Login Page FIN
	//Show header
	srand(time(NULL)*custCount);
	
	system("cls");
	cout << ".......... CUSTOMER SERVICE CENTER Login .........." << endl;
	
	//Info input
	string name;
	id = rand()%10 + 1;
	name = namePool[id-1];
		/*
		cout << "Name: ";	cin >> name;	cout << "ID: ";		cin >> id;
		*/
	
	//Get system time
    time_t timeNow = time(NULL);
	
	//Save log
	custCount++;	stepCount = 0;
	randCount++;
	sData << endl << "--------------------" << endl << ctime(&timeNow) << "Name = " << name << endl << "ID = " << id << endl;
}

int Usage(){		//Usage Menu
	//Show header and Save Log
	system("cls");
	cout << ".......... CUSTOMER SERVICE CENTER .........." << endl << "MENU >> Home >> Product Usage" << endl << "------------------------------" << endl;
	sData << " > usage";			stepCount++;			usageCount++;
	
	//Info Input
	int model = productModel();
	
	//Feature Print
	for(int i = 0 ; i <= 4 ; i++){
		if(feature[model][i])
			cout << i+1 << ")" << featureWord[i] << endl;
		else
			cout << "X)" << featureWord[i] << endl;
	}
	
	int choose = 1;
	switch(choose){
		//Feature Input
		cout << endl << "Please Select a feature to look out the detail about it, or enter 0 to go back to the previous menu." << endl;
		choose = rand()%6;
			/*
			cin >> choose;
			*/
		switch(choose){
			case 0: break;
			case 1: 
				system("cls");
				cout << ".......... CUSTOMER SERVICE CENTER .........." << endl << "MENU >> Home >> Product Usage >> Heart rate and blood pressure detection" << endl << "------------------------------" << endl;
				cout << "The product can detect your heart rate and blood pressure, and alarm you whenever your blood pressure is too high or low." << endl << endl;
				break;
			case 2:
				system("cls");
				cout << ".......... CUSTOMER SERVICE CENTER .........." << endl << "MENU >> Home >> Product Usage >> Exercise Tracking and analysing" << endl << "------------------------------" << endl;
				cout << "Combining with bheart rate detection, we can track your exercise route by GPS and analyse your status and tracks." << endl << endl;
				break;
			case 3: 
				system("cls");
				cout << ".......... CUSTOMER SERVICE CENTER .........." << endl << "MENU >> Home >> Product Usage >> Sleeping status monitoring" << endl << "------------------------------" << endl;
				cout << "The device will detect your breath, heart rate and the reactions when you are sleeping, and to let you improve the sleeping quality." << endl << endl;
				break;
			case 4: 
				system("cls");
				cout << ".......... CUSTOMER SERVICE CENTER .........." << endl << "MENU >> Home >> Product Usage >> Smartphone wireless conncection" << endl << "------------------------------" << endl;
				cout << "The product can connect wih your smartphone, in order to listen to music, picking up phonecalls, getting any kinds of informations from the net, and just to name a few." << endl << endl;
				break;
			case 5: 
				system("cls");
				cout << ".......... CUSTOMER SERVICE CENTER .........." << endl << "MENU >> Home >> Product Usage >> Gyro/G sensing and safety alarming" << endl << "------------------------------" << endl;
				cout << "The product equipes a g sensor, to detect your movements. When you fell, we will also send an alarm message out." << endl << endl;
				break;
		}
	}
}

int Repair(){		//Product Repair
	//Show header
	system("cls");
	cout << ".......... CUSTOMER SERVICE CENTER .........." << endl << "MENU >> Home >> Product Inquiry >> Product Repair" << endl << "------------------------------" << endl;
	
	//Info input
	string buffer, address;
	int year = rand() % 24 + 1990, month = rand() % 12 + 1, day = rand() % 31 + 1;
	int model = rand() % 3, number = productNumber(model);
		/*
		int model = productModel(), number = productNumber(model), yar, month, day;
		cout << "Purchase date (YYYY MM DD): ";					cin >> year >> month >> day;
		cout << "Address: ";			getline(cin, buffer);	getline(cin, address);
		*/
	
	//Warranty check
	struct tm buy = {0,0,0,day,month-1,year-1900};
    time_t t1 = mktime(&buy), t2 = time(NULL);
	
	//Save Log
	cout << "Thank you for your report. Your repair number is: " << setw(7) << setfill('0') << ++repairNum << endl;
	sData << " > repair";			stepCount++;			pairCount++;
	sData << endl << endl << "RepairNo." << setw(7) << setfill('0') << repairNum << endl << "|-ProductModel = " << model << endl << "|-ProductNumber = " << number << endl << "|-PurchaseDate = " << year << "." << month << "." << day /*<< endl << "|-Address = " << address*/ << endl;
	
	//Bill Generate
	if(difftime(t2, t1) > 31536000){
		cout << "\nDue to your warranty has expired, you will have to pay a fee for repairing the product.\n\n********** Repair Request Bill **********" << endl << "Customer ID: " << id << endl << "Product Number: " << number << endl << "Product repair fee: " << (int)(difftime(t2, t1) / 31536000)*100 << endl << "*****************************************";
		sData << "|-Fee = " << (int)(difftime(t2, t1) / 31536000)*100 << endl ;
	
	}
	
	sData << endl;
}

int Return(){	//Product Return FIN
	//Show header
	system("cls");
	cout << ".......... CUSTOMER SERVICE CENTER .........." << endl << "MENU >> Home >> Product Inquiry >> Product Return" << endl << "------------------------------" << endl;
	
	//Info input
	int year = rand() % 24 + 1990, month = rand() % 12 + 1, day = rand() % 31 + 1;
	int model = rand() % 3, number = productNumber(model);
		/*
		int model = productModel(), number = productNumber(model), year, month, day;
		cout << "Purchase date (YYYY MM DD): ";					cin >> year >> month >> day;
		cout << "Address: ";			getline(cin, buffer);	getline(cin, address);
		*/
	
	//Save Log
	cout << "Thank you for your report. Your return number is: " << setw(7) << setfill('0') << ++returnNum << endl;
	sData << " > return";			stepCount++;			returnCount++;
	sData << endl << endl << "ReturnNo." << setw(7) << setfill('0') << returnNum << endl << "|-ProductModel = " << model << endl << "|-ProductNumber = " << number << endl << "|-PurchaseDate = " << year << "." << month << "." << day << endl << endl;

}

int inq(){			//Inquiry Menu FIN
	int func=1;
	while(func){
		//Show header and Save Log
		system("cls");
		cout << ".......... CUSTOMER SERVICE CENTER .........." << endl << "MENU >> Home >> Product Inquiry" << endl << "------------------------------" << endl;
		cout << "Which kind of demand do you need?\n  0)Back\n  1)Product Repair\n  2)Product Return\n";
		sData << " > inquire";			stepCount++;			inqCount++;
		
		//Menu choose
		func = rand()%3;
			/*
			cin >> func;
			*/
		switch(func){
			case 1:
				Repair();
				break;
			case 2:
				Return();
				break;
			case 0:
				break;
			default:
				cout << "Invalid input! Please choose again." << endl;
		}
	}
}

int endMenu(){
	int func;
	cout << endl << endl << "Enter 0 to logout or 1 to go back to the main menu.\n";
	while(1){
		cin >> func;
		switch(func){
			case 0:
				id = 0;
				sData << endl << "steps = " << stepCount << endl;
				main();
			case 1:
				main();
			default:
				cout << "Invalid input! Please choose again." << endl;
		}
	}
}

int productModel(){
	int model;
	cout << "Product Model: ";
	for(int j = 0 ; j <= 2 ; j++){
		cout << j << "." << modelName[j] << "  ";
	}

	while(1){
		model = rand() % 3;
			/*
			cin >> model;
			*/
		if (model==0 || model==1 || model==2){
			return model;
			break;
		}
		else{
			cout << "Can\'t find this product, please enter again!\n To check the product list, enter\"help\"" << endl;		
		}
	}

}

int productNumber(int model){
	int number;
	cout << "Product Number: ";
	while(1){
		number = (rand() % 3 + 1)*10000 + rand()%100+1;
			/*
			cin >> number;
			*/
		if(number <= numberRange[model][0] && number >= numberRange[model][1]){
			return number;
			break;
		}
		else{
			cout << "Can\'t recognize your product number, please enter again!" << endl;
		}
	}
}

int main(){		//Main Menu
	int func=1;
	sData.open("SystemLog.txt", ios::out|ios::app);
	while(func){
		//Check Login Status
		if(id == 0)			Login();
		
		//Show header, Save log
		system("cls");
		cout << ".......... CUSTOMER SERVICE CENTER .........." << endl << "MENU >> Home" << endl << "------------------------------" << endl;
		cout << "Please choose which service you want.\n  1)Product usage\n  2)Product Inquiry\n  3)Logout and exit\n  0)Close and Leave System\n";
		sData << " > home";				stepCount++;
		
		//Menu Choose		
		if(randCount==100)
			func = 0;
		else
			func = rand()%3 + 1;
			/*
			cin >> func;
			*/
			
		switch(func){
			case 1:
				Usage();
				break;
			case 2:
				inq();
				break;
			case 3:
				id = 0;
				sData << endl << endl << "steps = " << stepCount << endl;
				break;
			case 0:
				sData << endl << endl << "steps = " << stepCount << endl;
				sData << endl << "------------------------------" << endl << "SYSTEM SUMMARY" << endl
					  << "Total Customers = " << custCount << endl
					  << "Usage Menu Selected = " << usageCount << endl
					  << "Inquiry Menu Selected = " << inqCount << endl
					  << "Repair Selected = " << pairCount << endl
					  << "Return Selected = " << returnCount << endl;
					  sData.close();
				break;
		}
	}
	return 0;
}

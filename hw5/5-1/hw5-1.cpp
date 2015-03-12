#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <time.h>

using namespace std;
int id, repairNum, returnNum, custCount, stepCount, usageCount, pairCount, returnCount, inqCount;

string modelName[3]={"Care Band","Safety Band","Deluxe Watch"};
string featureWord[5]={"Heart rate and blood pressure detection",
					   "Exercise Tracking and analysing",
					   "Sleeping status monitoring",
					   "Smartphone wireless conncection",
					   "Gyro/G sensing and safety alarming"};
int numberRange[3][2]={{19999,10001},{29999,20001},{39999,30001}};
bool feature[3][5]={{1,1,1,0,0},{1,1,0,0,1},{1,1,1,1,1}};

fstream sData;

int main();
int endMenu();
int productModel();
int productNumber(int model);

int Login(){		//Login Page FIN
	//Show header
	system("cls");
	cout << ".......... CUSTOMER SERVICE CENTER Login .........." << endl;
	
	//Info input
	string name;
	cout << "Name: ";	cin >> name;	cout << "ID: ";		cin >> id;
	
	//Get system time
    time_t timeNow = time(NULL);
	
	//Save log
	custCount++;	stepCount = 0;
	sData.open("SystemLog.txt", ios::out|ios::app);
	sData << endl << "--------------------" << endl << ctime(&timeNow) << "Name = " << name << endl << "ID = " << id << endl;
}

int Usage(){		//Usage Menu
	//Show header
	system("cls");
	cout << ".......... CUSTOMER SERVICE CENTER .........." << endl << "MENU >> Home >> Product Usage" << endl << "------------------------------" << endl;
	
	//Save log
	sData << " > usage";			stepCount++;			usageCount++;
	
	//Info Input
	string buffer;					getline(cin, buffer);
	int model = productModel();
	
	//Feature Select
	in:for(int i = 0 ; i <= 4 ; i++){
		if(feature[model][i])
			cout << i+1 << ")" << featureWord[i] << endl;
		else
			cout << "X)" << featureWord[i] << endl;
	}
	
	//Feature Input
	int choose;
	cout << endl << "Please Select a feature to look out the detail about it, or enter 0 to go back to the main menu." << endl;
	cin >> choose;
	switch(choose){
		case 0: main();
		case 1: 
			system("cls");
			cout << ".......... CUSTOMER SERVICE CENTER .........." << endl << "MENU >> Home >> Product Usage >> Heart rate and blood pressure detection" << endl << "------------------------------" << endl;
			cout << "The product can detect your heart rate and blood pressure, and alarm you whenever your blood pressure is too high or low." << endl << endl;
			goto in;
		case 2:
			system("cls");
			cout << ".......... CUSTOMER SERVICE CENTER .........." << endl << "MENU >> Home >> Product Usage >> Exercise Tracking and analysing" << endl << "------------------------------" << endl;
			cout << "Combining with bheart rate detection, we can track your exercise route by GPS and analyse your status and tracks." << endl << endl;
			goto in;
		case 3: 
			system("cls");
			cout << ".......... CUSTOMER SERVICE CENTER .........." << endl << "MENU >> Home >> Product Usage >> Sleeping status monitoring" << endl << "------------------------------" << endl;
			cout << "The device will detect your breath, heart rate and the reactions when you are sleeping, and to let you improve the sleeping quality." << endl << endl;
			goto in;
		case 4: 
			system("cls");
			cout << ".......... CUSTOMER SERVICE CENTER .........." << endl << "MENU >> Home >> Product Usage >> Smartphone wireless conncection" << endl << "------------------------------" << endl;
			cout << "The product can connect wih your smartphone, in order to listen to music, picking up phonecalls, getting any kinds of informations from the net, and just to name a few." << endl << endl;
			goto in;
		case 5: 
			system("cls");
			cout << ".......... CUSTOMER SERVICE CENTER .........." << endl << "MENU >> Home >> Product Usage >> Gyro/G sensing and safety alarming" << endl << "------------------------------" << endl;
			cout << "The product equipes a g sensor, to detect your movements. When you fell, we will also send an alarm message out." << endl << endl;
			goto in;
			
	}
}

int Repair(){		//Product Repair
	//Show header
	system("cls");
	cout << ".......... CUSTOMER SERVICE CENTER .........." << endl << "MENU >> Home >> Product Inquiry >> Product Repair" << endl << "------------------------------" << endl;
	
	//Info input
	string buffer, address;
	int year, month, day;
	getline(cin, buffer);
	int model = productModel(), number = productNumber(model);
	cout << "Purchase date (YYYY MM DD): ";					cin >> year >> month >> day;
	cout << "Address: ";			getline(cin, buffer);	getline(cin, address);
	
	//Warranty check
	struct tm buy = {0,0,0,day,month-1,year-1900};
    time_t t1 = mktime(&buy), t2 = time(NULL);
	
	//Save Log
	cout << "Thank you for your report. Your repair number is: " << setw(7) << setfill('0') << ++repairNum << endl;
	sData << " > repair";			stepCount++;			pairCount++;
	sData << endl << endl << "RepairNo." << setw(7) << setfill('0') << repairNum << endl << "|-ProductModel = " << model << endl << "|-ProductNumber = " << number << endl << "|-PurchaseDate = " << year << month << day << endl << "|-Address = " << address << endl;
	
	//Bill Generate
	if(difftime(t2, t1) > 31536000){
		cout << "\nDue to your warranty has expired, you will have to pay a fee for repairing the product.\n\n********** Repair Request Bill **********" << endl << "Customer ID: " << id << endl << "Product Number: " << number << endl << "Product repair fee: $" << (int)(difftime(t2, t1) / 31536000)*100 << endl << "*****************************************";
		sData << "|-Fee = " << (int)(difftime(t2, t1) / 31536000)*100 << endl;
	}
	
	endMenu();

}

int Return(){	//Product Return FIN
	//Show header
	system("cls");
	cout << ".......... CUSTOMER SERVICE CENTER .........." << endl << "MENU >> Home >> Product Inquiry >> Product Return" << endl << "------------------------------" << endl;
	
	//Save Log
	cout << "Thank you for your report. Your return number is: " << setw(7) << setfill('0') << ++returnNum << endl;
	sData << " > return";			stepCount++;			returnCount++;
	sData << endl << endl << "ReturnNo." << setw(7) << setfill('0') << returnNum << endl;
	
	endMenu();
}

int inq(){			//Inquiry Menu FIN
	//Show header
	system("cls");
	cout << ".......... CUSTOMER SERVICE CENTER .........." << endl << "MENU >> Home >> Product Inquiry" << endl << "------------------------------" << endl;
	cout << "Which kind of demand do you need?\n  0)Back\n  1)Product Repair\n  2)Product Return\n";
	
	//Save log
	sData << " > inquire";			stepCount++;			inqCount++;
	
	//Menu choose
	int func;
	in: cin >> func;
	switch(func){
		case 1: Repair(); break;
		case 2: Return(); break;
		case 0: main(); break;
		default:
			cout << "Invalid input! Please choose again." << endl;
			goto in;
	}
}

int endMenu(){
	int func;
	cout << endl << endl << "Enter 0 to logout or 1 to go back to the main menu.\n";
	in:cin >> func;
	switch(func){
		case 0: id = 0; sData << endl << "steps = " << stepCount << endl; main(); break;
		case 1: main(); break;
		default:
			cout << "Invalid input! Please choose again." << endl;
			goto in;
	}
}

int productModel(){
	string model, help="help";
	cout << "Product Model: ";
	in:getline(cin, model);
	if (!model.compare(modelName[0]))return 0;
	else if (!model.compare(modelName[1]))return 1;
	else if (!model.compare(modelName[2]))return 2;
	if (!model.compare(help)){
		for(int j = 0 ; j <= 2 ; j++){
			cout << "*" << modelName[j] << "  ";
		}
		cout << endl;
		goto in;
	}
	else{
		cout << "Can\'t find this product, please enter again!\n To check the product list, enter\"help\"" << endl;
		goto in;		
	}
}

int productNumber(int model){
	int number;
	cout << "Product Number: ";
	in:cin >> number;
	if(number <= numberRange[model][0] && number >= numberRange[model][1])	return number;
	else{
		cout << "Can\'t recognize your product number, please enter again!" << endl;
		goto in;		
	}
}

int main(){		//Main Menu FIN
	//Check login status		//DO NOT USE goto
	login:if(id == 0)			Login();
	
	//Show header
	system("cls");				//DO NOT USE system
	cout << ".......... CUSTOMER SERVICE CENTER .........." << endl << "MENU >> Home" << endl << "------------------------------" << endl;
	cout << "Please choose which service you want.\n  1)Product usage\n  2)Product Inquiry\n  3)Logout and exit\n";
	
	//Save log
	sData << " > home";				stepCount++;
	
	//Menu choose
	int func;
	in:cin >> func;
	switch(func){
		case 1: Usage(); break;
		case 2: inq(); break;
		case 3:
			id = 0;
			sData << endl << "steps = " << stepCount << endl;
			goto login;
		default:
			cout << "Invalid input! Please choose again." << endl;
			goto in;
	}

	return 0;
}

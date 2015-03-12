#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

int main()
{
    //Define variables
    string billing_date;
    char firstname[100], date1[100], date2[100], pay_date[100];
    float base, local, international;

    //Get variables
    cout << "billing_date: ";
    getline(cin, billing_date);
    cout << "firstname: ";
    cin >> firstname;
    cout << "date1: ";
    cin >> date1;
    cout << "date2: ";
    cin >> date2;
    cout << "base: ";
    cin >> base;
    cout << "local: ";
    cin >> local;
    cout << "international: ";
    cin >> international;
    cout << "pay_date: ";
    cin >> pay_date;

    //Clean the screen
    system("cls");

    //Print out results
    cout << billing_date << endl << "Dear " << firstname << " customer:" << endl << "The following is this month's billing details." << endl << endl << "Bill cycle: from " << date1 << " to " << date2 << endl << endl << "Base plan:.....................................$" << fixed << setprecision(2) << base << endl << "Local calls:....................................$" << local << endl << "International calls:...........................$" << international << endl << "Tax: ($" << base << "+$" << local << "+$" << international << ")*9%...................$" << (base+local+international)*0.09 << endl << "Total:.........................................$" << (base+local+international)*1.09 << endl << endl << endl << "Please pay the above total by " << pay_date << "." << endl << endl << "Billing Department" << endl << "One Telecommunication";
    return 0;
}

#include <iostream>
#include <cmath>
using namespace std;

int main(){
	
// 1 : Define basic variables, read in data.
//Definition : a=a1+a2*(2^-8), b=b1+b2*(2^-8)
	unsigned int m, n, p, q;
	unsigned char a1, a2, b1, b2; 							
	cin >> m >> n >> p >> q;
	a1 = m, a2 = n, b1 = p, b2 = q;
	
// 2 : Calculate a*b(shifted) with unsigned chars above and save to abS
//My Method : left shift all the chars 16 bit to calculate, and shift back after calculation.
	unsigned int abS = ( (a1*b1) << 16 ) + ( (a1*b2) << 8 ) + ( (a2*b1) << 8 ) + ( a2 * b2 );
	
// 3 : Shift back, save Integer and Fractional parts (also their overflow parts) into separate char.
//Definition : a*b = intA + intB*(2^8) + fracA*(2^-16) + fracB*(2^-8)
	unsigned char intA, intB, fracA, fracB;
	intB = (abS>>16) >> 8;
	intA = (abS>>16) - (intB<<8); 
	fracA = ( abS - ( (abS>>16) << 16 ) );
	fracB =  ( abS - ( (abS>>16) << 16 ) )>>8;
	
// 4 : Calculate and save the original a*b value to abO. Output all the answers.
	double abO = intB*pow(2,8) + intA + fracA*pow(2,-16) + fracB*pow(2,-8);
	cout << "a*b = " << abO << " = " << static_cast<int>(intA) << " + " << static_cast<int>(intB) << "*(2^8) + " << static_cast<int>(fracA) << "*(2^-16) + " << static_cast<int>(fracB) << "*(2^-8)" << endl;
    
// 5 : Verify the result by using float to calculate directly.
	float fa = a1+a2*pow(2,-8), fb = b1+b2*pow(2,-8);
	cout << "Check:" << fa*fb << endl;
    
    return 0;
}

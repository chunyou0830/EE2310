#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
using namespace std;

int main(){
// 1 Define variables
	float y=0, yo=0, yn=0, x=0, xo=0, xn=0, s, n=0;

// 2 Open target file
	ofstream opf;
	opf.open("Result.csv");

// 3 Print out headings
	cout << left << setw(7) << "s" << left << setw(7) << "xo[i]" << left << setw(7) << "x[i]" << endl;
	opf << "s,xo[i],xn[i],x[i],yo[i],yn[i],y[i]" << endl;
	
// 4 Using "for" to calculate one item each time, calculate the next item the second time of the loop. Print & save the result.
// Method : Variables befor the second circle calculation == The result of the previous one --> Same meaning as [i-1] !!
	for(n=0;n<=10;n++){
		s=0.2*n;
		xo=sqrt(s)*3;
		xn=xo+((double)rand()*2 / RAND_MAX - 1);
		x=xo+sin(10*s);
		yo=(0.85*yo) + (0.15*xo);
		yn=(0.85*yn) + (0.15*xn);
		y=(0.85*y) + (0.15*x);
		
		cout << fixed << showpoint << setprecision(3) << left << setw(7) << s << left << setw(7) << xo << left << setw(7) << x << endl;
		opf << s << "," << xo << "," << xn << "," << x << "," << yo << "," << yn << "," << y << endl;
	}
	
// 5 Close file
	opf.close();
	
	return 0;
}

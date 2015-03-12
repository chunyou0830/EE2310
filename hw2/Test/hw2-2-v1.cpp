#include <iostream>
#include <cmath>
using namespace std;

int main(){
	//-----MY OWN SOLUTION-----
	//m~q = cin buffer, atb = "a*b"
	unsigned char a1, a2, b1, b2;
	int m, n, p, q;
	float c1, c2, c0, d1, d2, d3, d4;
	int atb;
	
	//save buffer to char
	cin >> m >> n >> p >> q;
	a1 = m, a2 = n, b1 = p, b2 = q;
	
	//use char to calculate a*b, all left shift 16
	atb = ( (a1*b1) << 16 ) + ( (a1*b2) << 8 ) + ( (a2*b1) << 8 ) + ( a2 * b2 );
	
	//                      --int part--- + -----------------frac part----------------
	cout << "My Ans " << ( atb >> 16 ) + ( atb - ( (atb>>16) << 16 ) ) * pow(2,-16) << endl ;
	
	//-----SECOND SOLUTION-----
	c0 = (atb>>16) >> 16;
	c1 = (atb>>16)-( ( (atb>>16) >> 16 ) << 16 );
	c2 = ( atb - ( (atb>>16) << 16 ) ) * pow(2,-16);
	cout << "Test answer " << c1+c2 << endl;
	
	unsigned char final_int = c1;
	unsigned char final_frac = ( atb - ( (atb>>16) << 16 ) );
	cout << " " << static_cast<int>(final_int) << " " << static_cast<int>(final_frac) << endl;
	
	//-----THIRD SOLUTION-----
	/*float a=a1+(float)a2/256,b=b1+(float)b2/256;
    double ans=a*b;
    unsigned char ans1=((int)ans)%128;
    unsigned char ans2=((int)(ans*128))%128;
    cout<<(int)ans1<<" "<<(int)ans2<<endl;
    cout<<"His Ans "<<ans<<endl;*/
    
    //-----FORTH SOLUTION----
    /*d1 =  a1*b1 +( (a1*b2+a2*b1)  >> 8);
    d2 = ((a1*b2+a2*b1)%128 + a2*b2) >> 8;
    cout << d1+d2;*/
    
    return 0;
}

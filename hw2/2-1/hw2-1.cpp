#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    //USING FLOAT
    float f_T1, f_T2, f_u, f_v;
    cin>>f_u>>f_v;
    f_T1=sin(f_u)+sin(f_v);
    f_T2=2*sin((f_u+f_v)/2)*cos((f_u-f_v)/2);
    cout<<"Using float"<<endl<<f_T1<<endl<<f_T2<<endl<<endl;

    //USING DOUBLE
    double d_T1, d_T2, d_u, d_v;
    cin>>d_u>>d_v;
    d_T1=sin(d_u)+sin(d_v);
    d_T2=2*sin((d_u+d_v)/2)*cos((d_u-d_v)/2);
    cout<<"Using double"<<endl<<d_T1<<endl<<d_T2<<endl;
    return 0;

}

#include <iostream>
using namespace std;
class ConstExample
{
int x;
public:
ConstExample(int a){ x = a;}
void setValue(int);
int getValue() const;
};
int ConstExample::getValue() const
{
	x=3;
return x;
}
int main(){
	ConstExample x(1); 
	cout << x.getValue();
	return 0;
}


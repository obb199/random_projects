#include <iostream>
#include <math.h>

using namespace std;

double f(double x){
	return pow(x,3) - x + 5; // f(x) = x³ - x + 5  , F(x) = x**4 / 4 - x² / 2 + 5*x , dy/dx = 3x**2 - 1
	                                                        
}

double integral(float a, float b){ //extremuns of integration
	int sums = (unsigned int)(b-a) * 10000;
	double increase = (b-a)/sums;
	long double area = 0;
	
	for(register double i = a; i < b; i += increase){
		area += f(i)*(increase);
	}
	
	return area;
}

double derivative(double x){ 
	double increase = 0.0000001;
	return (f(x+increase) - f(x))/(increase);
}

int main(){
	cout << integral(10, 25) << " u.a" << endl;
	cout << derivative(5);
	
	return 0;
}

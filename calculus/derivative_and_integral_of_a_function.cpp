#include <iostream>
#include <math.h>

using namespace std;

double f1(double x){
	return pow(x,3) - x + 5; // f(x) = x³ - x + 5  , F(x) = x**4 / 4 - x² / 2 + 5*x + k , dy/dx = 3x**2 - 1	                                                        
}

double f2(double x){
	return x + 3;  // f(x) = x + 3, F(x) = x²/2 + 3x + k, dy/dx = 1
}

double f3(double x){
	return cos(x); //f(x) = cos(x), F(x) = sen(x), dy/dx = -sen(x)
}



double integral(float a, float b){ //extremuns of integration
	int sums = (unsigned int)(b-a) * 10000;
	double increase = (b-a)/sums;
	long double area = 0;
	
	for(register double i = a; i < b; i += increase){
		area += abs(f1(i)*(increase));
		//area += abs(f2(i)*(increase));
		//area += abs(f3(i)*(increase));
	}
	
	return area;
}

double derivative(double x){ 
	double increase = 0.0000001;
	return (f1(x+increase) - f1(x))/(increase);
	//return (f2(x+increase) - f2(x))/(increase);
	//return (f3(x+increase) - f3(x))/(increase);
}

int main(){
	cout << integral(10, 25) << " u.a" << endl;
	cout << derivative(5);
	
	return 0;
}

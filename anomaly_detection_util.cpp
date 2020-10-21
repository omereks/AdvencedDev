#include "anomaly_detection_util.h"
#include <cmath>
#include <iostream>
#include <stdlib.h>
using namespace std;

static float avg(float* x, int size) {
    float pi=0, sum=0;
    for(int i=0; i < size; i++) {
        sum += x[i]; 
    }
    if (size * sum == 0) {
        return 0;
    }
    pi = (float) 1 / size * sum;
    return pi;
}

float var(float* x, int size) {
    //omer was her
    float var1 , sumPow=0, pi = 0;
    for(int i=0; i < size; i++) {
//        sum += x[i];
          sumPow += pow(x[i] , 2);
    }        
         
//    pi = (float) 1 / size * sum;
    pi = avg(x , size);
        if (size * sumPow == 0) {
        return 0;
    }
    var1 = (float) 1 / size * sumPow - pow(pi , 2);
    return var1; 
}

float cov(float* x, float* y, int size) {
    float covarince = 0, sum = 0;
    for(int i = 0; i < size; i++) {
        sum += (x[i] - avg(x , size)) * (y[i] - avg(y , size));
    }

    covarince = sum / size;   
    return covarince;
}

float pearson(float* x, float* y, int size) {
    float pear = cov(x, y, size) / sqrt(var(x , size)) * sqrt(var(y , size));
    return pear; 
}

Line linear_reg(Point** points, int size){
    float a, b;
    float x[size], y[size];
    for(int i = 0; i < size; i++) {
        x[i] = points[i]->x;
        y[i] = points[i]->y;
    } 
    a = cov(x , y, size) / var(x , size);
    b = avg(y , size) - a * avg(x , size);
    return Line(a, b);  
}

float dev(Point p,Point** points, int size){
    float fx, dis;
    Line l = linear_reg(points , size);
    fx = l.f(p.x);
    dis = abs(fx - p.y);
return dis;

}

float dev(Point p,Line l) {
return 0;
}

bool wrong(float val, float expected){
	return val<expected-0.001 || val>expected+0.001;
}

// this is a simple test to put you on the right track
int main(){
	const int N=10;
	float x[]={1,2,3,4,5,6,7,8,9,10};
	float y[]={2.1,4.2,6.1,8.1,10.3,12.2,14.4,16.1,18.2,20.3};

	Point* ps[N];
	for(int i=0;i<N;i++)
		ps[i]=new Point(x[i],y[i]);

	Line l=linear_reg(ps,N);
	Point p(4,8);

	float v[]={var(x,N),cov(x,y,N),pearson(x,y,N),l.a,l.b,l.f(4),dev(p,l)};
	float e[]={8.25,16.63,0.999,2.015,0.113,8.176,0.176};


	for(int i=0;i<7;i++)
		if(wrong(v[i],e[i]))
			cout<<"error for check "<<i<<" (-14)"<<endl;


	for(int i=0;i<N;i++)
		delete ps[i];

	cout<<"done"<<endl;
	return 0;
}
// int main() {
// int size;
// cout << "please enter size\n";
// cin >> size;
// float x [size];
// float var1; 
// cout << "please enter X\n";
// for(int i=0; i<size; i++){
//     cin >> x[i];    
// }
// var1 = var(x, size);
// cout << var1 << "\n";
// for(int i=0; i<size; i++){
// cout << x[i] << "\n";    
// }
// cout << *x;
//     return 0;
// }
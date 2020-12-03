#include "timeseries.h"
#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <vector>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
using namespace std;








//insert Row

//get Row
vector<float> TimeSeries::getRow(int r){
    return (this->vecCSV[r]);
}


//getting te vector

//getting specific IJ

float TimeSeries::getVal(int r, int c){
    float valr = this->vecCSV[r][c];
    return (valr);
}

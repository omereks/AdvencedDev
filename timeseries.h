#ifndef TIMESERIES_H_
#define TIMESERIES_H_
#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
using namespace std;


class TimeSeries{
private:
    void creatVectorFromCSV(const char* CSVfileName){
        vector<vector<float>> vecrCSV;
        ifstream  csv;
        bool flag = true;
        csv.open(CSVfileName);
        string strLine, val;
        while (getline(csv, strLine))
        {
            vector<float> vecLine;
            stringstream s(strLine);
            if(flag)
            {
                while (getline(s, val, ','))
                {
                    this->features.push_back(val);
                }
                flag = false;
            }
            else
            {
                while (getline(s, val, ','))
                {
                    vecLine.push_back(stof (val));
                }
                this->vecCSV.push_back(vecLine);
            }
        }
    }


public:
	string fileName;
    vector<vector<float>> vecCSV;
    vector<string> features;
    

    TimeSeries(const char* CSVfileName) : fileName(CSVfileName){
        this->creatVectorFromCSV(CSVfileName);
    }
    
    float getVal(int r, int c){
        return (this->vecCSV[r][c]);
    }

    vector<float> getRow(int r){
        return (this->vecCSV[r]);
    }

    void getColumn(float* arrC, int c){
        vector<float> curVec;
        float curVal;
        int i = 0;
        for (int i = 0 ; i < this->vecCSV.size() ; i++)
        {
            arrC[i] = this->vecCSV[i][c];
        }
    }

    void addRow(float a, float b, float c, float d){
        vector<float> vecAdd;
        vecAdd.push_back(a);
        vecAdd.push_back(b);
        vecAdd.push_back(c);
        vecAdd.push_back(d);

        this->vecCSV.push_back(vecAdd);
    }

};





#endif /* TIMESERIES_H_ */

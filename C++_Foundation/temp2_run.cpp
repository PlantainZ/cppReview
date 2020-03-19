#include<stdio.h>
#include<iostream>
#include<string>
#include<iomanip>
using namespace std;


int main(){
    string str1 = "方铎泠 泠泠 东海黑龙 白化";
    string str2 = "";
    str2.assign(str1);
    int position=0;
    string result[4] = {"","","",""};

    for(int i=0;i<3;i++){
        position = str2.find(" ");
        result[i] = str2.substr(0,position);
        str2 = str2.substr(position+1,str2.length()-position);
    }

    result[3] = str2;
    for(int i=0;i<4;i++){
        cout<<result[i]<<endl;
    }
    //合并回去
    str2.swap(result[0]);
    for(int i=1;i<4;i++){
        str2+=" ";
        str2.append(result[i]);
    }
    bool equall=str2.compare(str1);

    cout<<"str2:"<<str2<<endl;
    cout<<"equall:"<<equall<<endl;

}

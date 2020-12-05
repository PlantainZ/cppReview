#include<stdio.h>
#include<iostream>

class Solution{
    public static double power(double base,int exponent){
        bool flag = exponent < 0;
        if(flag){ exponent = -exponent;}
        double result = getPower(base,exponent);
        return flag? 1/result:result;
    };

    public static double getPower(double base,int exponent){
        if(exponent==0) return 0;
        if(exponent==1) return base;

        int ans = getPower(base,exponent>>1)
    }
};

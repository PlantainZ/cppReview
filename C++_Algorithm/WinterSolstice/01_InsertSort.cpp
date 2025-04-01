#include<stdio.h>
#include<iostream>
#include<iomanip>
using namespace std;

// 插入排序 【运行正常】

void main() {
    // 可更改设置 ======================
    int a[8] = { 5,8,9,3,21,4,7,6 };
    int tmp;
    int n = 8;
    int i, j;

    // 初始数据=========================
    for (i = 0; i < n; i++)
        cout << "a_original：" << a[i] << endl;

    // 插入排序==========================

    for (i = 1; i < n; i++) {
        tmp = a[i - 1];
        if (a[i] < tmp) {
            tmp = a[i];

            for (j = i - 1; a[j] > tmp; j--) a[j + 1] = a[j];
            a[j + 1] = tmp;
        }
    }

    // 最终结果===========================
    for (i = 0; i < n; i++)
        cout << "a插入排序后的样子：" << a[i] << endl;
}
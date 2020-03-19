
#include<stdio.h>
///【1.插入排序: 简单插入】
#include<iostream>

//此处为简单插入排序
void easySelectSort(ElemType A[],int n){

    for(int i=0;i<n-1;i++){
        int min=i;
        for(int j=i;j<n;j++){
            if(A[j] < A[min]) min=j;

        if(min!=i) swap(A[i],A[min]);

        }

    }
}



///【2.归并排序】

ElemType *B=(ElemType*)malloc( (n+1)*malloc(sizeof(ElemType)) )
//这是辅助数组


void Merge(ElemType A[],int low,int mid,int high){
    //表A的两段A[low...mid] & [mid...high]各自有序，将他们合并

    for (int k=low;k<=high;k++) B[k]=A[k]
    //A才是原数组，B只是个缓冲区
    for (i=low,j=mid+1,k=i;low<=mid && j<high;k++){
        if(B[i]<B[j]) A[k]=B[i++];
        else A[k]=B[j++];
    }

    while(i<=mid) A[k++]=B[i++];
    while(j<=high) A[k++]=B[j++];
    //注意一下这里的技巧
}

//合并两个已经排序的子表得到结果
void MergeSort(ElemType A[],int low,int high){
    if(low<high){
        int mid=(low+high)/2;
        MergeSort(A[],low,mid);
        MergeSort(A[],mid+1,high);
        Merge(A[],low,mid,high);
    }
}

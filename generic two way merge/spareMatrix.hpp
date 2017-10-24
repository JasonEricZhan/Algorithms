//
//  spareMatrix.hpp
//  generic_mergesort
//
//  Created by Eric on 2017/9/28.
//  Copyright © 2017年 Eric. All rights reserved.
//

#ifndef spareMatrix_hpp
#define spareMatrix_hpp

#include <vector>
#include "merge.hpp"
#include <iostream>
#include <cstddef>

struct matrixTerm
{

    int row;int col;int value;
};


class spMatrix
{
public:
    spMatrix(){capacity=0;term_num=0;};
    template <size_t d0, size_t d1>
    spMatrix(int (&arr)[d0][d1]);
    spMatrix(int capacity_num,int row_num,int col_num,int terms){
            smArray=new matrixTerm[capacity_num];
            capacity=capacity_num;
            rows=row_num;cols=col_num;term_num=terms;};
    
    matrixTerm* getArray(){
        matrixTerm *temp=new matrixTerm[capacity];
        for(int i=0;i<capacity;i++)//copy
        {
            temp[i]=smArray[i];
        }
        return temp;}; 
    void setArray(matrixTerm *arr,int size){
        capacity=size;
        delete []smArray;
        smArray=new matrixTerm[capacity];
        for(int i=0;i<capacity;i++)//copy
        {
            smArray[i]=arr[i];
        }};
    
    int getCapacity(){return capacity;};
    
    int getRows(){return rows;}; 
    int getCols(){return cols;};
    int getTerms(){return term_num;};
    
       
    void storeSum(const int sum,const int row,const int col);
    matrixTerm* colMajor();
    spMatrix mul(spMatrix b);
    

    ~spMatrix(){};
    
    
private:
    int capacity;
    int rows;int cols;int term_num;
    matrixTerm* smArray;
    int sum;
};


template <size_t d0, size_t d1>
spMatrix::spMatrix(int (&arr)[d0][d1])
{
    capacity=0;
    for (size_t i = 0; i < d0; i++)
    {
        for (size_t j = 0; j < d1; j++)
        {
            if(arr[i][j]!=0)
            {
                capacity++;
            }
        }
    }
    term_num=0;
    smArray=new matrixTerm[capacity];
    for (size_t i = 0; i < d0; i++)
    {
        for (size_t j = 0; j < d1; j++)
        {
            if(arr[i][j]!=0)
            {
                smArray[term_num].row=static_cast<int>(i);
                smArray[term_num].col=static_cast<int>(j);
                smArray[term_num].value=arr[i][j];
                term_num++;
            }
        }
    }
    if(capacity!=term_num)
    {
        cout<<"error for capacity and term_num counting"<<endl;
        exit(9);
    }
}



#endif /* spareMatrix_hpp */

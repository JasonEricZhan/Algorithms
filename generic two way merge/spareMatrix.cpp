//
//  spareMatrix.cpp
//  generic_mergesort
//
//  Created by Eric on 2017/9/28.
//  Copyright © 2017年 Eric. All rights reserved.
//

#include "spareMatrix.hpp"

using namespace std;

inline bool operator<(const matrixTerm a,const matrixTerm b)
{
    return a.col<b.row;
}

inline bool operator==(const matrixTerm a,const matrixTerm b)
{
    return a.col==b.row;
}



void spMatrix::storeSum(const int sum,const int row,const int col)
{
   if(sum!=0)
   {
      if(term_num<=capacity)
      {
        smArray[term_num].row=row;
        smArray[term_num].col=col;
        smArray[term_num].value=sum;
        term_num++;
      }
      else
      {
          cout<<"matrix overflow"<<endl;
          exit(9);
      }
   }
}

void multiply_wrapper(int &aPtr,int &bPtr,matrixTerm *arr_a,matrixTerm *arr_b,int &sum,int flag)
{
    if(flag==1 or flag==4)
    {
        aPtr++;
    }
    else if(flag==3 or flag==5)
    {
        bPtr++;
    }
    else if(flag==2)
    {
        sum+=arr_a[aPtr].value*arr_b[bPtr].value;
        aPtr++;bPtr++;
    }
}

function<void(int &aPtr,int &bPtr,matrixTerm *arr_a,matrixTerm *arr_b,int &sum,int flag)> sp_func =multiply_wrapper;


matrixTerm* spMatrix::colMajor()
{
    matrixTerm *output=new matrixTerm[term_num];
    int *count=new int[cols+1];
    int *start=new int[cols+1];
    for (int i=0;i<cols;i++)
        count[i]=0;
    for (int i=0;i<term_num;i++)
        count[smArray[i].col]++;
    for (int i=1;i<cols;i++)
        start[i]=start[i-1]+count[i-1];
    for (int i=0;i<term_num;i++)
    {
        output[start[smArray[i].col]]=smArray[i];
        start[smArray[i].col]++;
    }
    delete []count;delete []start;
    return output;
}


spMatrix spMatrix::mul(spMatrix b)
{
    if(cols!=b.getRows())
    {
        cout<<"not compatible shape"<<endl;;
        exit(9);
    }
    else
    {
        spMatrix newMatrix(rows*b.getCols(),rows,b.getCols(),0);
        
        
        matrixTerm* colbsmArray=b.colMajor();
        

        vector<int> aPtrbound;
        for(int i=0;i<term_num-1;i++)
        {
            if(smArray[i].row!=smArray[i+1].row)
            {
                aPtrbound.push_back(i+1);
            }
        }
        aPtrbound.push_back(term_num);
        
        
        vector<int> bPtrbound;
        for(int i=0;i<b.getTerms()-1;i++)
        {
            if(colbsmArray[i].col!=colbsmArray[i+1].col)
            {
                
                 bPtrbound.push_back(i+1);
            }
        }
        bPtrbound.push_back(b.getTerms());
        
        int sum=0;
        
        int bTerms=b.getTerms();
        int aPtr=0;int bPtr=0;
        int currRow=smArray[aPtr].row;
        int currCol=colbsmArray[bPtr].col;
        int la=0;int lb=0;
        int aStarter=0;
        //matrix a  by row major,matrix b by column major, operation is a*b
        while(aPtr<term_num)
        {
            while(bPtr<=bTerms)    
            {   
                if(aPtr>=aPtrbound[la] or bPtr>=bPtrbound[lb])
                {
                    newMatrix.storeSum(sum,currRow,currCol);
                    sum=0;
                    aPtr=aStarter;
                    if(bPtr==bTerms)
                    {
                        break;
                    }
                    while(colbsmArray[bPtr].col==currCol)
                    {
                        bPtr++;
                    }
                    currCol=colbsmArray[bPtr].col;
                }
                else
                {
                    list spMerge(aPtrbound[la], bPtrbound[lb],aPtr,bPtr);
                    spMerge.merge(smArray, colbsmArray,sp_func,sum);
                    aPtr=spMerge.get_lPtr();bPtr=spMerge.get_rPtr();
                    lb++;
                }
            }
            la++; 
            lb=0;
            while(smArray[aPtr].row==currRow)
            {
                aPtr++;   
            }
            aStarter=aPtr;
            currRow=smArray[aPtr].row;
            currCol=colbsmArray[0].col;
            bPtr=0;
        }
        delete []colbsmArray;
        if(newMatrix.getCapacity()>newMatrix.getTerms())//clean out some unnecessary space
        {
            matrixTerm* newSmArray=newMatrix.getArray();
            matrixTerm *temp=new matrixTerm[newMatrix.getTerms()];
            int ptr=newMatrix.getTerms()-1;
            for(;ptr>=0;ptr--)
            {
                temp[ptr]=newSmArray[ptr];
            }
            newMatrix.setArray(temp,newMatrix.getTerms());
            delete [] newSmArray;
            
        }
        return newMatrix;
        
    }
}


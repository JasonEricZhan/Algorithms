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

//store it to the std function, then can reuse it
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
        
        //change to column major
        matrixTerm* colbsmArray=b.colMajor();
        
        
        //store the changing row ,column boundary for a and b
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
            while(bPtr<=bTerms)//multiply all the b's element by a's one row
            {//trick:bPtr going to bTerms is to put the result of last summation operation in storeSum
                
                if(aPtr>=aPtrbound[la] or bPtr>=bPtrbound[lb])//end of row
                {
                    newMatrix.storeSum(sum,currRow,currCol);
                    sum=0;
                    aPtr=aStarter;//initialize to the same row, ready to start again
                    if(bPtr==bTerms)//prevent some ambiguous
                    {
                        break;
                    }
                    //put in front of while loop for saving a little time
                    while(colbsmArray[bPtr].col==currCol)
                        //The b pointer isn't point to the next column elements?
                    {
                        bPtr++;//if doesn't point to the next column elements, the b pointer has to go to next column
                    }
                    currCol=colbsmArray[bPtr].col;
                }
                else
                {
                    //set the value of starters and boundary
                    list spMerge(aPtrbound[la], bPtrbound[lb],aPtr,bPtr);
                    spMerge.merge(smArray, colbsmArray,sp_func,sum);
                    aPtr=spMerge.get_lPtr();bPtr=spMerge.get_rPtr();
                    lb++;
                }
            }
            la++; //go to next boundary label for a
            lb=0;//go back to first boundary label for b
            while(smArray[aPtr].row==currRow)//complete a's one row multiply
            {
                aPtr++;    //go to next next row for a
            }
            aStarter=aPtr;//record the next column position for a
            currRow=smArray[aPtr].row;//record  next row for a 
            currCol=colbsmArray[0].col;//record the column of first element for b
            bPtr=0;//go to the first element for b
        }
        
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


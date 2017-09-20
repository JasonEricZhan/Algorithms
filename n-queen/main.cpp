//
//  main.cpp
//  8-queen
//
//  Created by Eric on 2017/9/20.
//  Copyright © 2017年 Eric. All rights reserved.
//

#include <iostream>


void  back_tracking(int *col,int row,int n);

bool promising(const int col[],int checked_index);

template <class T3>
void output_result(const T3 s[],T3 &the_ith_solution,int n);

using namespace std;

int the_ith_solution=1; //the variable record the solution is ith
int main(void) {
    int n=0;
    do{
        
    cout<<"How many queens(must bigger than 4)"<<endl;
    cin>>n;
        
    }while(n<4);
    srand(time(NULL));
    int col[n];
    
    col[0]=rand()%n;
    cout<<"==first queen at "<<col[0]+1<<"th column =="<<endl;
    back_tracking(col,1,n);
    return 0;
}

void  back_tracking(int *col,int row,int n)
{
    for(int j=0;j<n;j++)
    {
        col[row]=j;
        if(promising(col, row))
        {
            if(row==n-1)
            {
                output_result(col,the_ith_solution,n);
                return;
                    
            }
            else
            {
                back_tracking(col,row+1,n);
            }
        }
    }
    
}


bool promising(const int col[],int checked_index)
{
    
    bool legal=true;
    for(int put_index=0;put_index<checked_index;put_index++)
    {
        if(col[put_index]==col[checked_index] ||
           abs(col[checked_index]-col[put_index])==checked_index-put_index)
        {
            legal=false;
        }
    }
    return legal;
}

template <class T3>
void output_result(const T3 s[],T3 &the_ith_solution,int n)
{
    std::cout<<the_ith_solution<<"th solution is"<<std::endl;
    for(int i=0;i<n;i++)
    {
        int row=i;
        int col=s[i];
        for(int j=0;j<n;j++)
        {
            if(i==row && j==col)
            {
                cout<<" "<<'Q'<<" ";
            }
            else
            {
                cout<<" "<<'.'<<" ";
            }
        }
        cout<<" "<<endl;
    }
    std::cout<<"====="<<std::endl;
    the_ith_solution+=1; //change the variable of record ,add one
}

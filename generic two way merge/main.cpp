//
//  main.cpp
//  generic_mergesort
//
//  Created by Eric on 2017/9/28.
//  Copyright © 2017年 Eric. All rights reserved.
//

#include <iostream>

#include "merge.hpp"// std is from there
#include "polynomial.hpp"
#include "spareMatrix.hpp"
#include <fstream>




void list_wrapper(int &leftPtr,int &rightPtr,int *arr_left,int *arr_right,list &l,int flag)
{
    if(flag==1 or flag==4)
    {
        l.assignValue(arr_left[leftPtr]);
        leftPtr++;
    }
    if(flag==2 or flag==3 or flag==5)
    {
        l.assignValue(arr_right[rightPtr]);
        rightPtr++;
    }
    
}

//store it to the std function, then can reuse it
function <void(int &,int &,int *,int *,list &l,int)>list_func=list_wrapper;




using std::ifstream;

int main(int argc, const char * argv[]) {
    ifstream ifile;
    ifile.open("testdata.txt",ios_base::in);
    if(ifile.is_open() && ifile.good())//prevent some problem
    {
       
             cout<<"start reading file"<<endl;
             //list operation :get data
             int n1=0;int n2=0;
             ifile>>n1;
             int array1[n1+1];
             for(int i=0;i<n1;i++)
             {
                 ifile>>array1[i];
             }

            ifile>>n2;
            int array2[n2+1];
            for(int i=0;i<n2;i++)
            {
              ifile>>array2[i];
            }
            
            //list operation :do merge
            list merge(n1+n2,0,n1,n2,0,0);
            merge.merge(array1,array2,list_func,merge);
            cout<<endl;
            
            for(int i=0;i<n1+n2;i++)
            {
                cout<<merge.pop_array(i)<<" ";
            }
            cout<<endl;
            cout<<"==merge==complete=="<<endl;
            cout<<endl;
            
            //poly operation :get data
            int n3=0;int n4=0;
            ifile>>n3;
            poly a(n3,n3);
            term* a_arr=a.getArray();
            for(int i=0;i<n3;i++)
            {
                ifile>>a_arr[i].coef;
                ifile>>a_arr[i].exp;
            }
            a.setArray(a_arr,n3);
            delete []a_arr;
        
            ifile>>n4;
            poly b(n4,n4);
            term* b_arr=b.getArray();
            for(int i=0;i<n4;i++)
            {
                ifile>>b_arr[i].coef;
                ifile>>b_arr[i].exp;
            }
            b.setArray(b_arr,n4);
            delete []b_arr;
    
            //poly operation :do add
            poly c=a.add(b);
            term* c_arr=c.getArray();
            for(int i=0;i<c.getCapacity();i++)
            {
                cout<<c_arr[i].coef<<"*X^"<<c_arr[i].exp<<endl;
            }
            cout<<"==poly==complete=="<<endl;
            cout<<endl;
        
            
            //matrix operation :get data
            int n5=0;int n6=0;
            int d1=0;int d2=0;int d3=0;
            ifile >> n5>> d1>>d2 ;
        
            spMatrix Matrix1(n5,d1,d2,n5);
            matrixTerm* matrix1=Matrix1.getArray();
            int ith_term=0;
            int value=0;
            for(int i=0;i<d1;i++)
            {
                for(int j=0;j<d2;j++)
                {
                    ifile>>value;
                    if(value!=0)
                    {
                        matrix1[ith_term].row=i;
                        matrix1[ith_term].col=j;
                        matrix1[ith_term].value=value;
                        ith_term++;
                    }
                    value=0;
                }
           }
        
            if(ith_term!=n5)
            {
               cout<<"data size not meet"<<endl;
               exit(9);
            }
            Matrix1.setArray(matrix1,n5);
            delete []matrix1;

        
            ifile>>n6>>d2>>d3;
            spMatrix Matrix2(n6,d2,d3,n6);
            matrixTerm* matrix2=Matrix2.getArray();
            value=0;
            ith_term=0;
            for(int i=0;i<d2;i++)
            {
                for(int j=0;j<d3;j++)
                {
                    ifile>>value;
                    if(value!=0)
                    {
                        matrix2[ith_term].row=i;
                        matrix2[ith_term].col=j;
                        matrix2[ith_term].value=value;
                        ith_term++;
                    }
                    value=0;
                }
            }
            if(ith_term!=n6)
            {
               cout<<"data size not meet"<<endl;
               exit(9);
            }
            Matrix2.setArray(matrix2,n6);
            delete []matrix2;
        
            //matrix operation :do mul
            spMatrix Matrix3=Matrix1.mul(Matrix2);
            matrixTerm* matrix3=Matrix3.getArray();
        
            ith_term=0;
            for(int i=0;i<d1;i++)
            {
                for(int j=0;j<d3;j++)
                {
                    if(matrix3[ith_term].row==i && matrix3[ith_term].col==j
                       && ith_term<Matrix3.getTerms())
                    {
                        cout<<matrix3[ith_term].value<<" ";
                        ith_term++;
                    }
                    else
                    {
                        cout<<0<<" ";
                    }
                }
                cout<<" "<<endl;
            }
            cout<<"==spmatrix==complete=="<<endl;
            delete []matrix3;

            ifile.close();
    }
    else
    {
        cout<<"read file fail"<<endl;
    }
    return 0;
}






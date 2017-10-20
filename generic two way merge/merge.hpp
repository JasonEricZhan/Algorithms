//
//  merge.hpp
//  generic_mergesort
//
//  Created by Eric on 2017/9/28.
//  Copyright © 2017年 Eric. All rights reserved.
//

#ifndef merge_h
#define merge_h

#include <iostream>

using namespace std;

class list
{
public:
    list(){capacity=0;};
    list(int lb_num,int rb_num,int ls_num,int rs_num)
    {
        if(lb_num>ls_num and rb_num>rs_num)
        {
          leftBoundary=lb_num;
          rightBoundary=rb_num;
          leftStart=ls_num;
          rightStart=rs_num;
        }
        else
        {
            cout<<"boundary or starter setting fault"<<endl;
            exit(9);
        }
    }
    list(int capacity_num,int ith_num,int lb_num,int rb_num,int ls_num,int rs_num){
        capacity=capacity_num;
        output=new int[capacity];
        ith=ith_num;
        if(lb_num>ls_num and rb_num>rs_num)
        {
          leftBoundary=lb_num;
          rightBoundary=rb_num;
          leftStart=ls_num;
          rightStart=rs_num;
        }
        else
        {
            cout<<"boundary or starter setting fault"<<endl;
            exit(9);
        }
    };
    template<class T1,typename T2,typename T3>
    void merge(T1 *arr_left,T1 *arr_right,T2 func,T3 &container);
    int get_lPtr(){  //get the left pointer
        return leftPtr;
    };
    int get_rPtr(){//get the right pointer
        return rightPtr;
    };
    void assignValue(int num){output[ith]=num;ith++;} ;
    int  pop_array(int ptr){ return output[ptr];} ;
    ~list(){};
    
private:
    int leftBoundary;
    int rightBoundary;
    int capacity;
    int *output;
    int ith;
    int leftStart;int rightStart;
    int leftPtr;int rightPtr;
};

template<class T1,typename T2,typename T3>
void list::merge(T1 *arr_left,T1 *arr_right,T2 func,T3 &container)
/*
left sorted array and right sorted array,
func is function that depend on what work to do,
container is for passing in object, container, variable, which we want to modify.
 */
{
    leftPtr=leftStart;rightPtr=rightStart;
    while(rightPtr<rightBoundary && leftPtr<leftBoundary)
    {
        if(arr_left[leftPtr]<arr_right[rightPtr])
        {
            func(leftPtr,rightPtr,arr_left,arr_right,container,1);
        }
        else if(arr_left[leftPtr]==arr_right[rightPtr])
        {
            func(leftPtr,rightPtr,arr_left,arr_right,container,2);
        }
        else
        {
            func(leftPtr,rightPtr,arr_left,arr_right,container,3);
        }
    }
    while(leftPtr<leftBoundary)
    {
        func(leftPtr,rightPtr,arr_left,arr_right,container,4);
    }
    while(rightPtr<rightBoundary)
    {
        func(leftPtr,rightPtr,arr_left,arr_right,container,5);
    }
}

#endif /* merge_hpp */

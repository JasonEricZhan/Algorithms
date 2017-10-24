//
//  polynomial.hpp
//  generic_mergesort
//
//  Created by Eric on 2017/9/28.
//  Copyright © 2017年 Eric. All rights reserved.
//

#ifndef polynomial_hpp
#define polynomial_hpp

#include "merge.hpp"
#include <iostream>
#include <functional>

struct term
{
    float coef;
    int exp;
};

class poly
{
public:
    poly(){capacity=0;term_num=0;};
    poly(int capacity_num,int terms){
          capacity=capacity_num;
          termarray=new term[capacity];
          term_num=terms;};
    
    //safety but waste some space and time
    term* getArray(){
        term *temp=new term[capacity];
        for(int i=0;i<capacity;i++)//copy
        {
            temp[i]=termarray[i];
        }
        return temp;};
    void setArray(term *arr,int size){
        capacity=size;
        termarray=new term[capacity];
        for(int i=0;i<capacity;i++)//copy
        {
            termarray[i]=arr[i];
        }};
    
    int getCapacity(){return capacity;};
    int getTerms(){return term_num;};
 
    poly add(poly p);
    void newTerm(const float coef,const int exp);
    ~poly(){};
    
private:
    int capacity;
    int term_num;
    term *termarray;
};


#endif /* polynomial_hpp */

//
//  polynomial.cpp
//  generic_mergesort
//
//  Created by Eric on 2017/9/28.
//  Copyright © 2017年 Eric. All rights reserved.
//

#include "polynomial.hpp"


inline bool operator<(const term a,const term b)
{
    return a.exp<b.exp;
}

inline bool operator==(const term a,const term b)
{
    return a.exp==b.exp;
}

void poly::newTerm(const float coef,const int exp)
{
    if(term_num>=capacity)
    {
        cout<<"polynomail overflow"<<endl;
        exit(9);
    }
    termarray[term_num].coef = coef;
    termarray[term_num].exp = exp;
    term_num++;
}


void newTerm_wrapper(int &selfPtr,int &pPtr,term *self,term *p,poly &newp,int flag)
{
    if(flag== 2)
    {
        float sum=self[selfPtr].coef+p[pPtr].coef;
        if(sum)
        {
            newp.newTerm(sum,self[selfPtr].exp);
        }
        selfPtr++;pPtr++;
    }
    else if(flag== 1 or flag== 4 )
    {
        newp.newTerm(self[selfPtr].coef,self[selfPtr].exp);
        selfPtr++;
    }
    else if(flag== 3 or flag== 5 )
    {
        newp.newTerm(p[pPtr].coef,p[pPtr].exp);
        pPtr++;
    }
}

function<void(int &selfPtr,int &pPtr,term *self,term *p,poly &newp,int flag)>poly_func=newTerm_wrapper;

poly poly::add(poly p)
{
    term *ptermarray=p.getArray();
    int n=p.getTerms()+term_num;
    poly newpoly(n,0);
    list polyMerge(term_num,p.getTerms(),0,0);
    polyMerge.merge(termarray,ptermarray,poly_func,newpoly);
    if(newpoly.getCapacity()>newpoly.getTerms())//clean the space
    {
        term *newArray=newpoly.getArray();
        term *temp=new term[newpoly.getTerms()];
        int ptr=newpoly.getTerms()-1;
        for(;ptr>=0;ptr--)
        {
            temp[ptr]=newArray[ptr];
        }
        newpoly.setArray(temp,newpoly.getTerms());
        delete [] newArray;
        newArray=NULL;
    }
    return newpoly;
}






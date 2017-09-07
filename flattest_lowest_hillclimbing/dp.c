#include<stdio.h>
#include<stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include<math.h>
#include "dp.h"



float min(float a,float b)//return minimum value
{
    return( (a < b)? a : b); //if a is smaller than b then return a else return b
}

int slope_check(int j,int i) //check slope
{
    if(i==1 && j==0) 
    {
        return true;
    }
    else if(i==0 && j==0) //the starting point
    {
        return true;
    }
    else if(i==0 && j==1) //prevent zero diviser,so make default 
    {
        return false;
    }
    else if(i==0)  //prevent zero diviser,so make default 
    {
        return false;
    }
    //The rule of global path
    else if((j/i)>=1/2&&(j/i)<=2)
    {
        return true;
    }
    else
    {
        return false;
    }
}


float diff(int j,int i,int n,int m,float **s)
{
    float a=fabs(*(*(s+j)+i)-*(*(s+n)+m));
    return a;
}


void dp(int length,float **D,float **height,int **P)
{
   
  
    //initialize,(0,0) and (0,1~n) and (1~n,0),
    *(*(D+0)+0)=0+*(*(height+0)+0);
    *(*(P+0)+0)=0;   //because it's the starting point so is 0
    //(1,0)  is legal 
    *(*(D+0)+1)=*(*(D+0)+0)+diff(0,1,0,0,height)+*(*(height+0)+1);
    *(*(P+0)+1)=1;  //because the only way to go to (0,1) is from (0,0) and move horizon direction
    //(0,1) is illegal 
    *(*(D+1)+0)=INT_MAX;
    //other are illegal
    for(int i=2;i<length;i++)
    {
       *(*(D+i)+0)=INT_MAX;
    }
    for(int j=2;j<length;j++)
    {
        *(*(D+0)+j)=INT_MAX;
    }
    
    //start walking from (1,1)
    for(int j=1;j<length;j++)
    {
       for(int i=1;i<length;i++)
       {
           
                if(slope_check(j,i))//check the global constraint(slope) first
                {
                    //use three variable to save the value of three direction temporary
                    float diag=*(*(D+j-1)+i-1)+1.4*diff(j,i,j-1,i-1,height);
                    float horizon=*(*(D+j)+i-1)+diff(j,i,j,i-1,height);
                    float vertical=*(*(D+j-1)+i)+diff(j,i,j-1,i,height);
                    
                    /*prevent some uncertain issue made by INT_MAX adding with other numbers
                    Ex:INT_MAX+INT_MAX<0 ,INT_MAX+integar<0 at sometimes*/
                    
                    if(diag<0) 
                    {
                       diag=INT_MAX;
                    }
                    else if(horizon<0)
                    {
                       horizon=INT_MAX;
                    }
                    else if(vertical<0)
                    {
                       vertical=INT_MAX;
                    }
                    //check which previous point(direction) is illegal,if it's illegal then assign maximum value to it
                    if(!slope_check(j,i-1))
                    {
                        horizon=INT_MAX;
                    }
                    if(!slope_check(j-1,i))
                    {
                        vertical=INT_MAX;
                    }
                    if(!slope_check(j-1,i-1))
                    {
                        diag=INT_MAX;
                    }
                    
                    //finally choose the minimum cost point:
                    //record the cost
                    *(*(D+j)+i)=min(diag,min(horizon,vertical))+*(*(height+j)+i);
                    //record the direction
                    if(diag==min(diag,min(horizon,vertical))) //diag direction
                    {
                        *(*(P+j)+i)=2;
                      
                    }
                    else if(vertical==min(diag,min(horizon,vertical))) //vertical direction
                    {
                        *(*(P+j)+i)=3;
                        
                    }
                    else if(horizon==min(diag,min(horizon,vertical))) //horizon direction
                    {
                        *(*(P+j)+i)=1;
                        
                    }
                }
                else//the point which we pass by it's illegal
                {
                    *(*(D+j)+i)=INT_MAX;
                    *(*(P+j)+i)=0;
                    
                }
           
        }
            
    }                
}

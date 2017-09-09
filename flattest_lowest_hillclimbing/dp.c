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

int slope_check(int col,int row) //check slope
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


float diff(int col1,int row1,int col2,int row2,float **height)
{
    float difference=fabs(*(*(height+col1)+row1)-*(*(height+col2)+row2));
    return difference;
}


void dp(int length,float **cost,float **height,char **path)
{
   
    //initialize,(0,0) and (0,1~n) and (1~n,0),
    *(*(cost+0)+0)=0+*(*(height+0)+0);
    *(*(path+0)+0)='O';   //because it's the starting point so is O
    *(*(cost+0)+1)=*(*(cost+0)+0)+diff(0,1,0,0,height)+*(*(height+0)+1);
    *(*(path+0)+1)='H';
    *(*(cost+1)+0)=*(*(cost+0)+0)+diff(1,0,0,0,height)+*(*(height+1)+0);
    *(*(path+1)+0)='V';
    for(int i=2;i<length;i++)
    {
       *(*(cost+i)+0)=INT_MAX;
    }
    for(int j=2;j<length;j++)
    {
        *(*(cost+0)+j)=INT_MAX;
    }
    
    //start walking from (1,1)
    for(int j=1;j<length;j++)
    {
       for(int i=1;i<length;i++)
       {
           
                if(slope_check(j,i))//check the global constraint(slope) first
                {
                    //use three variable to save the value of three direction temporary
                    float diag=*(*(cost+j-1)+i-1)+1.4*diff(j,i,j-1,i-1,height);
                    float horizon=*(*(cost+j)+i-1)+diff(j,i,j,i-1,height);
                    float vertical=*(*(cost+j-1)+i)+diff(j,i,j-1,i,height);
                    
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
                    *(*(cost+j)+i)=min(diag,min(horizon,vertical))+*(*(height+j)+i);
                    //record the direction
                    if(diag==min(diag,min(horizon,vertical))) //diag direction
                    {
                        *(*(path+j)+i)='D';
                      
                    }
                    else if(vertical==min(diag,min(horizon,vertical))) //vertical direction
                    {
                        *(*(path+j)+i)='V';
                        
                    }
                    else if(horizon==min(diag,min(horizon,vertical))) //horizon direction
                    {
                        *(*(path+j)+i)='H';
                        
                    }
                }
                else//the point which we pass by it's illegal
                {
                    *(*(cost+j)+i)=INT_MAX;
                    *(*(path+j)+i)=0;
                    
                }
           
        }
            
    }                
}

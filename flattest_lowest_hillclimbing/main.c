//
//  main.c
//  flattest_lowest_hillclimbing
//
//  Created by Eric on 2017/4/19.
//  Copyright © 2017年 Eric. All rights reserved.
//

#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include "P.h"
#include "dp.h"





int main(int argc, const char * argv[]) {
    // insert code here...

    int n;
    scanf(" %2i",&n);
    
    //allocate dynamic array D[n][n]
    float **D_2D=NULL;
    D_2D = (float**)malloc(sizeof(float*)*n);//allocate n rows of space to store pointers
    if(!D_2D )
    {
        printf("Fail to allocate memory");
        exit(1);//unusual exit out the program
    }
    for(int i=0;i<n;i++)
    {
        D_2D[i]=(float*)malloc(sizeof(float)*n);//columns of i-th row
        if(!D_2D[i])
        {
            printf("Fail to allocate memory");
            exit(1);//unusual exit out the program
        }
    }
    
    //allocate dynamic array P[n][n]
    int **P_2D=NULL;
    P_2D = (int**)malloc(sizeof(int*)*n);//allocate n rows of space to store pointers
    if(!P_2D )
    {
        printf("Fail to allocate memory");
        exit(1);//unusual exit out the program
    }
    for(int i=0;i<n;i++)
    {
        P_2D[i]=(int*)malloc(sizeof(int)*n);//columns of i-th row
        if(!P_2D[i])
        {
            printf("Fail to allocate memory");
            exit(1);//unusual exit out the program
        }
    }
    
    //allocate dynamic array height[n][n]
    float **height_2D=NULL;
    height_2D = (float**)malloc(sizeof(float*)*n);//allocate n rows of space to store pointers
    if(!height_2D )
    {
        printf("Fail to allocate memory");
        exit(1);//unusual exit out the program
    }
    for(int i=0;i<n;i++)
    {
        height_2D[i]=(float*)malloc(sizeof(float)*n);//columns of i-th row
        if(!height_2D[i])
        {
            printf("Fail to allocate memory");
            exit(1);//unusual exit out the program
        }
    }
    
    getchar();
    //input the height of each point
    for(int j=0;j<n;j++)
    {
        for(int i=0;i<n;i++)
        {
          scanf(" %2f",*(height_2D+j)+i);
         /*i-th rows (the address of first rows) j-th columns,and not take \n
              as the end condition of scanf */
        }
    }
    getchar();
    dp(n,D_2D,height_2D,P_2D);//dynamic programming
    printf("\n");
    //use stack to reverse the order of output
    list *Top=NULL;  //intend to be safe
    Top=createnode();// create the node
    Top=record(P_2D,n-1,n-1,Top);//trace back from end point and return the position of the top of stack
    do
    {
        int j=-1;int i=-1;
        Top=pop(&j,&i ,Top);
        //Pop from the top of stack(changing the variable by calling address)
        if(j>=0 && i>=0)
        {
            printf("(%d,%d), ",i,j);
          
        }
    
    
    }while(Top!=NULL);//If it is not null(not at the bottom of the stack)keep doing pop
    printf("\n-----------------------------\n");
    //free allocated array
    for(int i=0;i<n;i++)
    {
        free(D_2D[i]);
        D_2D[i]=NULL;
    }
    free(D_2D);
    D_2D=NULL;
    for(int i=0;i<n;i++)
    {
        free(P_2D[i]);
        P_2D[i]=NULL;
    }
    free(P_2D);
    P_2D=NULL;
    for(int i=0;i<n;i++)
    {
        free(height_2D[i]);
        height_2D[i]=NULL;
    }
    free(height_2D);
    height_2D=NULL;
    return 0;
}







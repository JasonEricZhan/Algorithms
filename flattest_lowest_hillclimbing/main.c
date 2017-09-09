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
    float **cost_2D=NULL;
    cost_2D = (float**)malloc(sizeof(float*)*n);//allocate n rows of space to store pointers
    if(!cost_2D )
    {
        printf("Fail to allocate memory");
        exit(1);//unusual exit out the program
    }
    for(int i=0;i<n;i++)
    {
        cost_2D[i]=(float*)malloc(sizeof(float)*n);//columns of i-th row
        if(!cost_2D[i])
        {
            printf("Fail to allocate memory");
            exit(1);//unusual exit out the program
        }
    }
    
    //allocate dynamic array P[n][n]
    int **path_2D=NULL;
    path_2D = (int**)malloc(sizeof(int*)*n);//allocate n rows of space to store pointers
    if(!path_2D )
    {
        printf("Fail to allocate memory");
        exit(1);//unusual exit out the program
    }
    for(int i=0;i<n;i++)
    {
        path_2D[i]=(int*)malloc(sizeof(int)*n);//columns of i-th row
        if(!path_2D[i])
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
    dp(n,cost_2D,height_2D,path_2D);//dynamic programming
    printf("\n========\n");
    printf("lowest cost is %.2f(for checking)",*(*(cost_2D+n-1)+n-1));
    printf("\n========\n");
    printf("\n");
    //use stack to reverse the order of output
    list *Top=NULL;  //intend to be safe
    Top=create_node();// create the node
    Top=record(path_2D,n-1,n-1,Top);//trace back from end point and return the position of the top of stack
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
        free(cost_2D[i]);
        cost_2D[i]=NULL;
    }
    free(cost_2D);
    cost_2D=NULL;
    for(int i=0;i<n;i++)
    {
        free(path_2D[i]);
        path_2D[i]=NULL;
    }
    free(path_2D);
    path_2D=NULL;
    for(int i=0;i<n;i++)
    {
        free(height_2D[i]);
        height_2D[i]=NULL;
    }
    free(height_2D);
    height_2D=NULL;
    return 0;
}







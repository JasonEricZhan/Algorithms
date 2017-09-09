#include<stdio.h>
#include<stdlib.h>
#include "P.h"




list * create_node()//Create the first node point to the null
{
  list * newnode = malloc(sizeof(list));
  if(!newnode) // if the new pointer is null then it is fail to allocate memory
  {
    printf("Fail to allocate memory");
    exit(1);//unusual exit out the program
  }
  newnode->row =-1;
  newnode->col =-1;
  newnode->next = NULL;
  return newnode;
}




list* push(int col,int row,list*first)//push the data into the stack
{
  list *newnode;
  newnode = malloc(sizeof(list));
  //Put the new data
  newnode->col = col;
  newnode->row = row;
  if(!newnode) // if the new pointer is null then it is fail to allocate memory
  {
    printf("Fail to allocate memory");
    exit(1);//unusual exit out the program
  }
  else
  {
    newnode->next=first;//The new node point to the old head of link list
  }
  return newnode;//return the new node pointer
  
}


list* pop(int *col,int *row,list *first)//Pop out the record data
{
  list*t;
  //make temporary pointer point to the first node
  t=first;
  //Copy the data to input pointer's content
  *col=first->col;
  *row=first->row;
  //The pointer go to next position
  first = first->next;
  free(t);//Free the allocated memory space which t points to
  t=NULL;
  return first;//return the next node pointer
}



list* record(char **path,int col,int row,list* first)
{
    if(j==0 && row==0)
    {
        first=push(col,row,first);
        return first;
    }
    else if(*(*(path+col)+row)=='H')//horizon
    {
         
         first=push(col,row,first);
         return record(path,col-1,row,first);
    }
    else if(*(*(path+col)+row)=='D')//diag
    {
         
         first=push(col,row,first);
         return record(path,col-1,row-1,first);
    }
    else if(*(*(path+col)+row)=='V')//vertical
    {
         
         first=push(col,row,first);
         return record(path,col,row-1,first);
    }
    else
    {
        printf("there is missing value\n");  // for detecting
    }
    return first;
}

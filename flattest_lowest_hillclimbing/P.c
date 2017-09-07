#include<stdio.h>
#include<stdlib.h>
#include "P.h"




list * createnode()//Create the first node point to the null
{
  list * newnode = malloc(sizeof(list));
  if(!newnode) // if the new pointer is null then it is fail to allocate memory
  {
    printf("Fail to allocate memory");
    exit(1);//unusual exit out the program
  }
  newnode->i =-1;
  newnode->j =-1;
  newnode->next = NULL;
  return newnode;
}




list* push(int j,int i,list*first)//push the data into the stack
{
  list *newnode;
  newnode = malloc(sizeof(list));
  //Put the new data
  newnode->j = j;
  newnode->i = i;
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


list* pop(int *j,int *i,list *first)//Pop out the record data
{
  list*t;
  //make temporary pointer point to the first node
  t=first;
  //Copy the data to input pointer's content
  *j=first->j;
  *i=first->i;
  //The pointer go to next position
  first = first->next;
  free(t);//Free the allocated memory space which t points to
  t=NULL;
  return first;//return the next node pointer
}



list* record(int **P,int j,int i,list* first)
{
    if(j==0 && i==0)
    {
        first=push(j,i,first);
        return first;
    }
    else if(*(*(P+j)+i)==1)//horizon
    {
         
         first=push(j,i,first);
         return record(P,j,i-1,first);
    }
    else if(*(*(P+j)+i)==2)//diag
    {
         
         first=push(j,i,first);
         return record(P,j-1,i-1,first);
    }
    else if(*(*(P+j)+i)==3)//vertical
    {
         
         first=push(j,i,first);
         return record(P,j-1,i,first);
    }
    else
    {
        printf("there is missing value\n");  // for detecting
    }
    return first;
}

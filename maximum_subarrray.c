//
//  main.c
//  max_subarray_sum
//
//  Created by Eric on 2017/3/15.
//  Copyright © 2017年 Eric. All rights reserved.
//

#include <stdio.h>
#include <limits.h>
#include<stdlib.h>

int findcrossing(int *arr, int l, int m, int r);
int max(int a, int b);
int finddivede(int *arr, int l, int r);

typedef struct node
{//Use single link list to build the stack to record the data of every maximum subarray
    int start;  //left endpoind
    int end;    //right endpoind
    int sum;//The sum of subarray
    struct node*next;
}list;

list *Top;//Pointer points to the top of stack
list *createnode(int data);
list *push(int start,int end,int value,list*first);
list *pop(int *start,int *end ,int *value,list *first);


int main(void)
{
    //Create the first node at the bottom of stack which points to the null and the sum is infinite small
    Top=createnode(INT_MIN);
    if(!Top)
    {
    	printf("Fail to allocate memory");
        exit(1);//unusual exit out the program
    }
    int n;
    do
    {
        scanf("%3i",&n);
        getchar();//Prevent wrong input make the inifinite loop
    }
    while(n<1||n>999);//no more than 3 bit length
    int *array;
    array = malloc(sizeof(int)*(n+1));//dynamica allocate
    for(int i=1;i<n+1;i++)     //array[1..n]
    {
        scanf("%3i",array+i);
    }
    int max_sum =finddivede(array, 1, n);
    printf("\n-----------------------------\n");
    printf("sum is %3i (for checking )",max_sum);
    printf("\n-----------------------------\n");
    int start, end ,value,prev=0;
    //Declare the variables of recording the position and value of each stack
    do
    {
        Top=pop(&start,&end ,&value,Top);
        //Pop from the top of stack(changing the variable by calling address)
        if((value==max_sum)&&(prev!=start))
        {
            printf("From %3i to %3i(the first element is at 1)\n",start,end);
            printf("The maximum sum subarray is\n");
            for(int i=start; i<=end;i++)
            {
                printf("%3i ",*(array+i));
                prev=start;/*Record the previous start point,prevent print the same result twice in the
                    case of input are all negative numbers */
            }
            printf("\n-----------------------------\n");
        }
        
        
    }while(Top!=NULL);//If it is not null(not at the bottom of the stack)keep doing pop
    free(array);
    return 0;
    
}


list * createnode(int data)//Create the first node point to the null
{
    list * newNode = malloc(sizeof(list));
    newNode->sum =data;
    newNode->next = NULL;
    return newNode;
}


list* push(int start,int end,int value,list*first)//push the data into the stack
{
    list *newnode;
    newnode = malloc(sizeof(list));
    //Put the new data
    newnode->start = start;
    newnode->end = end;
    newnode->sum= value;
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


list* pop(int *start,int *end ,int *value,list *first)//Pop out the record data
{
    list*t;
    //make temporary pointer point to the first node
    t=first;
    //Copy the data to input pointer's content
    *start=first->start;
    *end=first->end;
    *value=first->sum;
    //The pointer go to next position
    first = first->next;
    free(t);//Free the allocated memory space which t points to
    return first;//return the next node pointer
}

int max(int a, int b)
{
    //which one is bigger ,and return the bigger one
    return( (a > b)? a : b);
    
}

//The step of dividing the array to two subarray
int finddivede(int *arr, int l, int r)
{
    // boundary condition: only one element
    if (l == r)
    {
        Top=push(l,r,*(arr+l),Top);
        return *(arr+l);
    }
    // middle point index
    int m = (l + r)/2;
    
    /* return maximum sum :
     a) maximum subarray sum in left half and maximum subarray sum in right half
     b) maximum subarray sum such that the subarray crosses the mid(like merge the two part) */
    
    
    return  max(   max(  finddivede(arr, l, m),finddivede(arr, m+1, r)   ),   findcrossing(arr, l, m, r)  );
    
}



//The crossing merge step:
int findcrossing(int *arr, int l, int m, int r)
{
    /*To  mantain that only one negetive number can be choose:
    At the merge step,The starting point are m and m+1.
    If they are both negative then return the maxium one of them,else keep going*/
    if(*(arr+m)<0&&*(arr+m+1)<0)
    {
            if(*(arr+m)==max(*(arr+m),*(arr+m+1))) //Choose the bigger one,and record the data of it
            {
                Top=push(m,m,*(arr+m),Top);
            }
            else
            {
                Top=push(m+1,m+1,*(arr+m+1),Top);
            }
            return max(*(arr+m),*(arr+m+1));
    }
    else
    {
            int start=0,end=0;//Declare the variable record the endpoint of subarray
//Left size:expand to left
            int record = 0;  //use variable to record the max sum value
            /*initialize:set the two values to infinite small,making it comparable
               1.when it is infinite small means the loop is at the beginning
               2.when it is not infinite small means the variables  left_max and right_max is the old record
               */
            int left_max = INT_MIN;
            int right_max = INT_MIN;
            int neg_count=0;//Use a negative number's counter to count the negative number when expand the subarray
            if(*(arr+m)<0||*(arr+m+1)<0)
            {// If one of mid point number is negative then add one to counter
                  neg_count++;
            }
            for (int i = m; i >= l; i--)
            {
                record = record + *(arr+i);
                if (record>=left_max)
                    //Zero or positive integar is in the new endpoint
                {
                     left_max = record;
                     start=i;
                }
                else
                {
                    //Means encounter a negative number and add one to negative number's counter
                    neg_count++;
                    if(neg_count>1&&(*(arr+i)<0&&*(arr+i+1)<0))
                    {//Check if encounter the second one of continuous negative number
                         start=i+2;
                        //If true then the start of maximum subarray go back two indexes
                        neg_count=neg_count-2;
                        //will not get this element so minus two on negative number counter
                        break;
                    }
                    else if(neg_count>1&&*(arr+i)<0)//Other case of encounter second negative integar
                    {
                        start=i+1;//go back one step
                        neg_count=neg_count-1;
                        //will not get this element so minus one on negative number counter
                        break;
                    }
                 }
             }
//Right size:expand to right
            record=0;    //initialize record again
            for (int i = m+1; i <= r; i++)
            {
                record = record + *(arr+i);
                if (record>=right_max)
                    //zero or positive integar is in the new position
                {
                        right_max = record;
                        end=i;
                }
                else
                {
                    //Means encounter a negative number and add one to negative number's counter
                    neg_count++;
                    if(neg_count>1&&(*(arr+i)<0&&*(arr+i-1)<0))
                    {//Check if encounter the second one of continuous negative number
                         end=i-2;
                        //If true then the start of maximum subarray go back two indexes
                        neg_count=neg_count-2;
                        //will not get this element so minus two on negative number counter
                        break;
                    }
                    else if(neg_count>1&&*(arr+i)<0)//Other case of encounter second negative integar
                    {
                        end=i-1;//go back one step
                        neg_count=neg_count-1;
                        //will not get this element so minus one on negative number counter
                        break;
                    }
                 }
             }
        Top=push(start,end,left_max + right_max,Top);
        return left_max + right_max;//The final sum result of crossing midpoint maximum subarray
      }
    return INT_MIN;//error message
    
}

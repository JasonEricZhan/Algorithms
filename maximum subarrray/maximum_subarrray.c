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

struct data
{
    int right;
    int left;
    int sum;
};

struct data maxmerge(int arr[], int left, int mid, int right);
struct data max(struct data a, struct data b);
struct data maxdivede(int arr[], int left, int right);


int main(void)
{
    int n=0;
    do
    {
        printf("Enter the number of elements:(no more than 6 bit length)\n");
        scanf("%6i",&n);
        getchar();//Prevent wrong input make the inifinite loop
        
    }while(n<1||n>999999);
    int array[n];
    int c=n;//Show how many integars need to be tapped in
    printf("Enter %6i integars no more than 6 bit length : \n",c);
    for(int i=1;i<n+1;i++)     
    {
        scanf("%12i",&array[i]);
        c--;
        while(!(array[i]>-99999&&array[i]<999999))
        {
            c++;
            printf("\nEnter %6i integars no more than 6 bit length : \n",c);
            scanf("%12i",&array[i]);
            c--;
        }
        
    }
    
    struct data max_sum =maxdivede(array, 1, n);
    printf("from%6d",max_sum.left);
    printf("to%6d\n",max_sum.right);
    printf("sum is %6d\n",max_sum.sum);
    for(int i=max_sum.left;i<=max_sum.right;i++)
    {
        printf("%6d",array[i]);
    }
  
    return 0;
    
}
    
struct data max(struct data a, struct data b)
{
    
    return( (a.sum > b.sum)? a : b);
       
}


struct data divede(int *arr, int left, int right)
{
    
    if (left == right)
    {
        
        struct data element;
        element.left=left;
        element.right=right;
        element.sum=arr[left];
        return element;
    }
    int mid = (left + right)/2;
    
    /* return maximum sum :
     a) maximum subarray sum in left half and maximum subarray sum in right half
     b) maximum subarray sum such that the subarray crosses the mid(like merge the two part) */
    return  max(   max(  divede(arr, left, mid),divede(arr, mid+1, right)   ),   merge(arr, left, mid, right)  );
    
}


    
struct data merge(int *arr, int left, int mid, int right)
{
    struct data element;
    /*To  mantain that only one negetive number can be choose:
    At the merge step,The starting point are m and m+1.
    If they are both negative then return the maxium one of them,else keep going*/
    if(arr[mid]<0&&arr[mid+1]<0)
    {
            if(arr[mid]>arr[mid+1]) 
            {
                
                element.left=left;
                element.right=right;
                element.sum=arr[mid];
            }
            else
            {
 
                element.left=left;
                element.right=right;
                element.sum=arr[mid+1];
            }
            return element;
    }
    else
    {
            int start=0,end=0;
            int record = 0;  
            
            int left_max = INT_MIN;
            int right_max = INT_MIN;
            int neg_number_count=0;
            if(arr[mid]<0||arr[mid+1]<0)
            {
                  neg_number_count++;
            }
            /*Two case:
               a)if the first reaching element of maximum subarray then left_max get the element
               b)if the sum of adding the next value is smaller then the original sum then restore it
               */
            for (int i = mid; i >= left; i--)
            {
                record = record + arr[i];
                if (record>=left_max)
                {
                     left_max = record;
                     start=i;
                }
                else
                {
                     neg_number_count++;
                    if(neg_count>1&&(arr[i]<0&&arr[i+1]<0))
                    {
                         start=i+2;
                        
                        neg_number_count=neg_number_count-2;
                        
                        break;
                    }
                    else if(neg_number_count>1&&arr[i]<0)
                    {
                        start=i+1;
                        neg_number_count=neg_number_count-1;
                        break;
                    }
                 }
            }
            record=0;   
            /*Two case:
             a)if the first value of maximum subarray then right_max get the first value
             b)if the sum of adding the next value is smaller then the original sum then restore it
             */
            for (int i = mid+1; i <= right; i++)
            {
                record = record + arr[i];
                if (record>=right_max)
                {
                        right_max = record;
                        end=i;
                }
                else
                {
                    neg_number_count++;
              
                    if(neg_number_count>1&&(arr[i]<0&&arr[i-1]<0))
                    {
                         end=i-2;
                        
                        neg_number_count=neg_number_count-2;
                        break;
                    }
                    else if(neg_number_count>1&&arr[i]<0)
                    {
                        end=i-1;
                        neg_number_count=neg_number_count-1;
                        break;
                    }
                 }
             }
        element.left=start;
        element.right=end;
        element.sum=left_max + right_max;
        ;
      }
    return element;//error message
    
}





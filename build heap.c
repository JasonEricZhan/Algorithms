,,,,,,,,,,,,,,,,,,,,,(iteration)
#include <stdio.h>

void adjust(int*a ,int r ,int n)
{
   int k=a[r];
   int j;
    for(j=r*2;j<=n;j=j*2)
    {
        if (a[j]<a[j+1]&& j<n ) j++;   ///junp out of range n may make a mistake
        if(k>a[j])
            break;
        else
        a[j/2]=a[j];
    }
    a[j/2]=k;
}

int b[11]={0,4,7,1,5,15,12,9,6,3,8};

int i;
int x=10;
int main(void)
{
    // insert code here..
    for(i=x/2;i>=1;i--)
         adjust(b,i,x) ;
    for(i=1;i<=10;i++)
        printf("%3d",b[i])  ;
    return 0;
}

,,,,,,,,,,,,,,,,,,,,
,,,,,,,,,,,,,,,,,,,,(recursion)

#include<stdio.h>


int n=10;
int b[10]={4,7,1,5,15,12,9,6,3,8};
int main()
{
    
    
    for(i=n/2;i>=0;i--)
    {
        adjust(b,i);
    }
    for(i=0;i<n;i++)
    {
        printf("%3d\t",b[i]);     ///  \t  is tab
    }
    return 0;
}


void adjust(int *a, int i)
{
    int l,r,biggest,temp;
    l=2*i+1;                      ///coordinate
    r=2*i+2;
    if(l<n && a[l]>a[i])
    {
        biggest=l;
    }
    else
    {
        biggest=i;
    }
    if(r<n && a[r]>a[biggest])
    {
        biggest=r;
    }
    if(biggest!=i)
    {
        temp=a[i];
        a[i]=a[biggest];
        a[biggest]=temp;          /// after change, a[biggest] become root
        adjust(a,biggest);         
    }
}
,,,,,,,,,,,,,,,,,,,,,

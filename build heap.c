#include <stdio.h>

void adjust(int*a ,int r ,int n)
{
   int k=a[r];
   int j;
    for(j=r*2;j<=n;j=j*2)
    {
        if (a[j]<a[j+1]&& j<10 ) j++;
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

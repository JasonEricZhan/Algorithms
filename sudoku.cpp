#include <iostream>

template <class T1>
void BackTrck( T1 s[],T1 index);
template <class T2>
bool promising(const T2 s[],T2 checked_index);
template <class T3>
void output_result(const T3 s[],T3 &the_ith_solution);


int the_ith_solution=1; //the variable record the solution is ith
int main(void) {
    
    using namespace std;
    char S_char[81];
    int S_number[81];
    for(int i=0;i<81;i++)
    {
        cin>>S_char[i];
    }
    
    for(int i=0;i<81;i++)
    {
        S_number[i]=static_cast<int>(S_char[i]-'0');  //transform to integar
    }
    cout<<"====="<<endl;
    BackTrck(S_number,0);
    return 0;
}

template <class T1>
void  BackTrck( T1 s[],T1 index)
{
    index=static_cast<int>(index);//for security
    if(s[index]==0)//the point is empty
    {
        for(int j=1;j<10;j++)//try to fit the number
        {
            s[index]=j;
            if(promising(s,index))//check it's valid or not
            {
                if(index==80)
                {
                    output_result(s,the_ith_solution);
                    return;
                }
                BackTrck(s,index+1);
                
            }
            if(j==9)//no solution
            {
                /*initialize to 0,exit this run and go back to the point
                 of starting this decision*/
                s[index]=0;
                return;
            }
        }
    }
    else if(s[index]!=0)//the point is not empty
    {
        if(index==80)
        {
            output_result(s,the_ith_solution);
            return;
        }
        BackTrck(s,index+1);//skip,and go to the next one
        
    }
    
}

template <class T2>
bool promising(const T2 s[],T2 checked_index)
{
    bool tag=true;
    int checked_row=checked_index/9,checked_col=checked_index%9;
    for(int k=0;k<81;k++)
    {
        int row=k/9,col=k%9;
        if(k!= checked_index && s[k]!=0 )//reach to itself or the point is empty
        {
            
            if((checked_row==row||checked_col==col)
               && s[checked_index]==s[k])
                // same column or same row ,and the number to fit in is same
            {
                tag=false;
            }
            else if(((checked_row/3)*3+checked_col/3)
                    == ((row/3)*3+col/3 )
                    && s[checked_index]==s[k]) //same area,and the number to fit in is same
            {
                tag=false;
            }
        }
    }
    return tag;//go through the over all loop check
}

template <class T3>
void output_result(const T3 s[],T3 &the_ith_solution)
{
    std::cout<<the_ith_solution<<"th solution is"<<std::endl;
    for(int k=0;k<81;k++)
    {
        if((k+1)%9==0 && k!=0)
        {
            std::cout<<s[k]<<" "<<std::endl;
        }
        else
        {
             std::cout<<s[k]<<" ";
        }
    }
    std::cout<<"====="<<std::endl;
    the_ith_solution+=1; //change the variable of record ,add one
}


#include<iostream>
#include<string.h>
#include<cstdlib>
using namespace std;
int timename[3]{0};
int life[6]{0};
int rankred[6]{0,3,4,5,2,1},rankblue[6]{0,4,1,2,3,5};
string boy[6]={" ","dragon","ninja","iceman","lion","wolf"};
int numred=0,numblue=0;
int flagred=1,flagblue=1;
int lifered=0,lifeblue=0;
int countred[6]{0},countblue[6]{0};
int count=0;
int countofred=1,countofblue=1;
void Red(int& lifes,int& num,int& flag)
{
    if(flag==0) return ;
    cout<<timename[0]<<timename[1]<<timename[2]<<" ";
    flag=0;
    for(int i=1;i<6;i++)
    if(lifes>=life[i])
    {
        flag=1;
        break;
    }
    if(flag==0)
    {
        cout<<"red headquarter stops making warriors"<<endl;
        return ;
    }
    for(int i=num;;i++)
    {
        if(lifes>=life[rankred[i%5+1]])
        {
            num=i;
            countred[rankred[i%5+1]]++;
            cout<<"red "<<boy[rankred[i%5+1]]<<" "<<countofred<<" born with strength "<<life[rankred[i%5+1]]\
            <<','<<countred[rankred[i%5+1]]<<" "<<boy[rankred[i%5+1]]<<" in red headquarter"<<endl;
            lifes-=life[rankred[i%5+1]];
            num++;
            countofred++;
            break;
        }
    }
}
void Blue(int& lifes,int& num,int& flag)
{
    if(flag==0) return ;
    cout<<timename[0]<<timename[1]<<timename[2]<<" ";
    flag=0;
    for(int i=1;i<6;i++)
    if(lifes>=life[i])
    {
        flag=1;
        break;
    }
    if(flag==0)
    {
        cout<<"blue headquarter stops making warriors"<<endl;
        return ;
    }
    for(int i=num;;i++)
    {
        if(lifes>=life[rankblue[i%5+1]])
        {
            num=i;
            countblue[rankblue[i%5+1]]++;
            cout<<"blue "<<boy[rankblue[i%5+1]]<<" "<<countofblue<<" born with strength "<<life[rankblue[i%5+1]]\
            <<','<<countblue[rankblue[i%5+1]]<<" "<<boy[rankblue[i%5+1]]<<" in blue headquarter"<<endl;
            lifes-=life[rankblue[i%5+1]];
            num++;
            countofblue++;
            break;
        }
    }
}
int main()
{
    int n,M;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>M;
        lifered=lifeblue=M;
        for(int j=1;j<=5;j++)
        cin>>life[j];
        cout<<"Case:"<<i<<endl;
        memset(timename,0,sizeof(timename));
        numred=numblue=0;
        flagred=flagblue=1;
        count=0;
        memset(countred,0,sizeof(countred));
        memset(countblue,0,sizeof(countblue));
        countofred=countofblue=1;
        while(flagred+flagblue)
        {
            timename[0]=count/100;
            timename[1]=(count%100)/10;
            timename[2]=count%10;
            count++;
            Red(lifered,numred,flagred);
            Blue(lifeblue,numblue,flagblue);
        }
    }
    system("pause");
    return 0;
}
#include<iostream>
#include<cstring>

using namespace std;

int M,N,T,K,smalllife=200,realt=0;
int locred=0,locblue=0;
string worriersarr[5]={"dragon","ninja","iceman","lion","wolf"};
int lifearr[5]{0};
int strengtharr[5]{0};
string weapons[3]={"sword","bomb","arrow"};
int Rquene[5]={2,3,4,1,0},Bquene[5]={3,0,1,2,4};
int hours,minutes;
bool gameover=false;
class worriers
{
    public:
        char color;
        int who=0;//名字索引
        int wrank=0;//第几位
        int place=0;
        int life=0;
        int strength=0;
        int weapon0=0,weapon1=0,weapon2[10]{0};
        int cntofweapon=0;
        int loyalty=10;
        string name;
        worriers(){};
        worriers(char id,int leftlife,int rank,int knowwho):color(id),wrank(rank),who(knowwho)
        {
            if(color=='r')
            {
                place=0;
            }
            else place=N+1;
            life=lifearr[who];
            strength=strengtharr[who];
            if(who!=4)
            {
                if(wrank%3==0) 
                    weapon0=1;
                else if(wrank%3==1)
                    weapon1=1;
                else
                    weapon2[0]=2;
                cntofweapon=1;
                name=worriersarr[who];
                if(name=="ninja") 
                {
                    if((wrank+1)%3==0) 
                        weapon0=1;
                    else if((wrank+1)%3==1)
                        weapon1=1;
                    else
                        weapon2[0]=2;
                        cntofweapon=2;
                }
            }
            else name="wolf";
            if(name=="lion") loyalty=leftlife;
        }
        void move()
        {
            if(color=='r'&&place<N+1)
            {
                ++place;
                cout<<hours/100<<hours%100/10<<hours%10<<":"<<minutes/10<<minutes%10<<" ";
                if(name=="iceman") life-=life/10;
                if(name=="lion") loyalty-=K;
                if(place!=N+1)
                cout<<"red "<<worriersarr[who]<<" "<<wrank<<" marched to city "<<place<<" with "<<life<<" elements and force "<<strength<<endl;
                else cout<<"red "<<worriersarr[who]<<" "<<wrank<<" reached blue headquarter with "<<life<<" elements and force "<<strength<<endl;
                //000:10 red iceman 1 marched to city 1 with 20 elements and force 30
                //004:10 red iceman 1 reached blue headquarter with 19 elements and force 23
                if(place==N+1) 
                {
                    gameover=true;
                    cout<<hours/100<<hours%100/10<<hours%10<<":"<<minutes/10<<minutes%10<<" ";
                    cout<<"blue headquarter was taken"<<endl;
                    //003:10 blue headquarter was taken
                }
            }
            else if(color=='b'&&place>0)
            {
                --place;
                cout<<hours/100<<hours%100/10<<hours%10<<":"<<minutes/10<<minutes%10<<" ";
                if(name=="iceman") life-=life/10;
                if(name=="lion") loyalty-=K;
                if(place!=0)
                cout<<"blue "<<worriersarr[who]<<" "<<wrank<<" marched to city "<<place<<" with "<<life<<" elements and force "<<strength<<endl;
                else cout<<"blue "<<worriersarr[who]<<" "<<wrank<<" reached red headquarter with "<<life<<" elements and force "<<strength<<endl;
                if(place==0) 
                {
                    gameover=true;
                    cout<<hours/100<<hours%100/10<<hours%10<<":"<<minutes/10<<minutes%10<<" ";
                    cout<<"red headquarter was taken"<<endl;
                }
            }
        }
};
class Home
{
    public:
        int rank=1;
        int sumlife=0;
        Home(int M)
        {
            sumlife=M;
        }
        bool over=false;
        ~Home(){}
        void produce(string id,worriers * p)
        {
            int temploc=0;
            if(id=="red")
            {
                temploc=Rquene[locred%5];
            }
            else temploc=Bquene[locblue%5];
            if(sumlife<lifearr[temploc]) 
            {
                over=true;
            }
            if(over) return ;
            else 
            {
                if(id=="red") locred++;
                else locblue++;
            }
            sumlife-=lifearr[temploc];
            switch(temploc)
            {
                case 0:
                    if(id=="red") 
                        p[rank]=worriers('r',sumlife,rank,0);
                    else
                        p[rank]=worriers('b',sumlife,rank,0);
                    break;
                case 1:
                    if(id=="red")
                        p[rank]=worriers('r',sumlife,rank,1);
                    else
                        p[rank]=worriers('b',sumlife,rank,1);
                    break;
                case 2:
                    if(id=="red")
                        p[rank]=worriers('r',sumlife,rank,2);
                    else
                        p[rank]=worriers('b',sumlife,rank,2);
                    break;
                case 3:
                    if(id=="red")
                        p[rank]=worriers('r',sumlife,rank,3);
                    else
                        p[rank]=worriers('b',sumlife,rank,3);
                    break;
                case 4:
                    if(id=="red")
                        p[rank]=worriers('r',sumlife,rank,4);
                    else
                        p[rank]=worriers('b',sumlife,rank,4);
            }
            cout<<hours/100<<hours%100/10<<hours%10<<":"<<minutes/10<<minutes%10<<" ";
            cout<<id<<" "<<worriersarr[temploc]<<" "<<rank<<" born"<<endl;
            if(temploc==3) 
                cout<<"Its loyalty is "<<sumlife<<endl;
            rank++;
        }
};

//! 1->weapon0 not used  2->weapon1 not used  0-> weapon1 used
//! 3->once 4->twice  0->weapon2 useless
void paixu(worriers & a,int aweapon[10])
{
    for(int i=0;i<a.weapon0;i++)
    aweapon[i]=1;
    for(int i=a.weapon0;i<a.weapon0+a.weapon1;i++)
    aweapon[i]=2;
    int row1=0,row2=0;
    for(int i=0;i<10;i++)
    {
        if(a.weapon2[i]==1) row1++;
        else if(a.weapon2[i]==2) row2++;
    }
    for(int i=a.weapon0+a.weapon1;i<a.cntofweapon;i++)
    {
        if(i-a.weapon0-a.weapon1<row1)
        aweapon[i]=3;
        else aweapon[i]=4;
    }
}
//! 1->weapon0 not used  2->weapon1 not used  0-> weapon1 used
//! 3->once 4->twice  0->weapon2 useless
bool realbeat(int s[10])
{
    for(int i=0;i<10;i++)
    if(s[i]) return true;
    return false;
}
void beat(worriers & a,worriers & b)
{
    if(b.name=="ninja"&&b.place==5)
    {
        b.name="ninja";
        b.place=5;
    }
    int aweapon[10]{0},bweapon[10]{0};
    paixu(a,aweapon);
    paixu(b,bweapon);
    int sta=-1,stb=-1;
    if(a.place%2==1)
    {
        while(true)
        {
            int flag=0;
            if(realbeat(aweapon))
            {
                int step=1;
                for(step=1;step<=10;step++)
                {
                    if(aweapon[(sta+step)%10]==1)
                    {
                        b.life-=a.strength*2/10;
                        if(a.strength*2/10>0) flag=1;
                        sta=(sta+step)%10;
                        break;
                    }
                    if(aweapon[(sta+step)%10]==2)
                    {
                        b.life-=a.strength*4/10;
                        if(a.name!="ninja") a.life-=(a.strength*4/10)/2;
                        aweapon[(sta+step)%10]=0;
                        flag=1;
                        sta=(sta+step)%10;
                        break;
                    }
                    if(aweapon[(sta+step)%10]>2)
                    {
                        flag=1;
                        b.life-=a.strength*3/10;
                        if(aweapon[(sta+step)%10]==3) aweapon[(sta+step)%10]=0;
                        else aweapon[(sta+step)%10]=3;
                        sta=(sta+step)%10;
                        break;
                    }
                }
            }
            if(a.life>0&&b.life>0&&realbeat(bweapon))
            {
                int step=1;
                for(step=1;step<=10;step++)
                {
                    if(bweapon[(stb+step)%10]==1)
                    {
                        a.life-=b.strength*2/10;
                        if(b.strength*2/10>0) flag=1;
                        stb=(stb+step)%10;
                        break;
                    }
                    if(bweapon[(stb+step)%10]==2)
                    {
                        a.life-=b.strength*4/10;
                        if(b.name!="ninja") b.life-=(b.strength*4/10)/2;
                        bweapon[(stb+step)%10]=0;
                        flag=1;
                        stb=(stb+step)%10;
                        break;
                    }
                    if(bweapon[(stb+step)%10]>2)
                    {
                        a.life-=b.strength*3/10;
                        if(bweapon[(stb+step)%10]==3) bweapon[(stb+step)%10]=0;
                        else bweapon[(stb+step)%10]=3;
                        flag=1;
                        stb=(stb+step)%10;
                        break;
                    }
                }
            }
            for(int i=0;i<10;i++)
            if(aweapon[i]>1||bweapon[i]>1)
            {
                flag=1;
                break;
            }
            if(flag==0) break;
            if(a.life<=0||b.life<=0) break;
        }
    }
    else
    {
        while(true)
        {
            int flag=0;
            if(realbeat(bweapon))
            {
                int step=1;
                for(step=1;step<=10;step++)
                {
                    if(bweapon[(stb+step)%10]==1)
                    {
                        a.life-=b.strength*2/10;
                        if(b.strength*2/10>0) flag=1;
                        stb=(stb+step)%10;
                        break;
                    }
                    if(bweapon[(stb+step)%10]==2)
                    {
                        a.life-=b.strength*4/10;
                        if(b.name!="ninja") b.life-=(b.strength*4/10)/2;
                        bweapon[(stb+step)%10]=0;
                        flag=1;
                        stb=(stb+step)%10;
                        break;
                    }
                    if(bweapon[(stb+step)%10]>2)
                    {
                        a.life-=b.strength*3/10;
                        if(bweapon[(stb+step)%10]==3) bweapon[(stb+step)%10]=0;
                        else bweapon[(stb+step)%10]=3;
                        flag=1;
                        stb=(stb+step)%10;
                        break;
                    }
                }
            }
            if(a.life>0&&b.life>0&&realbeat(aweapon))
            {
                int step=1;
                for(step=1;step<=10;step++)
                {
                    if(aweapon[(sta+step)%10]==1)
                    {
                        b.life-=a.strength*2/10;
                        if(a.strength*2/10>0) flag=1;
                        sta=(sta+step)%10;
                        break;
                    }
                    if(aweapon[(sta+step)%10]==2)
                    {
                        b.life-=a.strength*4/10;
                        if(a.name!="ninja") a.life-=(a.strength*4/10)/2;
                        aweapon[(sta+step)%10]=0;
                        flag=1;
                        sta=(sta+step)%10;
                        break;
                    }
                    if(aweapon[(sta+step)%10]>2)
                    {
                        flag=1;
                        b.life-=a.strength*3/10;
                        if(aweapon[(sta+step)%10]==3) aweapon[(sta+step)%10]=0;
                        else aweapon[(sta+step)%10]=3;
                        sta=(sta+step)%10;
                        break;
                    }
                }
            }
            for(int i=0;i<10;i++)
            if(aweapon[i]>1||bweapon[i]>1)
            {
                flag=1;
                break;
            }
            if(flag==0) break;
            if(a.life<=0||b.life<=0) break;
        }
    }        
    cout<<hours/100<<hours%100/10<<hours%10<<":"<<minutes/10<<minutes%10<<" ";
    if(a.life>0&&b.life>0)
    {
        cout<<"both red "<<a.name<<" "<<a.wrank<<" and blue "<<b.name<<" "<<b.wrank<<" were alive in city "<<a.place<<endl;
        if(a.name=="dragon") 
        {
            cout<<hours/100<<hours%100/10<<hours%10<<":"<<minutes/10<<minutes%10<<" ";
            cout<<"red dragon "<<a.wrank<<" yelled in city "<<a.place<<endl;
            //003:40 blue dragon 2 yelled in city 4
        }
        if(b.name=="dragon") 
        {
            cout<<hours/100<<hours%100/10<<hours%10<<":"<<minutes/10<<minutes%10<<" ";
            cout<<"blue dragon "<<b.wrank<<" yelled in city "<<b.place<<endl;
            //003:40 blue dragon 2 yelled in city 4
        }
        //000:40 red iceman 1 killed blue lion 12 in city 2 remaining 20 elements
        //000:40 both red iceman 1 and blue lion 12 died in city 2
        //000:40 both red iceman 1 and blue lion 12 were alive in city 2
        //! "grab"
        int cnt0=0,cnt1=0,cnt21=0,cnt22=0;
        for(int i=0;i<10;i++)
        {
            if(aweapon[i]==1)  cnt0++;
            else if(aweapon[i]==2) cnt1++;
            else if(aweapon[i]==3) cnt21++;
            else if(aweapon[i]==4) cnt22++;
        }
        a.weapon0=cnt0;
        a.weapon1=cnt1;
        for(int i=0;i<10;i++)
        a.weapon2[i]=0;
        for(int i=0;i<cnt21;i++)
        {
            a.weapon2[i]=1;
        }
        for(int i=cnt21;i<cnt21+cnt22;i++)
        {
            a.weapon2[i]=2;
        }
        a.cntofweapon=cnt0+cnt1+cnt21+cnt22;
        cnt0=0;
        cnt1=0;
        cnt21=0;
        cnt22=0;
        for(int i=0;i<10;i++)
        {
            if(bweapon[i]==1)  cnt0++;
            else if(bweapon[i]==2) cnt1++;
            else if(bweapon[i]==3) cnt21++;
            else if(bweapon[i]==4) cnt22++;
        }
        b.weapon0=cnt0;
        b.weapon1=cnt1;
        for(int i=0;i<10;i++)
        b.weapon2[i]=0;
        for(int i=0;i<cnt21;i++)
        {
            b.weapon2[i]=1;
        }
        for(int i=cnt21;i<cnt21+cnt22;i++)
        {
            b.weapon2[i]=2;
        }
        b.cntofweapon=cnt0+cnt1+cnt21+cnt22;
    }
    else if(a.life<=0&&b.life<=0)
    {
        cout<<"both red "<<a.name<<" "<<a.wrank<<" and blue "<<b.name<<" "<<b.wrank<<" died in city "<<a.place<<endl;
        //! "grab"
    }
    else if(a.life>0)
    {
        cout<<"red "<<a.name<<" "<<a.wrank<<" killed blue "<<b.name<<" "<<b.wrank<<" in city "<<a.place<<" remaining "<<a.life<<" elements"<<endl;
        if(a.name=="dragon") 
        {
            cout<<hours/100<<hours%100/10<<hours%10<<":"<<minutes/10<<minutes%10<<" ";
            cout<<"red dragon "<<a.wrank<<" yelled in city "<<a.place<<endl;
            //003:40 blue dragon 2 yelled in city 4
        }
        int cnt0=0,cnt1=0,cnt21=0,cnt22=0;
        for(int i=0;i<10;i++)
        {
            if(aweapon[i]==1)  cnt0++;
            else if(aweapon[i]==2) cnt1++;
            else if(aweapon[i]==3) cnt21++;
            else if(aweapon[i]==4) cnt22++;
        }
        int leftplace=10-cnt0-cnt1-cnt21-cnt22;
        while(leftplace>0)
        {
            int flags=0;
            for(int i=0;i<10;i++)
            if(bweapon[i]) flags=1;
            if(flags==0) break;
            for(int i=0;i<10;i++)
            {
                if(bweapon[i]==1)
                {
                    cnt0++;
                    leftplace--;
                    bweapon[i]=0;
                    break;
                }
                else if(bweapon[i]==2)
                {
                    cnt1++;
                    leftplace--;
                    bweapon[i]=0;
                    break;
                }
                else if(bweapon[i]==4)
                {
                    cnt22++;
                    leftplace--;
                    bweapon[i]=0;
                    break;
                }
                else if(bweapon[i]==3)
                {
                    cnt21++;
                    leftplace--;
                    bweapon[i]=0;
                    break;
                }
            }
        }
        a.weapon0=cnt0;
        a.weapon1=cnt1;
        for(int i=0;i<10;i++)
        a.weapon2[i]=0;
        for(int i=0;i<cnt21;i++)
        {
            a.weapon2[i]=1;
        }
        for(int i=cnt21;i<cnt21+cnt22;i++)
        {
            a.weapon2[i]=2;
        }
        a.cntofweapon=cnt0+cnt1+cnt21+cnt22;
    }
    else
    {
        cout<<"blue "<<b.name<<" "<<b.wrank<<" killed red "<<a.name<<" "<<a.wrank<<" in city "<<b.place<<" remaining "<<b.life<<" elements"<<endl;
        if(b.name=="dragon") 
        {
            cout<<hours/100<<hours%100/10<<hours%10<<":"<<minutes/10<<minutes%10<<" ";
            cout<<"blue dragon "<<b.wrank<<" yelled in city "<<b.place<<endl;
            //003:40 blue dragon 2 yelled in city 4
        }
        int cnt0=0,cnt1=0,cnt21=0,cnt22=0;
        for(int i=0;i<10;i++)
        {
            if(bweapon[i]==1)  cnt0++;
            else if(bweapon[i]==2) cnt1++;
            else if(bweapon[i]==3) cnt21++;
            else if(bweapon[i]==4) cnt22++;
        }
        int leftplace=10-cnt0-cnt1-cnt21-cnt22;
        while(leftplace>0)
        {
            int flags=0;
            for(int i=0;i<10;i++)
            if(aweapon[i]) flags=1;
            if(flags==0) break;
            for(int i=0;i<10;i++)
            {
                if(aweapon[i]==1)
                {
                    cnt0++;
                    leftplace--;
                    aweapon[i]=0;
                    break;
                }
                else if(aweapon[i]==2)
                {
                    cnt1++;
                    leftplace--;
                    aweapon[i]=0;
                    break;
                }
                else if(aweapon[i]==4)
                {
                    cnt22++;
                    leftplace--;
                    aweapon[i]=0;
                    break;
                }
                else if(aweapon[i]==3)
                {
                    int pflag=1;
                    for(int i=0;i<10;i++)
                    {
                        if(aweapon[i]==4) pflag=0;
                    }
                    if(pflag==0) continue;
                    cnt21++;
                    leftplace--;
                    aweapon[i]=0;
                    break;
                }
            }
        }
        b.weapon0=cnt0;
        b.weapon1=cnt1;
        for(int i=0;i<10;i++)
        b.weapon2[i]=0;
        for(int i=0;i<cnt21;i++)
        {
            b.weapon2[i]=1;
        }
        for(int i=cnt21;i<cnt21+cnt22;i++)
        {
            b.weapon2[i]=2;
        }
        b.cntofweapon=cnt0+cnt1+cnt21+cnt22;
    }
}
int main()
{
    int t;
    cin>>t;
    for(int i=1;i<=t;i++)
    {
        smalllife=200;
        realt=0;
        locred=0;
        locblue=0;
        gameover=false;
        worriers pred[101];
        worriers pblue[101];
        cin>>M>>N>>K>>T;
        Home Redhome(M),Bluehome(M);
        for(int i=0;i<5;i++)
        {
            cin>>lifearr[i];
            if(lifearr[i]<=smalllife)
            smalllife=lifearr[i];
        }
        for(int i=0;i<5;i++)
        cin>>strengtharr[i];
        cout<<"Case "<<i<<":"<<endl;
        while(realt<=T)
        {
            if(gameover) break;
            hours=realt/60;
            minutes=realt%60;
            if(minutes==0)
            {
                Redhome.produce("red",pred);
                Bluehome.produce("blue",pblue);
                realt+=5;
            }
            else if(minutes==5)
            {
                for(int j=0;j<=N+1;j++)
                {
                    for(int i=1;i<=Redhome.rank;i++)
                    if(pred[i].name=="lion"&&pred[i].loyalty<=0&&pred[i].place==j&&pred[i].life>0)
                    {
                        cout<<hours/100<<hours%100/10<<hours%10<<":"<<minutes/10<<minutes%10<<" ";
                        //blue lion 1 ran away
                        cout<<"red lion "<<pred[i].wrank<<" ran away"<<endl;
                        pred[i].life=-1;
                    }
                    for(int i=1;i<=Bluehome.rank;i++)
                    if(pblue[i].name=="lion"&&pblue[i].loyalty<=0&&pblue[i].place==j&&pblue[i].life>0)
                    {
                        cout<<hours/100<<hours%100/10<<hours%10<<":"<<minutes/10<<minutes%10<<" ";
                        //blue lion 1 ran away
                        cout<<"blue lion "<<pblue[i].wrank<<" ran away"<<endl;
                        pblue[i].life=-1;
                    }
                }
                realt+=5;
            }
            else if(minutes==10)
            {
                int tempredplace[101]{0};
                for(int i=1;i<=Redhome.rank;i++) tempredplace[i]=pred[i].place;
                int tempblueplace[101]{0};
                for(int i=1;i<=Bluehome.rank;i++) tempblueplace[i]=pblue[i].place;
                for(int j=0;j<=N+1;j++)
                {
                    for(int i=1;i<=Redhome.rank;i++)
                    {
                        if(pred[i].life>0&&tempredplace[i]+1==j) pred[i].move();
                    }
                    for(int i=1;i<=Bluehome.rank;i++)
                    {
                        if(pblue[i].life>0&&tempblueplace[i]-1==j) pblue[i].move();
                    }
                }
                realt+=25;
                if(gameover) break;
            }
            else if(minutes==35)
            {
                for(int j=0;j<=N+1;j++)
                {
                    for(int i=1;i<=Redhome.rank;i++)
                    {
                        if(pred[i].name=="wolf"&&pred[i].life>0&&pred[i].place==j)
                        {
                            for(int s=1;s<=Bluehome.rank;s++)
                            {
                                if(pblue[s].life>0&&pblue[s].place==j&&pblue[s].name!="wolf")
                                {
                                    int grabcnt=0,grabweapon=0;
                                    if(pblue[s].weapon0) 
                                    {
                                        grabweapon=0;
                                        while(pred[i].cntofweapon<10&&pblue[s].weapon0>0)
                                        {
                                            grabcnt++;
                                            pred[i].cntofweapon++;
                                            pred[i].weapon0++;
                                            pblue[s].weapon0--;
                                        }
                                    }
                                    else if(pblue[s].weapon1) 
                                    {
                                        grabweapon=1;
                                        while(pred[i].cntofweapon<10&&pblue[s].weapon1>0)
                                        {
                                            grabcnt++;
                                            pred[i].cntofweapon++;
                                            pred[i].weapon1++;
                                            pblue[s].weapon1--;
                                        }
                                    }
                                    else
                                    {
                                        for(int w=0;w<10;w++)
                                        {
                                            if(pblue[s].weapon2[w]) grabweapon=2;
                                        }
                                        int weapon2to2=0,weapon2to1=0;
                                        for(int i=0;i<10;i++)
                                        {
                                            if(pblue[s].weapon2[i]==2) weapon2to2++;
                                            else if(pblue[s].weapon2[i]) weapon2to1++;
                                        }
                                        int loseto2=0,loseto1=0;
                                        if(pred[i].cntofweapon+weapon2to2>=10)
                                        {
                                            loseto2=10-pred[i].cntofweapon;
                                            loseto1=0;
                                        }
                                        else if(pred[i].cntofweapon+weapon2to2+weapon2to1>=10)
                                        {
                                            loseto2=weapon2to2;
                                            loseto1=10-(pred[i].cntofweapon+weapon2to2);
                                        }
                                        else
                                        {
                                            loseto2=weapon2to2;
                                            loseto1=weapon2to1;
                                        }
                                        weapon2to2-=loseto2;
                                        weapon2to1-=loseto1;
                                        for(int i=0;i<10;i++)
                                        {
                                            if(i<weapon2to1) pblue[s].weapon2[i]=2;
                                            else if(i<weapon2to2+weapon2to1) pblue[s].weapon2[i]=1;
                                            else pblue[s].weapon2[i]=0;
                                        }
                                        for(int p=9;p>=0;p--)
                                        {
                                            if(9-p<loseto2) pred[i].weapon2[p]=2;
                                            else if(9-p<loseto2+loseto1) pred[i].weapon2[p]=1;
                                        }
                                        grabcnt=loseto1+loseto2;
                                        pred[i].cntofweapon+=grabcnt;
                                    }
                                    if(grabcnt==0) break;
                                    cout<<hours/100<<hours%100/10<<hours%10<<":"<<minutes/10<<minutes%10<<" ";
                                    pblue[s].cntofweapon-=grabcnt;
                                    cout<<"red wolf "<<pred[i].wrank<<" took "<<grabcnt<<" "<<weapons[grabweapon]<<" from blue "<<pblue[s].name<<" "<<pblue[s].wrank<<" in city "<<j<<endl;
                                }
                            }
                        }
                    }
                    for(int i=1;i<=Bluehome.rank;i++)
                    {
                        if(pblue[i].name=="wolf"&&pblue[i].life>0&&pblue[i].place==j)
                        {
                            for(int s=1;s<=Redhome.rank;s++)
                            {
                                if(pred[s].life>0&&pred[s].place==j&&pred[s].name!="wolf")
                                {
                                    int grabcnt=0,grabweapon=0;
                                    if(pred[s].weapon0) 
                                    {
                                        grabweapon=0;
                                        while(pblue[i].cntofweapon<10&&pred[s].weapon0>0)
                                        {
                                            grabcnt++;
                                            pblue[i].cntofweapon++;
                                            pblue[i].weapon0++;
                                            pred[s].weapon0--;
                                        }
                                    }
                                    else if(pred[s].weapon1) 
                                    {
                                        grabweapon=1;
                                        while(pblue[i].cntofweapon<10&&pred[s].weapon1>0)
                                        {
                                            grabcnt++;
                                            pblue[i].cntofweapon++;
                                            pblue[i].weapon1++;
                                            pred[s].weapon1--;
                                        }
                                    }
                                    else
                                    {
                                        for(int w=0;w<10;w++)
                                        {
                                            if(pred[s].weapon2[w]) grabweapon=2;
                                        }
                                        int weapon2to2=0,weapon2to1=0;
                                        for(int i=0;i<10;i++)
                                        {
                                            if(pred[s].weapon2[i]==2) weapon2to2++;
                                            else if(pred[s].weapon2[i]) weapon2to1++;
                                        }
                                        int loseto2=0,loseto1=0;
                                        if(pblue[i].cntofweapon+weapon2to2>=10)
                                        {
                                            loseto2=10-pblue[i].cntofweapon;
                                            loseto1=0;
                                        }
                                        else if(pblue[i].cntofweapon+weapon2to2+weapon2to1>=10)
                                        {
                                            loseto2=weapon2to2;
                                            loseto1=10-(pblue[i].cntofweapon+weapon2to2);
                                        }
                                        else
                                        {
                                            loseto2=weapon2to2;
                                            loseto1=weapon2to1;
                                        }
                                        weapon2to2-=loseto2;
                                        weapon2to1-=loseto1;
                                        for(int i=0;i<10;i++)
                                        {
                                            if(i<weapon2to1) pred[s].weapon2[i]=2;
                                            else if(i<weapon2to2+weapon2to1) pred[s].weapon2[i]=1;
                                            else pred[s].weapon2[i]=0;
                                        }
                                        for(int p=9;p>=0;p--)
                                        {
                                            if(9-p<loseto2) pblue[i].weapon2[p]=2;
                                            else if(9-p<loseto2+loseto1) pblue[i].weapon2[p]=1;
                                        }
                                        grabcnt=loseto1+loseto2;
                                        pblue[i].cntofweapon+=grabcnt;
                                    }
                                    if(grabcnt==0) break;
                                    pred[s].cntofweapon-=grabcnt;
                                    cout<<hours/100<<hours%100/10<<hours%10<<":"<<minutes/10<<minutes%10<<" ";
                                    cout<<"blue wolf "<<pblue[i].wrank<<" took "<<grabcnt<<" "<<weapons[grabweapon]<<" from red "<<pred[s].name<<" "<<pred[s].wrank<<" in city "<<j<<endl;
                                }
                            }
                        }
                    }
                }
                realt+=5;
            }
            else if(minutes==40)
            {
                for(int j=0;j<=N+1;j++)
                {
                    for(int i=1;i<=Redhome.rank;i++)
                    {
                        if(pred[i].place==j&&pred[i].life>0)
                        {
                            for(int s=1;s<=Bluehome.rank;s++)
                            {
                                if(pblue[s].place==j&&pblue[s].life>0)
                                {
                                    beat(pred[i],pblue[s]);
                                }
                            }
                        }
                    }
                }
                realt+=10;
            }
            else if(minutes==50)
            {
                //000:50 100 elements in red headquarter
                cout<<hours/100<<hours%100/10<<hours%10<<":"<<minutes/10<<minutes%10<<" ";
                cout<<Redhome.sumlife<<" elements in red headquarter"<<endl;
                cout<<hours/100<<hours%100/10<<hours%10<<":"<<minutes/10<<minutes%10<<" ";
                cout<<Bluehome.sumlife<<" elements in blue headquarter"<<endl;
                realt+=5;
            }
            else if(minutes==55)
            {
                for(int j=0;j<=N+1;j++)
                {
                    for(int i=1;i<=Redhome.rank;i++)
                    {
                        if(pred[i].place==j&&pred[i].life>0)
                        {
                            int cntof2=0;
                            for(int s=0;s<10;s++)
                            if(pred[i].weapon2[s]) cntof2++;
                            cout<<hours/100<<hours%100/10<<hours%10<<":"<<minutes/10<<minutes%10<<" ";
                            cout<<"red "<<pred[i].name<<" "<<pred[i].wrank<<" has "<<pred[i].weapon0<<" sword "<<pred[i].weapon1<<" bomb "<<cntof2<<" arrow and "<<pred[i].life<<" elements"<<endl;
                        }
                    }
                    for(int i=1;i<=Bluehome.rank;i++)
                    {
                        if(pblue[i].place==j&&pblue[i].life>0)
                        {
                            int cntof2=0;
                            for(int s=0;s<10;s++)
                            if(pblue[i].weapon2[s]) cntof2++;
                            cout<<hours/100<<hours%100/10<<hours%10<<":"<<minutes/10<<minutes%10<<" ";
                            cout<<"blue "<<pblue[i].name<<" "<<pblue[i].wrank<<" has "<<pblue[i].weapon0<<" sword "<<pblue[i].weapon1<<" bomb "<<cntof2<<" arrow and "<<pblue[i].life<<" elements"<<endl;
                        }
                    }
                }
                realt+=5;
                //000:55 blue wolf 2 has 2 sword 3 bomb 0 arrow and 7 elements
            }
        }
    }
    return 0;
}
#include <iostream>
#include <cstring>
#include <cmath>
#include <iomanip>
#include <fstream>
using namespace std;

int M, N, R, T, K, smalllife = 200, realt = 0;
int locred = 0, locblue = 0;
string worriersarr[5] = {"dragon", "ninja", "iceman", "lion", "wolf"};
int lifearr[5]{0};
int strengtharr[5]{0};
int citylife[21]{0};
int cityflag[21]; //-3表示红旗 -2表示红旗但是已经输了一场 -1表示空白但是胜了一场 0表示空白 1表示空白但是胜了一场 2表示蓝旗输了一场 3表示蓝旗
string weapons[3] = {"sword", "bomb", "arrow"};
int Rquene[5] = {2, 3, 4, 1, 0}, Bquene[5] = {3, 0, 1, 2, 4};
int hours, minutes;
int gameoverred = 0, gameoverblue = 0;
void bobaotime()
{
    cout << hours / 100 << hours % 100 / 10 << hours % 10 << ":" << minutes / 10 << minutes % 10 << " ";
}
class worriers
{
public:
    char color;
    int who = 0;   //名字索引
    int wrank = 0; //第几位
    int place = 0;
    int life = 0;
    int strength = 0;
    int worrierweapons[3]{0};
    int swordstrength = 0;
    int loyalty = 10;
    double brave = 0;
    bool shame = false;
    string name;
    worriers(){};
    worriers(char id, int leftlife, int rank, int knowwho) : color(id), wrank(rank), who(knowwho)
    {
        if (color == 'r')
        {
            place = 0;
        }
        else
            place = N + 1;
        life = lifearr[who];
        strength = strengtharr[who];
        name = worriersarr[who];
        if (who == 0)
        {
            worrierweapons[wrank % 3]++;
            brave = leftlife * 1.0 / life;
        }
        else if (who == 1)
        {
            worrierweapons[wrank % 3]++;
            worrierweapons[(wrank + 1) % 3]++;
        }
        else if (who == 2)
        {
            worrierweapons[wrank % 3]++;
        }
        else if (who == 3)
        {
            loyalty = leftlife;
        }
        if (worrierweapons[2])
            worrierweapons[2] = 3;
        if (worrierweapons[0])
            swordstrength = 0.2 * strength;
        bobaotime();
        if (id == 'r')
            cout << "red";
        else
            cout << "blue";
        cout << " " << worriersarr[knowwho] << " " << rank << " born" << endl;
        if (knowwho == 3)
            cout << "Its loyalty is " << leftlife << endl;
        if (knowwho == 0)
            cout << fixed << setprecision(2) << "Its morale is " << brave << endl;
    }
    void move()
    {
        if (color == 'r' && place < N + 1)
        {
            ++place;
            bobaotime();
            if (name == "iceman" && place % 2 == 0)
            {
                life -= 9;
                strength += 20;
                if (life <= 0)
                    life = 1;
            }
            if (place != N + 1)
                cout << "red " << worriersarr[who] << " " << wrank << " marched to city " << place << " with " << life << " elements and force " << strength << endl;
            else
                cout << "red " << worriersarr[who] << " " << wrank << " reached blue headquarter with " << life << " elements and force " << strength << endl;
            // 000:10 red iceman 1 marched to city 1 with 20 elements and force 30
            // 004:10 red iceman 1 reached blue headquarter with 19 elements and force 23
            if (place == N + 1)
            {
                gameoverred++;
                if (gameoverred >= 2)
                {
                    bobaotime();
                    cout << "blue headquarter was taken" << endl;
                }
                // 003:10 blue headquarter was taken
            }
        }
        else if (color == 'b' && place > 0)
        {
            --place;
            bobaotime();
            if (name == "iceman" && (N + 1 - place) % 2 == 0)
            {
                life -= 9;
                strength += 20;
                if (life <= 0)
                    life = 1;
            }
            if (place != 0)
                cout << "blue " << worriersarr[who] << " " << wrank << " marched to city " << place << " with " << life << " elements and force " << strength << endl;
            else
                cout << "blue " << worriersarr[who] << " " << wrank << " reached red headquarter with " << life << " elements and force " << strength << endl;
            if (place == 0)
            {
                gameoverblue++;
                if (gameoverblue >= 2)
                {
                    bobaotime();
                    cout << "red headquarter was taken" << endl;
                }
            }
        }
    }
};
class Home
{
public:
    int rank = 1;
    int sumlife = 0;
    Home(int M)
    {
        sumlife = M;
    }
    bool over = false;
    ~Home() {}
    void produce(string id, worriers *p)
    {
        int temploc = 0;
        if (id == "red")
        {
            temploc = Rquene[locred % 5];
        }
        else
            temploc = Bquene[locblue % 5];
        if (sumlife < lifearr[temploc])
            return;
        else
        {
            if (id == "red")
                locred++;
            else
                locblue++;
        }
        sumlife -= lifearr[temploc];
        switch (temploc)
        {
        case 0:
            if (id == "red")
                p[rank] = worriers('r', sumlife, rank, 0);
            else
                p[rank] = worriers('b', sumlife, rank, 0);
            break;
        case 1:
            if (id == "red")
                p[rank] = worriers('r', sumlife, rank, 1);
            else
                p[rank] = worriers('b', sumlife, rank, 1);
            break;
        case 2:
            if (id == "red")
                p[rank] = worriers('r', sumlife, rank, 2);
            else
                p[rank] = worriers('b', sumlife, rank, 2);
            break;
        case 3:
            if (id == "red")
                p[rank] = worriers('r', sumlife, rank, 3);
            else
                p[rank] = worriers('b', sumlife, rank, 3);
            break;
        case 4:
            if (id == "red")
                p[rank] = worriers('r', sumlife, rank, 4);
            else
                p[rank] = worriers('b', sumlife, rank, 4);
        }
        rank++;
    }
};
void beat(worriers &a, worriers &b)
{
    if ((a.place % 2 == 1 && abs(cityflag[a.place]) <= 1) || cityflag[a.place] <= -2)
    {
        b.life -= a.strength + a.swordstrength;
        a.swordstrength *= 0.8;
        bobaotime();
        cout << "red " << a.name << " " << a.wrank << " attacked blue " << b.name << " " << b.wrank << " in city " << a.place << " with " << a.life << " elements and force " << a.strength << endl;
        // 000:40 red iceman 1 attacked blue lion 1 in city 1 with 20 elements and force 30
        if (b.life > 0 && b.name != "ninja")
        {
            a.life -= int(b.strength * 0.5) + b.swordstrength;
            b.swordstrength *= 0.8;
            // 001:40 blue dragon 2 fought back against red lion 2 in city 1
            bobaotime();
            cout << "blue " << b.name << " " << b.wrank << " fought back against red " << a.name << " " << a.wrank << " in city " << b.place << endl;
        }
    }
    else
    {
        a.life -= b.strength + b.swordstrength;
        b.swordstrength *= 0.8;
        bobaotime();
        cout << "blue " << b.name << " " << b.wrank << " attacked red " << a.name << " " << a.wrank << " in city " << b.place << " with " << b.life << " elements and force " << b.strength << endl;
        if (a.life > 0 && a.name != "ninja")
        {
            b.life -= int(a.strength * 0.5) + a.swordstrength;
            a.swordstrength *= 0.8;
            bobaotime();
            cout << "red " << a.name << " " << a.wrank << " fought back against blue " << b.name << " " << b.wrank << " in city " << a.place << endl;
        }
    }
    if (a.life <= 0)
    {
        bobaotime();
        cout << "red " << a.name << " " << a.wrank << " was killed in city " << a.place << endl;
    }
    // 001:40 red lion 2 was killed in city 1
    else if (b.life <= 0)
    {
        bobaotime();
        cout << "blue " << b.name << " " << b.wrank << " was killed in city " << b.place << endl;
    }
}
// yell
int main()
{
    int t;
    cin >> t;
    for (int i = 1; i <= t; i++)
    {
        realt = 0;
        locred = 0;
        locblue = 0;
        gameoverred = 0;
        gameoverblue = 0;
        worriers pred[101];
        worriers pblue[101];
        cin >> M >> N >> R >> K >> T;
        Home Redhome(M), Bluehome(M);
        for (int i = 0; i < 5; i++)
        {
            cin >> lifearr[i];
        }
        for (int i = 0; i < 5; i++)
            cin >> strengtharr[i];
        for (int i = 1; i <= N; i++)
        {
            cityflag[i] = 0;
            citylife[i] = 0;
        }
        cout << "Case " << i << ":" << endl;
        while (realt <= T)
        {
            if (realt == 180)
            {
                realt = 180;
            }
            if (gameoverred >= 2 || gameoverblue >= 2)
                break;
            hours = realt / 60;
            minutes = realt % 60;
            if (minutes == 0)
            {
                Redhome.produce("red", pred);
                Bluehome.produce("blue", pblue);
                realt += 5;
            }
            else if (minutes == 5)
            {
                for (int j = 0; j <= N + 1; j++)
                {
                    for (int i = 1; i < Redhome.rank; i++)
                        if (pred[i].name == "lion" && pred[i].loyalty <= 0 && pred[i].place == j && pred[i].life > 0)
                        {
                            bobaotime();
                            // blue lion 1 ran away
                            cout << "red lion " << pred[i].wrank << " ran away" << endl;
                            pred[i].life = -1;
                        }
                    for (int i = 1; i < Bluehome.rank; i++)
                        if (pblue[i].name == "lion" && pblue[i].loyalty <= 0 && pblue[i].place == j && pblue[i].life > 0)
                        {
                            bobaotime();
                            // blue lion 1 ran away
                            cout << "blue lion " << pblue[i].wrank << " ran away" << endl;
                            pblue[i].life = -1;
                        }
                }
                realt += 5;
            }
            else if (minutes == 10)
            {
                int tempredplace[101]{0};
                for (int i = 1; i < Redhome.rank; i++)
                    tempredplace[i] = pred[i].place;
                int tempblueplace[101]{0};
                for (int i = 1; i < Bluehome.rank; i++)
                    tempblueplace[i] = pblue[i].place;
                for (int j = 0; j <= N + 1; j++)
                {
                    for (int i = 1; i < Redhome.rank; i++)
                    {
                        if (pred[i].life > 0 && tempredplace[i] + 1 == j)
                            pred[i].move();
                    }
                    for (int i = 1; i < Bluehome.rank; i++)
                    {
                        if (pblue[i].life > 0 && tempblueplace[i] - 1 == j)
                            pblue[i].move();
                    }
                }
                realt += 10;
                if (gameoverred >= 2 || gameoverblue >= 2)
                    break;
            }
            else if (minutes == 20)
            {
                for (int i = 1; i <= N; i++)
                    citylife[i] += 10;
                realt += 10;
            }
            else if (minutes == 30)
            {
                for (int p = 1; p <= N; p++)
                {
                    for (int i = 1; i < Redhome.rank; i++)
                    {
                        if (pred[i].place == p && pred[i].life > 0)
                        {
                            int flag = 1;
                            for (int j = 1; j < Bluehome.rank; j++)
                            {
                                if (pblue[j].place == p && pblue[j].life > 0)
                                {
                                    flag = 0;
                                    break;
                                }
                            }
                            if (flag)
                            {
                                Redhome.sumlife += citylife[pred[i].place];
                                bobaotime();
                                cout << "red " << pred[i].name << " " << pred[i].wrank << " earned " << citylife[pred[i].place] << " elements for his headquarter" << endl;
                                citylife[pred[i].place] = 0;
                            }
                            // 000:30 blue lion 1 earned 10 elements for his headquarter
                        }
                    }
                    for (int i = 1; i < Bluehome.rank; i++)
                    {
                        if (pblue[i].place == p && pblue[i].life > 0)
                        {
                            int flag = 1;
                            for (int j = 1; j < Redhome.rank; j++)
                            {
                                if (pred[j].place == p && pred[j].life > 0)
                                {
                                    flag = 0;
                                    break;
                                }
                            }
                            if (flag)
                            {
                                if (realt == 150 && pblue[i].name == "ninja")
                                {
                                    realt = 150;
                                }
                                Bluehome.sumlife += citylife[pblue[i].place];
                                bobaotime();
                                cout << "blue " << pblue[i].name << " " << pblue[i].wrank << " earned " << citylife[pblue[i].place] << " elements for his headquarter" << endl;
                                citylife[pblue[i].place] = 0;
                            }
                        }
                    }
                }
                realt += 5;
            }
            else if (minutes == 35)
            {
                int bluehurt[100]{0};
                for (int i = 1; i <= N; i++)
                {
                    for (int j = 1; j < Redhome.rank; j++)
                    {
                        if (pred[j].place == i && pred[j].life > 0 && pred[j].worrierweapons[2])
                        {
                            for (int s = 1; s < Bluehome.rank; s++)
                            {
                                if (pred[j].place + 1 == pblue[s].place && pblue[s].life > 0)
                                {
                                    bluehurt[s]++;
                                    pred[j].worrierweapons[2]--;
                                    pblue[s].life -= R;
                                    bobaotime();
                                    cout << "red " << pred[j].name << " " << pred[j].wrank << " shot";
                                    if (pblue[s].life <= 0)
                                    {
                                        pblue[s].shame = true;
                                        cout << " and killed blue " << pblue[s].name << " " << pblue[s].wrank;
                                        // 000:35 blue dragon 1 shot and killed red lion 4
                                    }
                                    cout << endl;
                                }
                            }
                        }
                    }
                    for (int j = 1; j < Bluehome.rank; j++)
                    {
                        if (pblue[j].place == i && (pblue[j].life > 0 || bluehurt[j]) && pblue[j].worrierweapons[2])
                        {
                            for (int s = 1; s < Redhome.rank; s++)
                            {
                                if (pred[s].place + 1 == pblue[j].place && pred[s].life > 0)
                                {
                                    pblue[j].worrierweapons[2]--;
                                    pred[s].life -= R;
                                    bobaotime();
                                    cout << "blue " << pblue[j].name << " " << pblue[j].wrank << " shot";
                                    if (pred[s].life <= 0)
                                    {
                                        pred[s].shame = true;
                                        cout << " and killed red " << pred[s].name << " " << pred[s].wrank;
                                    }
                                    cout << endl;
                                }
                            }
                        }
                    }
                }
                realt += 3;
            }
            else if (minutes == 38)
            {
                for (int i = 1; i <= N; i++)
                {
                    for (int j = 1; j < Redhome.rank; j++)
                    {
                        if (pred[j].place == i && pred[j].life > 0 && pred[j].worrierweapons[1])
                        {
                            for (int s = 1; s < Bluehome.rank; s++)
                            {
                                if (pblue[s].place == i && pblue[s].life > 0)
                                {
                                    int redlife = pred[j].life, bluelife = pblue[s].life;
                                    int redstrength = pred[j].strength, bluestrength = pblue[s].strength;
                                    int redsword = pred[j].swordstrength, bluesword = pblue[s].swordstrength;
                                    if ((abs(cityflag[i]) <= 1 && i % 2 == 1) || cityflag[i] <= -2)
                                    {
                                        bluelife -= redstrength + redsword;
                                        redsword *= 0.8;
                                        if (bluelife > 0 && pblue[s].name != "ninja")
                                        {
                                            redlife -= int(0.5 * bluestrength) + bluesword;
                                            bluesword *= 0.8;
                                        }
                                    }
                                    else
                                    {
                                        redlife -= bluestrength + bluesword;
                                        bluesword *= 0.8;
                                        if (redlife > 0 && pred[j].name != "ninja")
                                        {
                                            bluelife -= int(0.5 * redstrength) + redsword;
                                            redsword *= 0.8;
                                        }
                                    }
                                    if (redlife <= 0)
                                    {
                                        bobaotime();
                                        cout << "red " << pred[j].name << " " << pred[j].wrank << " used a bomb and killed blue " << pblue[s].name << " " << pblue[s].wrank << endl;
                                        pred[j].life = 0;
                                        pblue[s].life = 0;
                                    }
                                }
                            }
                        }
                        // 000:38 blue dragon 1 used a bomb and killed red lion 7
                    }
                    for (int j = 0; j < Bluehome.rank; j++)
                    {
                        if (pblue[j].place == i && pblue[j].life > 0 && pblue[j].worrierweapons[1])
                        {
                            for (int s = 1; s < Redhome.rank; s++)
                            {
                                if (pred[s].place == i && pred[s].life > 0)
                                {
                                    int redlife = pred[s].life, bluelife = pblue[j].life;
                                    int redstrength = pred[s].strength, bluestrength = pblue[j].strength;
                                    int redsword = pred[s].swordstrength, bluesword = pblue[j].swordstrength;
                                    if ((abs(cityflag[i]) <= 1 && i % 2 == 1) || cityflag[i] <= -2)
                                    {
                                        bluelife -= redstrength + redsword;
                                        redsword *= 0.8;
                                        if (bluelife > 0 && pblue[j].name != "ninja")
                                        {
                                            redlife -= int(0.5 * bluestrength) + bluesword;
                                            bluesword *= 0.8;
                                        }
                                    }
                                    else
                                    {
                                        redlife -= bluestrength + bluesword;
                                        bluesword *= 0.8;
                                        if (redlife > 0 && pred[s].name != "ninja")
                                        {
                                            bluelife -= int(0.5 * redstrength) + redsword;
                                            redsword *= 0.8;
                                        }
                                    }
                                    if (bluelife <= 0)
                                    {
                                        bobaotime();
                                        cout << "blue " << pblue[j].name << " " << pblue[j].wrank << " used a bomb and killed red " << pred[s].name << " " << pred[s].wrank << endl;
                                        pred[s].life = 0;
                                        pblue[j].life = 0;
                                    }
                                }
                            }
                        }
                    }
                }
                realt += 2;
            }
            else if (minutes == 40)
            {
                int redwin[100]{0}, bluewin[100]{0}, redrecord = 0, bluerecord = 0;
                for (int j = 1; j <= N; j++)
                {
                    for (int i = 1; i < Redhome.rank; i++)
                    {
                        if (pred[i].place == j && (pred[i].life > 0 || pred[i].shame))
                        {
                            for (int s = 1; s < Bluehome.rank; s++)
                            {
                                if (pblue[s].place == j && (pblue[s].life > 0 || pblue[s].shame))
                                {
                                    int redlife = pred[i].life, bluelife = pblue[s].life;
                                    if (pred[i].shame && pblue[s].shame)
                                        continue;
                                    if (pred[i].life > 0 && pblue[s].life > 0)
                                        beat(pred[i], pblue[s]);
                                    if (pred[i].life <= 0)
                                    {
                                        bluewin[bluerecord] = s;
                                        bluerecord++;
                                        if (pblue[s].name == "dragon")
                                        {
                                            pblue[s].brave += 0.2;
                                            if (pblue[s].brave > 0.8 && (cityflag[j] >= 2 || abs(cityflag[j]) <= 1 && j % 2 == 0))
                                            {
                                                bobaotime();
                                                cout << "blue dragon " << pblue[s].wrank << " yelled in city " << j << endl;
                                                // 003:40 blue dragon 2 yelled in city 4
                                            }
                                        }
                                        bobaotime();
                                        cout << "blue " << pblue[s].name << " " << pblue[s].wrank << " earned " << citylife[j] << " elements for his headquarter" << endl;
                                        // 001:40 blue dragon 2 earned 10 elements for his headquarter
                                        if (pred[i].name == "lion")
                                        {
                                            pred[i].loyalty -= K;
                                            if (pred[i].shame)
                                                pblue[s].life += 0;
                                            else
                                                pblue[s].life += redlife;
                                        }
                                        if (pblue[s].name == "wolf")
                                        {
                                            for (int ww = 0; ww < 3; ww++)
                                            {
                                                if (pblue[s].worrierweapons[ww] == 0)
                                                {
                                                    pblue[s].worrierweapons[ww] = pred[i].worrierweapons[ww];
                                                    if (ww == 0)
                                                        pblue[s].swordstrength = pred[i].swordstrength;
                                                }
                                            }
                                        }
                                        if (cityflag[j] >= 1 || cityflag[j] == -2)
                                        {
                                            if (cityflag[j] < 2)
                                            {
                                                bobaotime();
                                                cout << "blue flag raised in city " << j << endl;
                                            }
                                            cityflag[j] = 3;
                                        }
                                        else if (cityflag[j] == 0)
                                            cityflag[j] = 1;
                                        else if (cityflag[j] == -3)
                                            cityflag[j] = -2;
                                        else
                                            cityflag[j] = 1;
                                    }
                                    else if (pblue[s].life <= 0)
                                    {
                                        redwin[redrecord] = i;
                                        redrecord++;
                                        if (pred[i].name == "dragon")
                                        {
                                            pred[i].brave += 0.2;
                                            if (pred[i].brave > 0.8 && (cityflag[j] <= -2 || abs(cityflag[j]) <= 1 && j % 2 == 1))
                                            {
                                                bobaotime();
                                                cout << "red dragon " << pred[i].wrank << " yelled in city " << j << endl;
                                                // 003:40 blue dragon 2 yelled in city 4
                                            }
                                        }
                                        bobaotime();
                                        cout << "red " << pred[i].name << " " << pred[i].wrank << " earned " << citylife[j] << " elements for his headquarter" << endl;
                                        // 001:40 blue dragon 2 earned 10 elements for his headquarter
                                        if (pblue[s].name == "lion")
                                        {
                                            pblue[s].loyalty -= K;
                                            if (pblue[s].shame)
                                                pred[i].life += 0;
                                            else
                                                pred[i].life += bluelife;
                                        }
                                        if (pred[i].name == "wolf")
                                        {
                                            for (int ww = 0; ww < 3; ww++)
                                            {
                                                if (pred[i].worrierweapons[ww] == 0)
                                                {
                                                    pred[i].worrierweapons[ww] = pblue[s].worrierweapons[ww];
                                                    if (ww == 0)
                                                        pred[i].swordstrength = pblue[s].swordstrength;
                                                }
                                            }
                                        }
                                        if (cityflag[j] <= -1 || cityflag[j] == 2)
                                        {
                                            if (cityflag[j] > -2)
                                            {
                                                bobaotime();
                                                cout << "red flag raised in city " << j << endl;
                                            }
                                            cityflag[j] = -3;
                                        }
                                        else if (cityflag[j] == 0)
                                            cityflag[j] = -1;
                                        else if (cityflag[j] == 3)
                                            cityflag[j] = 2;
                                        else
                                            cityflag[j] = -1;
                                    }
                                    else
                                    {
                                        if (pred[i].name == "dragon")
                                            pred[i].brave -= 0.2;
                                        if (pblue[s].name == "dragon")
                                            pblue[s].brave -= 0.2;
                                        if (pred[i].name == "dragon" && pred[i].brave > 0.8 && (cityflag[j] <= -2 || abs(cityflag[j]) <= 1 && j % 2 == 1))
                                        {
                                            bobaotime();
                                            cout << "red dragon " << pred[i].wrank << " yelled in city " << j << endl;
                                            // 003:40 blue dragon 2 yelled in city 4
                                        }
                                        if (pblue[s].name == "dragon" && pblue[s].brave > 0.8 && (cityflag[j] >= 2 || abs(cityflag[j]) <= 1 && j % 2 == 0))
                                        {
                                            bobaotime();
                                            cout << "blue dragon " << pblue[s].wrank << " yelled in city " << j << endl;
                                            // 003:40 blue dragon 2 yelled in city 4
                                        }
                                        if (pred[i].name == "lion")
                                        {
                                            pred[i].loyalty -= K;
                                        }
                                        if (pblue[s].name == "lion")
                                        {
                                            pblue[s].loyalty -= K;
                                        }
                                        if (cityflag[j] == -2)
                                            cityflag[j] = -3;
                                        else if (cityflag[j] == 2)
                                            cityflag[j] = 3;
                                        else if (abs(cityflag[j]) <= 1)
                                            cityflag[j] = 0;
                                    }
                                }
                            }
                        }
                    }
                }
                for (int p = redrecord - 1; p >= 0; p--)
                {
                    if (Redhome.sumlife < 8)
                        break;
                    pred[redwin[p]].life += 8;
                    Redhome.sumlife -= 8;
                }
                for (int p = 0; p < bluerecord; p++)
                {
                    if (Bluehome.sumlife < 8)
                        break;
                    pblue[bluewin[p]].life += 8;
                    Bluehome.sumlife -= 8;
                }
                for (int p = 0; p < redrecord; p++)
                {
                    Redhome.sumlife += citylife[pred[redwin[p]].place];
                    citylife[pred[redwin[p]].place] = 0;
                }
                for (int p = 0; p < bluerecord; p++)
                {
                    Bluehome.sumlife += citylife[pblue[bluewin[p]].place];
                    citylife[pblue[bluewin[p]].place] = 0;
                }
                for (int i = 1; i < Redhome.rank; i++)
                    pred[i].shame = false;
                for (int j = 1; j < Bluehome.rank; j++)
                    pblue[j].shame = false;
                realt += 10;
            }
            else if (minutes == 50)
            {
                // 000:50 100 elements in red headquarter
                bobaotime();
                cout << Redhome.sumlife << " elements in red headquarter" << endl;
                bobaotime();
                cout << Bluehome.sumlife << " elements in blue headquarter" << endl;
                realt += 5;
            }
            else if (minutes == 55)
            {
                /*
                000:55 blue wolf 2 has arrow(2),bomb,sword(23)
                000:55 blue wolf 4 has no weapon
                000:55 blue wolf 5 has sword(20)
                */
                for (int s = Redhome.rank - 1; s >= 1; s--)
                {
                    if (pred[s].life > 0)
                    {
                        if (hours == 15 && minutes == 55 && pred[s].wrank == 3)
                        {
                            hours = 15;
                        }
                        int flag = 0;
                        bobaotime();
                        cout << "red " << pred[s].name << " " << pred[s].wrank << " has ";
                        if (pred[s].swordstrength == 0)
                            pred[s].worrierweapons[0] = 0;
                        for (int i = 2; i >= 0; i--)
                        {
                            if (pred[s].worrierweapons[i])
                            {
                                flag++;
                                if (i == 2)
                                    cout << "arrow(" << pred[s].worrierweapons[2] << ")";
                                else if (flag > 1 && i == 1)
                                    cout << ",bomb";
                                else if (i == 1)
                                    cout << "bomb";
                                else if (flag > 1 && i == 0)
                                    cout << ",sword(" << pred[s].swordstrength << ")";
                                else
                                    cout << "sword(" << pred[s].swordstrength << ")";
                            }
                        }
                        if (flag == 0)
                            cout << "no weapon";
                        cout << endl;
                    }
                }
                for (int s = 1; s < Bluehome.rank; s++)
                {
                    if (s == 2)
                    {
                        s = 2;
                        s = 2;
                    }
                    if (pblue[s].life > 0)
                    {
                        int flag = 0;
                        bobaotime();
                        cout << "blue " << pblue[s].name << " " << pblue[s].wrank << " has ";
                        if (pblue[s].swordstrength == 0)
                            pblue[s].worrierweapons[0] = 0;
                        for (int i = 2; i >= 0; i--)
                        {
                            if (pblue[s].worrierweapons[i])
                            {
                                flag++;
                                if (i == 2)
                                    cout << "arrow(" << pblue[s].worrierweapons[2] << ")";
                                else if (flag > 1 && i == 1)
                                    cout << ",bomb";
                                else if (i == 1)
                                    cout << "bomb";
                                else if (flag > 1 && i == 0)
                                    cout << ",sword(" << pblue[s].swordstrength << ")";
                                else
                                    cout << "sword(" << pblue[s].swordstrength << ")";
                            }
                        }
                        if (flag == 0)
                            cout << "no weapon";
                        cout << endl;
                    }
                }
                realt += 5;
            }
        }
    }
    return 0;
}
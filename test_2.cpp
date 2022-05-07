#include <iostream>
#include <string.h>
#include <cstdlib>
#include <iomanip>
using namespace std;
int timename[3]{0};
int life[6]{0};
int rankred[6]{0, 3, 4, 5, 2, 1}, rankblue[6]{0, 4, 1, 2, 3, 5};
string boy[6] = {" ", "dragon", "ninja", "iceman", "lion", "wolf"};
string cuts[3] = {"sword", "bomb", "arrow"};
int numred = 0, numblue = 0;
int flagred = 1, flagblue = 1;
int lifered = 0, lifeblue = 0;
int countred[6]{0}, countblue[6]{0};
int count = 0;
int countofred = 1, countofblue = 1;
void add(int rank, int lifes)
{
    if (rank == 1)
    {
        double morale = 0;
        cout << "It has a " << cuts[count % 3] << ",and it's morale is " << fixed << setprecision(2) << lifes * 1.0 / life[rank] << endl;
    }
    else if (rank == 2)
    {
        cout << "It has a " << cuts[count % 3] << " and a " << cuts[(count + 1) % 3] << endl;
    }
    else if (rank == 3)
    {
        cout << "It has a " << cuts[count % 3] << endl;
    }
    else if (rank == 4)
    {
        cout << "It's loyalty is " << lifes << endl;
    }
}
/*
dragon 可以拥有一件武器。编号为n的dragon降生时即获得编号为 n%3 的武器。dragon还有“士气”这个属性，是个浮点数，其值为它降生后其司令部剩余生命元的数量除以造dragon所需的生命元数量。
ninja可以拥有两件武器。编号为n的ninja降生时即获得编号为 n%3 和 (n+1)%3的武器。
iceman有一件武器。编号为n的iceman降生时即获得编号为 n%3 的武器。
lion 有“忠诚度”这个属性，其值等于它降生后其司令部剩余生命元的数目。
wolf没特点。
*/
void Red(int &lifes, int &num, int &flag)
{
    if (flag == 0)
        return;
    cout << timename[0] << timename[1] << timename[2] << " ";
    flag = 0;
    for (int i = 1; i < 6; i++)
        if (lifes >= life[i])
        {
            flag = 1;
            break;
        }
    if (flag == 0)
    {
        cout << "red headquarter stops making warriors" << endl;
        return;
    }
    for (int i = num;; i++)
    {
        if (lifes >= life[rankred[i % 5 + 1]])
        {
            num = i;
            countred[rankred[i % 5 + 1]]++;
            cout << "red " << boy[rankred[i % 5 + 1]] << " " << countofred << " born with strength " << life[rankred[i % 5 + 1]]
                << ',' << countred[rankred[i % 5 + 1]] << " " << boy[rankred[i % 5 + 1]] << " in red headquarter" << endl;
            lifes -= life[rankred[i % 5 + 1]];
            num++;
            add(rankred[i % 5 + 1], lifes);
            countofred++;
            break;
        }
    }
}
void Blue(int &lifes, int &num, int &flag)
{
    if (flag == 0)
        return;
    cout << timename[0] << timename[1] << timename[2] << " ";
    flag = 0;
    for (int i = 1; i < 6; i++)
        if (lifes >= life[i])
        {
            flag = 1;
            break;
        }
    if (flag == 0)
    {
        cout << "blue headquarter stops making warriors" << endl;
        return;
    }
    for (int i = num;; i++)
    {
        if (lifes >= life[rankblue[i % 5 + 1]])
        {
            num = i;
            countblue[rankblue[i % 5 + 1]]++;
            cout << "blue " << boy[rankblue[i % 5 + 1]] << " " << countofblue << " born with strength " << life[rankblue[i % 5 + 1]]
                << ',' << countblue[rankblue[i % 5 + 1]] << " " << boy[rankblue[i % 5 + 1]] << " in blue headquarter" << endl;
            lifes -= life[rankblue[i % 5 + 1]];
            num++;
            add(rankblue[i % 5 + 1], lifes);
            countofblue++;
            break;
        }
    }
}
int main()
{
    int n, M;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> M;
        lifered = lifeblue = M;
        for (int j = 1; j <= 5; j++)
            cin >> life[j];
        cout << "Case:" << i << endl;
        memset(timename, 0, sizeof(timename));
        numred = numblue = 0;
        flagred = flagblue = 1;
        count = 0;
        memset(countred, 0, sizeof(countred));
        memset(countblue, 0, sizeof(countblue));
        countofred = countofblue = 1;
        while (flagred + flagblue)
        {
            timename[0] = count / 100;
            timename[1] = (count % 100) / 10;
            timename[2] = count % 10;
            count++;
            Red(lifered, numred, flagred);
            Blue(lifeblue, numblue, flagblue);
        }
    }
    system("pause");
    return 0;
}
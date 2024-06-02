#ifndef CORRECTEXE_H
#define CORRECTEXE_H

#include <string>
#include<algorithm>
#include<map>
#include<set>
#include<vector>
#include<cstring>
#include<QDebug>

using namespace std;

class Warrior{
public:
    string name;
    bool color;//
    int id;
    mutable int strength;
    int place;
    int dir;
    int weapon[3];
    int attk;
    mutable int swordatk;
    mutable int arrowrem;
    int icestep;//iceman steps
    int loyalty;
    double morale;
    Warrior(string s,int ptr,int M_have,int c);
    bool operator < (const Warrior &b)const;
};

class City{
public:
    int flag;//
    int m;
    int pos;
    int prevwinner;//
    City(int p=0);
};

//City city[maxn];
//set<Warrior> samurai;
class Base{
public:
    int m;
    bool down;
    int ptr;//
    int enemycnt;
    Base(int _M);
    Warrior build(bool color);
};


#endif // CORRECTEXE_H

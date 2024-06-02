#ifndef CASEINFO_H
#define CASEINFO_H


#include <QPair>
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

class Gamestate{
public:
    //一个Case 里 一个时间点的所有状态
    int ctime;
    set<Warrior> samurai;
    Base rbase;
    Base bbase;
    vector<City> cityline;
    Gamestate(int t,set<Warrior> &s,Base &rb,Base &bb,vector<City> city,QString str="");
    QString report;
};

class Caseinfo{
public:
    int M,N,R,K,T;
    string rord[5]={"iceman","lion","wolf","ninja","dragon"};
    string bord[5]={"lion","dragon","ninja","iceman","wolf"};
    map<string,int> hp,atk;
    //前面是Case对应的全局变量
    vector<Gamestate> info;
    Caseinfo(vector<Gamestate> in);
    Caseinfo(int m,int n,int r,int k,int t,string *ror,string *bor,map<string,int> &H,map<string,int> &at);
    Caseinfo();
    void addState(Gamestate g);
};

class Allcases{
public:
    vector< QPair<QString,Caseinfo> > Cases;
    void addACase(const QPair<QString,Caseinfo> & Case);
};

Allcases correctrun(QString data);
void init();
void saveAState(int t,Base rb,Base bb);
bool virtualfight(int place,Warrior wblue,Warrior wred,int col);
int solve(vector<int> v,int indexcnt);

#endif // CASEINFO_H

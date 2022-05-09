//
// Created by 陆明奇 on 2022/5/9.
//

#ifndef CLAUSE_RESOLUTION_INFO_H
#define CLAUSE_RESOLUTION_INFO_H

#include <string>
#include <map>
#include <queue>
using namespace std;

struct implication
{
    string KB; //input
    int count=0;// num of precursor
    map<string,bool> hasKnown; //whether precursor is known
    string conclusion; //consequent
};

extern implication p[50];
extern queue<string> agenda; //unused facts
extern string target;
extern int KB_Num;

void input();
void transition();

#endif //CLAUSE_RESOLUTION_INFO_H

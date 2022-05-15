//
// Created by 陆明奇 on 2022/5/9.
//

#include "info.h"
#include<iostream>
#include<algorithm>
using namespace std;

implication p[50];
queue<string> agenda; //unused facts
string target;
int KB_Num;

void input()
{
    cout<<"Please input the number of facts"<<endl;
    int num;
    cin>>num;
    string fact;
    cout<<"Please input every one of the facts"<<endl;
    for(int i=0;i<num;i++){
        cin>>fact;
        agenda.push(fact);
    }

    cout<<"Please input the number of implications"<<endl;
    cin>>KB_Num;
    cout<<"Please input every one of the implications"<<endl;
    for(int i=0;i<KB_Num;i++){
        cin>>p[i].KB;
    }

    cout<<"Please input the target"<<endl;
    cin>>target;
}

//arrange the struct in ascending order according to the number of precursors
bool cmp (implication a, implication b)
{
    return a.count<b.count;
}

void transition()
{
    string s;
    for(int i=0;i<KB_Num;i++){
        int size=p[i].KB.size();
        for(int j=0;j<size;j++) {

            // finish reading clause
            if (p[i].KB[j] == '&') {
                p[i].count++;
                p[i].hasKnown[s] = false; //the precursor hasn't become a fact(not proved) yet
                s = "";
            }

            //the last one is conclusion
            else if (p[i].KB[j] == '-') {
                p[i].count++;
                p[i].hasKnown[s] = false; //the precursor hasn't become a fact(not proved) yet
                s = "";
                p[i].conclusion = p[i].KB.substr(j + 2);
                break;
            }

            //is  reading a clause
            else {
                s += p[i].KB[j];
            }
        }
    }
    sort(p,p+KB_Num,cmp);
    //cout<<"Transition has completed"<<endl;
}

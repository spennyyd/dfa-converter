/*
    @author Spencer Davis
    Operating System: Ubuntu 20.04
    Compiled with g++ 9.3.0

    Computer Theory 
    Assignment: Regex to NFA 
*/

#ifndef NFA_H
#define NFA_H
#include <bits/stdc++.h>


struct nfa_on{
    std::vector<int> one;
    std::vector<int> zero;
    std::vector<int> e;
};

/*
    nfa table
*/
class Nfa{
    public:
        int stateCount = 0;
        std::map<int, nfa_on> transitions; 

        int start;
        int end;

        // Constructor
        Nfa();

        // Methods
        int addState();
        void addTransition(int from, int to, char on);
        void printTable();
        void setStart(int);
        void setEnd(int);
        std::pair<int, int> addMachine(char on);
        std::pair<int, int> concat(std::pair<int, int> second, std::pair<int,int> first);
        std::pair<int,int> buildOr(std::pair<int, int> second, std::pair<int,int> first);
        std::pair<int, int> buildStar(std::pair<int,int> machine);

};
#endif
/*
    @author Spencer Davis
    Operating System: Ubuntu 20.04
    Compiled with g++ 9.3.0

    Computer Theory 
    Assignment: Regex to NFA 
*/

#include <iostream>
#include <vector>
#include <string>
#include "Nfa.h"

Nfa::Nfa()
{

}

int Nfa::addState()
{
    // Create a new key for the current state count. Starts at 0
    
    transitions[stateCount];
    // Increment the statecount
    
    stateCount++;
    return stateCount - 1;
}

void Nfa::addTransition(int from, int to, char on)
{
    switch(on)
    {
        case '0':
            transitions[from].zero.push_back(to);
            break;
        case '1':
            transitions[from].one.push_back(to);
            break;
        case 'e':
            transitions[from].e.push_back(to);
            break;
    }
}

std::pair<int, int> Nfa::addMachine(char on)
{
    
    int from  = addState();
    int to = addState();
    addTransition(from, to, on);
    std::pair<int, int> return_val(from, to);

    std::cout << "Current Machine: " << from << " to " << to << std::endl;
    return return_val;
}

// Given the first set of states and the second set of states
// create another 2 states and add e transitions
std::pair<int, int> Nfa::concat(std::pair<int, int> second, std::pair<int, int> first)
{
    int inter = addState();
    int newStart = addState();
    int newEnd = second.second;

    std::cout << "Intermediate: " << inter << " New Start: " << newStart << " New End: " << newEnd << std::endl;
    addTransition(first.second, inter, 'e');
    addTransition(inter, second.first, 'e');
    addTransition(newStart, first.first, 'e');

    return std::make_pair(newStart, newEnd);
}

std::pair<int, int> Nfa::buildOr(std::pair<int, int> second, std::pair<int, int> first)
{
    int newStart = addState();
    int newEnd = addState();

    addTransition(newStart, first.first, 'e');
    addTransition(newStart, second.first, 'e');
    addTransition(first.second, newEnd, 'e');
    addTransition(second.second, newEnd, 'e');

    return std::make_pair(newStart, newEnd);
}

std::pair<int, int> Nfa::buildStar(std::pair<int,int> machine)
{
    int newStart = addState();
    int newEnd = addState();

    addTransition(newStart, newEnd, 'e');
    addTransition(newStart, machine.first, 'e');
    addTransition(newEnd, newStart, 'e');
    addTransition(machine.second, newEnd, 'e');

    return std::make_pair(newStart, newEnd);
}

void Nfa::printTable()
{
    std::cout << "States\t0\t1\te\n";
    for(int i = 0; i < transitions.size(); ++i)
    {
        std::cout << i << "\t[ ";
         
        for(int j = 0; j < transitions[i].zero.size(); ++j)
        {
            std::cout << transitions[i].zero[j] << " ";
        }
        std::cout << "]\t[ ";
        for(int j = 0; j < transitions[i].one.size(); ++j)
        {
            std::cout << transitions[i].one[j] << " ";
        }
        std::cout << "]\t[ ";
        for(int j = 0; j < transitions[i].e.size(); ++j)
        {
            std::cout << transitions[i].e[j] << " ";
        }
        std::cout << "]\n";
    }
}

void Nfa::setStart(int start_)
{
    start = start_;
}

void Nfa::setEnd(int end_)
{
    end = end_;
}

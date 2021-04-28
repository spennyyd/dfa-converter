#ifndef DFA_H
#define DFA_H

#include <bits/stdc++.h>
#include "Nfa.h"
/*
    Struct that contains the state name, and it's transitions
*/
struct state{

    std::vector<int> one;
    std::vector<int> zero;
};


class Dfa{

    /*
        Private Variables
    */
    std::set<std::string> states;                           // Used to get the set of all states that will be in the DFA
    std::map<std::string, state> state_map;               // Transitions of all states in the 
    int nfa_start;                                  // Start state of the NFA
    int nfa_end;                                    // End state of the NFA
    std::map<int, nfa_on> nfa_transitions;
    

    /*
        Private Methods
    */
    std::vector<int> epsilon_enclosure(int);
    std::vector<int> split_spaces(std::string);
    std::string order_states(std::string);
    std::vector<int> on_one(std::vector<int>);
    std::vector<int> on_zero(std::vector<int>);


    public:
        /*
            Public Variables
        */
        std::string start_state;
        std::string end_state;

        /*
            Public Mehods
        */

        // Constructor. Arguments are: e transitions, 1 transtioins, 0 transitions, Start State, End state
        Dfa(std::map<int, nfa_on>, int, int);

        // Conversion from NFA to DFA
        bool convert();

};
#endif

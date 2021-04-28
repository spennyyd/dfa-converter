#include <bits/stdc++.h>
#include "dfa.h"
/*
    Constructor to make DFA object.
    Parameters:
    e_trans: e transitions from NFA
    one_trans: one transitions from NFA
    zero_trans: zero transitions from NFA
    start: Start state from NFA
    end: End state from NFA
*/
Dfa::Dfa(std::map<int, nfa_on> transitions, int start, int end)
{
    nfa_start = start;
    nfa_end = end;
    nfa_transitions = transitions;
}

/*
    Convert all NFA transitions and states held within the DFA object into a DFA
*/
bool Dfa::convert()
{
    // Start at the start state
    std::cout << "epsilon enclosure of start\n";
    std::vector<int> dfa_start = epsilon_enclosure(nfa_start);
    std::cout << "after start closure\n";
    std::string temp_string = "";
    std::vector<int> cur_state = epsilon_enclosure(nfa_start);
    bool new_state_added = true;

    for(int i = 0; i < cur_state.size(); ++i)
    {
        temp_string.append(std::to_string(cur_state[i]));

        if(i != cur_state.size() - 1)
        {
            temp_string.append(" ");
        }
    }
    state_map[temp_string];

    states.insert(temp_string);

    // remove me
    std::cout << "Before while loop\n";
    while(new_state_added)
    {
        int cur_size = states.size();   
        
        // Go through each state in the NFA that makes up the DFA state
        // Get the transitions on zero and one
        
        std::map<std::string, state>::iterator it;
        for(it = state_map.begin(); it != state_map.end(); ++it)
        {
            cur_state.clear();
            temp_string.clear();
            for(int i = 0; i < it->first.size(); ++i)
            {
                if(it->first[i] != ' ')
                {
                    temp_string.append(1, it->first[i]);
                }
                else{
                    cur_state.push_back(std::stoi(temp_string));
                    temp_string.clear();
                }
                
            }

            if(temp_string.size() > 0)
            {
                cur_state.push_back(std::stoi(temp_string));
            }
            
            for(int i = 0; i < cur_state.size(); ++i)
            {
               std::cout << cur_state[i] <<  " "; 
            }
            std::cout << std::endl;
            on_one(cur_state);
            on_zero(cur_state);
        }

        
        // If the size of the set at the beginning of the loop is the same as
        // the size of the set at the end of the loop. No new state was added.
        if(states.size() == cur_size)
        {
            new_state_added = false;
        }
    }

    std::cout << "DFA Transitions \t 1 \t 0\n";
    std::map<std::string, state>::iterator it;
    for(it = state_map.begin(); it != state_map.end(); it++)
    {
        std::cout << "[" << it->first << "]\t";

        std::cout<< "[ ";
        for(int i = 0; i < it->second.one.size(); ++i)
        {
            std::cout << it->second.one[i] << " ";
        }
        std::cout << "]\t[ ";
        for(int i = 0; i < it->second.zero.size(); ++i)
        {
            std::cout << it->second.zero[i] << " ";
        }
        std::cout << "]\n";
    }

    return true;
}

// Given a set of states return the set of states you can go on a one
std::vector<int> Dfa::on_one(std::vector<int> cur_state)
{
    std::set<int> set;
    std::vector<int> one_transitions;
    std::vector<int> enclosed;
    std::string as_string = "";
    // Loop through and get the transitions
    for(int i = 0; i < cur_state.size(); ++i)
    {
        one_transitions.clear();
        one_transitions = nfa_transitions[cur_state[i]].one;

        enclosed.clear();
        for(int j = 0; j < one_transitions.size(); ++j)
        {
            enclosed = epsilon_enclosure(one_transitions[j]);
            for(int k = 0; k < enclosed.size(); ++k)
            {
                set.insert(enclosed[k]);
            }
        }
    }

    // Iterate over the set and put into a vector
    one_transitions.clear();
    std::set<int>::iterator it;
    for(it = set.begin(); it != set.end(); ++it)
    {
        one_transitions.push_back(*it);
    }

    // Turn the vector into a string
    for(int i = 0; i < cur_state.size(); ++i)
    {
        as_string.append(std::to_string(cur_state[i]));

        if(i != cur_state.size() - 1)
        {
            as_string.append(" ");
        }
    }


    state_map[as_string].one = one_transitions;
    

    as_string.clear();
    for(int i = 0; i < one_transitions.size(); ++i)
    {
        as_string.append(std::to_string(one_transitions[i]));

        if(i != one_transitions.size() - 1)
        {
            as_string.append(" ");
        }
    }

    states.insert(as_string);
    state_map[as_string];

    return one_transitions;
}

// Given a set of states return where you can go on a zero
std::vector<int> Dfa::on_zero(std::vector<int> cur_state)
{
    std::set<int> set;
    std::vector<int> zero_transitions;
    std::vector<int> enclosed;
    std::string as_string = "";
    // Loop through and get the transitions
    for(int i = 0; i < cur_state.size(); ++i)
    {
        zero_transitions.clear();
        zero_transitions = nfa_transitions[cur_state[i]].zero;

        enclosed.clear();
        for(int j = 0; j < zero_transitions.size(); ++j)
        {
            enclosed = epsilon_enclosure(zero_transitions[j]);
            for(int k = 0; k < enclosed.size(); ++k)
            {
                set.insert(enclosed[k]);
            }
        }
    }

    // Iterate over the set and put into a vector
    zero_transitions.clear();
    std::set<int>::iterator it;
    for(it = set.begin(); it != set.end(); ++it)
    {
        zero_transitions.push_back(*it);
    }

    // Turn the vector into a string
    for(int i = 0; i < cur_state.size(); ++i)
    {
        as_string.append(std::to_string(cur_state[i]));

        if(i != cur_state.size() - 1)
        {
            as_string.append(" ");
        }
    }

    // Test if the current enclosed state exists within the map

    state_map[as_string].zero = zero_transitions;
 

    as_string.clear();
    for(int i = 0; i < zero_transitions.size(); ++i)
    {
        as_string.append(std::to_string(zero_transitions[i]));

        if(i != zero_transitions.size() - 1)
        {
            as_string.append(" ");
        }
    }

    states.insert(as_string);
    state_map[as_string];

    return zero_transitions;
}

/*
    Given a state from the NFA return a string with all epsilon transitions enclosed in a single string
*/
std::vector<int> Dfa::epsilon_enclosure(int nfa_state)
{
    std::cout << "in enclosure with " << nfa_state << std::endl;
    std::set<int> enclosed_states;
    std::vector<int> sort_me;
    std::string enclosed = "";
    std::queue<int> enclose_me;

    sort_me.push_back(nfa_state);

    // Add all states to the queue
    for(int i = 0; i < nfa_transitions[nfa_state].e.size(); ++i)
    {
        enclose_me.push(nfa_transitions[nfa_state].e[i]);    
    }


    // Go through the queue and enclose each state.
    while(!enclose_me.empty())
    {
        std::vector<int> temp = epsilon_enclosure(enclose_me.front());
        enclose_me.pop();
        for(int j = 0; j < temp.size(); ++j)
        {
            enclosed_states.insert(temp[j]);
        }
    }

    // Iterate over set and put into a vector<int>
    std::set<int>::iterator it;
    for(it = enclosed_states.begin(); it != enclosed_states.end(); ++it)
    {
        sort_me.push_back(*it);
    }
    
    // Sort
    std::sort(sort_me.begin(), sort_me.end());

    for(int i = 0; i < sort_me.size(); ++i)
    {
        enclosed.append(std::to_string(sort_me[i]));

        if(i != sort_me.size() - 1)
        {
            enclosed.append(" ");
        }
    }

    return sort_me;
}
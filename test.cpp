#include <bits/stdc++.h>

int main(int argc, char const *argv[])
{
    int count = 0;
    std::set<std::string> test_set;
    std::map<std::string, std::vector<int>> state_map;
    bool new_state_added = true;

    test_set.insert("0 5 6 11 12");

    std::set<std::string>::iterator it = test_set.begin();
    std::set<std::string>::iterator end = test_set.end();


    std::cout << "Before While\n";
    while(new_state_added)
    {
        int cur_size = test_set.size();   

        if(state_map.find(*it) == state_map.end())
        {
            state_map.insert(*it, {});
        }
        
        // Go through each state in the NFA that makes up the DFA state
        // Get the transitions on zero and one
        if(count < 5)
        {
            test_set.insert(std::to_string(count));
        }
        ++count;
        // If the size of the set at the beginning of the loop is the same as
        // the size of the set at the end of the loop. No new state was added.
        if(test_set.size() == cur_size)
        {
            new_state_added = false;
        }
    }

    for(it = test_set.begin(); it != test_set.end(); ++it)
    {
        std::cout << *it << std::endl;
    }
    return 0;
}

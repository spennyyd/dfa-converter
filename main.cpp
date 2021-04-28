/*
    @author Spencer Davis
    Operating System: Ubuntu 20.04
    Compiled with g++ 9.3.0

    Computer Theory 
    Assignment: Regex to NFA 

    NOTE:
    This checks for 1's and 0's as opposed to the example on canvas that uses a's and b's in the alphabet.
*/
#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include "Nfa.h"
#include "dfa.h"

/*
    PROTOTTYPES
*/
bool s(std::string);
bool e(std::string);
bool t(std::string);
bool f(std::string);
bool q(std::string);
bool r(std::string);
bool u(std::string);
void printTable(void);


// Global variables.
// Current Character
// Stack to keep track of start and end states
// Table that represents the nfa
std::string::iterator current_char;
std::stack < std::pair<int, int> > stateStack;
Nfa table;


/*
    MAIN FUNCTION
*/
int main()
{
    // Variables
    std::string expression;
    bool valid;
    std::string expression_list[100];

    std::cout << "\n\nWelcome to the regular expression grammar checker!\n\n";
    std::cout << "The current valid alphabet is { 0, 1, +, *, (, ) }\n";
    std::cout << "These are the grammar rules: \n\n";
    std::cout <<    "Start --> Expression <end of line>\n"
                     "Expression --> Expression + Term\n"
                     "Term --> Term Factor\n"
                     "Term --> Factor\n"
                     "Factor --> 0\n"
                     "Factor --> 1\n"
                     "Factor --> Factor *\n"
                     "Factor --> ( Expression )\n"
                     "----------------------------------\n";
    // Get input from user
    std::cout << "Please enter an expression (type \"end\" to quit): \n";
    std::cin >> expression;

    while(expression != "end")
    {
        // Send expression for validation
        valid = s(expression);
        
        if(valid)
        {
            table.printTable();
            std::pair<int, int> temp = stateStack.top();
            std::cout << "Start State: " << temp.first << std::endl;
            std::cout << "End State: " << temp.second << std::endl;
            table.setStart(temp.first);
            table.setEnd(temp.second);

            std::cout << "before dfa created\n";
            Dfa dfa_table(table.transitions, table.start, table.end);
            dfa_table.convert();
            std::cout << "Valid:\t\t" << expression << std::endl;
        }
        else
        {
            std::cout << "Invalid:\t" << expression << std::endl;
        }
        
        // Get user input again
        std::cout << "Please enter an expression (type \"end\" to quit): \n";
        std::cin >> expression;
    }
    
    return 0;
} // End of main


/* 
    START OF RECURSIVE FUNCTIONS
*/

// Go to t
// then q
// Then check if the current character is 
// the end of expression
bool s(std::string expression)
{
    // Set the current character to the start of the string
    current_char = expression.begin();
    if(!t(expression))
    {
        return false;
    }
    if(!q(expression))
    {
        return false;
    }
    if(current_char == expression.end())
    {
        return true;
    }
    return false;
}

// Go to t
// then q
// then check if the current character is a )
//and not the end of the expression
bool e(std::string expression)
{
    if(!t(expression))
    {
        return false;
    }
    if(!q(expression))
    {
        return false;
    }
    if(*current_char == ')' && current_char != expression.end())
    {
        return true;
    }
    return false;

}

// Check if the current character is a ( or a 0 or a 1
// Then go to f and r
bool t(std::string expression)
{
    if(*current_char == '(' || *current_char == '0' || *current_char == '1')
    {
        if(!f(expression))
        {
            return false;
        }
        // Possibility number 2

        if(!r(expression))
        {
            return false;
        }
        return true;
    }
    return false;
}

// Look for ( 0 or 1
// Then check if it's 0 or 1
// If it is 0 or 1 switch to next character and go to u
// If it isn't 0 or 1 but is an ( switch to next character
// then go to e
// Then check if the current character is )
// Then go to u
bool f(std::string expression)
{
    if(*current_char == '(' || *current_char == '0' || *current_char == '1')
    {
        if(*current_char == '0' || *current_char == '1')
        {
            stateStack.push(table.addMachine(*current_char));
            
            ++current_char;
            if(!u(expression))
            {
                return false;
            }
            return true;
        }
        else if(*current_char == '(')
        {
            ++current_char;
            if(!e(expression))
            {
                return false;
            }
            if(*current_char == ')')
            {
                ++current_char;
            }
            else
            {
                return false;
            }
            if(!u(expression))
            {
                return false;
            }
            return true;
            
        }

    }
    return false;
}

// Looks for the + operator.
// If it is the + operator continue to the next character
// go to t and then q
bool q(std::string expression)
{
    if(*current_char == '+')
    {
        ++current_char;
        if(!t(expression))
        {
            return false;
        }
        std::pair<int, int> temp1 = stateStack.top();
        stateStack.pop();
        std::pair<int, int> temp2 = stateStack.top();
        stateStack.pop();
        stateStack.push(table.buildOr(temp1, temp2));
        if(!q(expression))
        {
            return false;
        }

    }
    return true;
}

// Looks for opening paranthesis 0 or 1
// If its any of those go to f and then r
bool r(std::string expression)
{
    if(*current_char == '(' || *current_char == '0' || *current_char == '1')
    {
        if(!f(expression))
        {
            return false;
        }
        // Possibilibty number 1
        std::pair<int, int> temp1 = stateStack.top();
        stateStack.pop();
        std::pair<int, int> temp2 = stateStack.top();
        stateStack.pop();

        stateStack.push(table.concat(temp1, temp2));
        if(!r(expression))
        {
            return false;
        }
    }
    return true;
}

// Looks for the repeat symbol
// Switches to next character
// go to u
bool u(std::string expression)
{
    // Add 4 epsilon transitions
    // and 2 new states
    if(*current_char == '*')
    {
        stateStack.push(table.buildStar(stateStack.top()));
        ++current_char;
        u(expression);
    }
    return true;
}
#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;

// Add prototypes of helper functions here
void wordleHelper(std::string in, const std::string& floating, const std::set<std::string>& dict, std::set<std::string>& results, unsigned int position);
//bool hasFloats(std::string in, std::string floating);
bool isValid(std::string in, const std::string& floating);

// Definition of primary wordle function
std::set<std::string> wordle(const std::string& in, const std::string& floating, const std::set<std::string>& dict)
{
    // Add your code here
    std::set<std::string> results;
    std::string incopy = in;
    std::string fcopy = floating;

    wordleHelper(incopy, fcopy, dict, results, 0);
    return results;
}

// Define any helper functions here
void wordleHelper(std::string in, const std::string& floating, const std::set<std::string>& dict, std::set<std::string>& results, unsigned int position)
{
    if(!isValid(in, floating))
        return;

    if(position == in.length())
    {
        if(dict.find(in) != dict.end() && isValid(in, floating))
            results.insert(in);

        return;
    }
    if(in[position] == '-')
    {
        for(char c='a'; c <= 'z'; c++)
        {
            in[position] = c;
            wordleHelper(in, floating, dict, results, position+1);
        }
    }
    else
        wordleHelper(in, floating, dict, results, position+1);
}

bool isValid(std::string in, const std::string& floating)
{
    if(floating == "")
        return true;
    for(unsigned int i=0; i<floating.length(); i++)
    { 
        if(in.find(floating[i]) == std::string::npos && in.find('-') == std::string::npos)
            return false;
        else
        {
            if(in.find(floating[i]) != std::string::npos)
                in.erase(in.find(floating[i]), 1);
            else
                in.erase(in.find('-'), 1);
        }
    }
    return true;
}
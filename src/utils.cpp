#include "utils.h"

#include <cctype>

unsigned getPasswordStrength(const std::string &pw)
{
    unsigned score{ 0 };

    if(pw.size() >= 8)
    {
        score += 25;
    }

    bool hasAplha{ false };
    bool hasDigit{ false };

    for(auto c : pw)
    {
        if(std::isalpha(c) && !hasAplha)
        {
            score += 25;
            hasAplha = true;
        }
        else if(std::isdigit(c) && !hasDigit)
        {
            score += 25;
            hasDigit = true;
        }
    }

    if(pw.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890") != std::string::npos)
    {
        score += 25;
    }

    return score;
}

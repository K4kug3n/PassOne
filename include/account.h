#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

struct Account{
    Account(std::string const& siteName, std::string const& log, std::string const& pwrd):
        siteName{siteName},
        login{ log },
        password{ pwrd }
    {
    }

    std::string siteName;
    std::string login;
    std::string password;
};

#endif // ACCOUNT_H

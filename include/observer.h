#ifndef OBSERVER_H
#define OBSERVER_H

#include <string>
#include <optional>

class Observer
{
public:
    Observer();

    virtual void clickDetails(size_t id) = 0;
    virtual void input(std::string const& login, std::string const& pw, std::string const& siteName, std::optional<size_t> const& id) = 0;
    virtual void remove(size_t id) = 0;
    //virtual void edit(size_t id) = 0;
    virtual void inputAsked() = 0;
    virtual void editAsked(size_t id) = 0;


    virtual ~Observer();
};

#endif // OBSERVER_H

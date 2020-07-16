#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include <vector>
#include <functional>
#include <optional>

#include "observer.h"

class Observable
{
public:
    Observable();

    void addObserver(Observer & obs);

    void notifyDetail(size_t id);
    void notifyInputAsked();
    void notifyEditAsked(size_t id);
    void notifyInput(std::string const& login, std::string const& pw, std::string const& siteName, std::optional<size_t> const& id);
    void notifyRemove(size_t id);

private:
    std::vector<std::reference_wrapper<Observer>> observers;
};

#endif // OBSERVABLE_H

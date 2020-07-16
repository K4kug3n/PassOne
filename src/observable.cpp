#include "observable.h"

Observable::Observable()
{

}

void Observable::addObserver(Observer & obs)
{
    observers.push_back(obs);
}

void Observable::notifyDetail(size_t id)
{
    for(auto & observer : observers){
        observer.get().clickDetails(id);
    }
}

void Observable::notifyInputAsked()
{
    for(auto & observer : observers){
        observer.get().inputAsked();
    }
}

void Observable::notifyEditAsked(size_t id)
{
    for(auto & observer : observers){
        observer.get().editAsked(id);
    }
}

void Observable::notifyInput(const std::string &login, const std::string &pw, const std::string &siteName, std::optional<size_t> const& id)
{
    for(auto & observer : observers){
        observer.get().input(login, pw, siteName, id);
    }
}

void Observable::notifyRemove(size_t id)
{
    for(auto & observer : observers){
        observer.get().remove(id);
    }
}

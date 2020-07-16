#include "controller.h"

#include <algorithm>
#include <iostream>

Controller::Controller(Model & model, MainWindow & view):
    model(model),
    view(view)
{
    view.addObserver(*this);
}

void Controller::clickDetails(size_t id)
{
    auto it = std::find_if(model.begin(), model.end(), [id](auto const& account){ return account.id == id; });

    if(it != model.end()){
        view.showDetails(it->id, it->account.siteName, it->account.login, it->account.password);
    }

}

void Controller::inputAsked()
{
    view.getForm().setTitle("New Account");

    view.showForm();
}

void Controller::editAsked(size_t id)
{
    auto it = std::find_if(model.begin(), model.end(), [id](auto const& account){ return account.id == id; });

    if(it != model.end()){
        view.getForm().setTitle("Edit Account");

        view.getForm().setSiteName(it->account.siteName);
        view.getForm().setLogin(it->account.login);
        view.getForm().setPassword(it->account.password);
        view.getForm().setId(it->id);

        view.showForm();
    }
}

void Controller::input(const std::string &login, const std::string &pw, const std::string &siteName, std::optional<size_t> const& id)
{
    if(id.has_value()){
        edit(login, pw, siteName, id.value());
    }
    else{
        add(siteName, login, pw);
    }

    save("save.json");
}

void Controller::remove(size_t id){
    model.removeAccount(id);

    save("save.json");

    updatePresentation();
    view.showAccountList();
}

/*void Controller::addAccountInView(const std::string &name, const std::string &login, const std::string &password)
{
    size_t id{ model.addAccount(name, login, password) };

    view.addAccount(id, name);
}*/

void Controller::updatePresentation()
{
    view.resetPresentation();

    for(auto it{ model.cbegin() }; it != model.cend(); it++){
        view.addAccount(it->id, it->account.siteName);
    }
}

void Controller::save(const std::string &path)
{
    model.save(path);
}

void Controller::load(const std::string &path)
{
    model.load(path);

    for(auto it{ model.begin() }; it != model.end(); it++){
        view.addAccount(it->id, it->account.siteName);
    }
}

Controller::~Controller()
{
}

void Controller::add(const std::string &name, const std::string &login, const std::string &password)
{
    auto id{ model.addAccount(name, login, password) };

    view.addAccount(id, name);
}

void Controller::edit(const std::string &login, const std::string &pw, const std::string &siteName, size_t id)
{
    Model::iterator it{ std::find_if(model.begin(), model.end(), [id](auto const& account){
        return (account.id == id);
    }) };

    if(it != model.end()){
        it->account.siteName = siteName;
        it->account.login = login;
        it->account.password = pw;
    }

    updatePresentation();
}

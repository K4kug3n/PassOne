#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "mainwindow.h"
#include "model.h"
#include "observer.h"

class Controller : public Observer
{
public:
    Controller(Model & model, MainWindow & view);

    void clickDetails(size_t id) override;
    void input(std::string const& login, std::string const& pw, std::string const& siteName, std::optional<size_t> const& id) override;
    void remove(size_t id) override;
    void inputAsked() override;
    void editAsked(size_t id) override;

    //void addAccountInView(std::string const& name, std::string const& login, std::string const& password);

    void updatePresentation();

    void save(std::string const& path);
    void load(std::string const& path);

    ~Controller() override;

private:
    void add(std::string const& name, std::string const& login, std::string const& password);
    void edit(std::string const& login, std::string const& pw, std::string const& siteName, size_t id);

    Model & model;
    MainWindow & view;
};

#endif // CONTROLLER_H

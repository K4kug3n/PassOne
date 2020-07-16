#include "model.h"

#include <algorithm>

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonDocument>
#include <QFile>

#include <QDebug>

Model::Model() :
    nextId{ 0 }
{
}

size_t Model::addAccount(std::string const& siteName, std::string const& login, std::string const& password)
{
    size_t currentId = nextId;
    addAccount( InternalAccount{ Account{ siteName, login, password }, nextId });

    nextId++;

    return currentId;
}

void Model::save(const std::string &path)
{
    QJsonObject recordObject;

    recordObject.insert("Next ID", QJsonValue(QString::number(nextId)));

    QJsonArray accountsObject;
    for(iterator it{ begin() }; it != end(); it++){
        QJsonObject account;

        account.insert("ID", QJsonValue(QString::number(it->id)));
        account.insert("Site Name", QJsonValue(QString::fromStdString(it->account.siteName)));
        account.insert("Login", QJsonValue(QString::fromStdString(it->account.login)));
        account.insert("Password", QJsonValue(QString::fromStdString(it->account.password)));

        accountsObject.push_back(account);
    }

    recordObject.insert("Accounts", accountsObject);

    QJsonDocument doc{ recordObject };

    QFile jsonFile(QString::fromStdString(path));
    jsonFile.open(QFile::WriteOnly);
    jsonFile.write(doc.toJson());
}

void Model::load(const std::string &path)
{
    QFile jsonFile{ QString::fromStdString(path) };
    jsonFile.open(QFile::ReadOnly);

    QString value{ jsonFile.readAll() };
    jsonFile.close();

    QJsonDocument doc{QJsonDocument::fromJson( value.toUtf8() )};
    QJsonObject recordObject{ doc.object() };

    QJsonValue nextIdValue{ recordObject.value("Next ID") };
    nextId = nextIdValue.toString().toULongLong();

    QJsonArray accounts{ recordObject.value(QString("Accounts")).toArray() };
    for(auto i{0}; i < accounts.size(); i++){
        QJsonObject account{ accounts[i].toObject() };

        size_t id{ account.value("ID").toString().toULongLong() };
        std::string name{ account.value("Site Name").toString().toStdString() };
        std::string login{ account.value("Login").toString().toStdString() };
        std::string password{ account.value("Password").toString().toStdString() };

        addAccount(InternalAccount{ Account{ name, login, password }, id });
    }

}

void Model::removeAccount(size_t id)
{
    accounts.erase(std::remove_if(accounts.begin(), accounts.end(), [id](std::unique_ptr<InternalAccount> & internalAccount){
        return (internalAccount.get()->id == id);
    }), accounts.end());
}

Model::iterator Model::begin()
{
    return iterator(std::begin(accounts));
}

Model::iterator Model::end()
{
     return iterator(std::end(accounts));
}

Model::const_iterator Model::cbegin() const
{
    return const_iterator(std::begin(accounts));
}

Model::const_iterator Model::cend() const
{
    return const_iterator(std::end(accounts));
}

void Model::addAccount(const Model::InternalAccount &account)
{
    accounts.push_back(std::make_unique<InternalAccount>(account));
}

Model::iterator::iterator(std::vector<std::unique_ptr<InternalAccount>>::iterator it) :
    it(it)
{
}

Model::iterator &Model::iterator::operator++()
{
    it++;
    return *this;
}

Model::iterator Model::iterator::operator++(int)
{
    iterator i{ it };
    it++;

    return i;
}

bool Model::iterator::operator==(Model::iterator const& other) const
{
    return (it == other.it);
}

bool Model::iterator::operator!=(Model::iterator const& other) const
{
    return (it != other.it);
}

Model::iterator::reference Model::iterator::operator*()
{
    return *it->get();
}

Model::iterator::pointer Model::iterator::operator->()
{
    return it->get();
}


Model::const_iterator::const_iterator(std::vector<std::unique_ptr<InternalAccount>>::const_iterator it):
    it(it)
{
}

Model::const_iterator &Model::const_iterator::operator++()
{
    it++;
    return *this;
}

Model::const_iterator Model::const_iterator::operator++(int)
{
    const_iterator i{ it };
    it++;

    return i;
}

bool Model::const_iterator::operator==(const Model::const_iterator &other) const
{
    return (it == other.it);
}

bool Model::const_iterator::operator!=(const Model::const_iterator &other) const
{
    return (it != other.it);
}

const Model::const_iterator::reference Model::const_iterator::operator*()
{
     return *it->get();
}

const Model::const_iterator::pointer Model::const_iterator::operator->()
{
    return it->get();
}

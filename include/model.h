#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>
#include <memory>
#include "account.h"

class Model
{
    struct InternalAccount
    {
        InternalAccount(Account const& acc, size_t id):
            account{ acc },
            id{ id }
        {
        }

        Account account;
        const size_t id;
    };

public:
    class iterator{
    public:
        using difference_type = InternalAccount;
        using value_type = InternalAccount;
        using pointer = InternalAccount*;
        using reference = InternalAccount&;
        using iterator_category = std::forward_iterator_tag;

        iterator(std::vector<std::unique_ptr<InternalAccount>>::iterator it);
        iterator& operator++();
        iterator operator++(int);
        bool operator==(iterator const& other) const;
        bool operator!=(iterator const& other) const;

        reference operator*();
        pointer operator->();

    private:
         std::vector<std::unique_ptr<InternalAccount>>::iterator it;
    };

    class const_iterator{
    public:
        using difference_type = InternalAccount;
        using value_type = const InternalAccount;
        using pointer = InternalAccount*;
        using reference = InternalAccount&;
        using iterator_category = std::forward_iterator_tag;

        const_iterator(std::vector<std::unique_ptr<InternalAccount>>::const_iterator it);
        const_iterator& operator++();
        const_iterator operator++(int);
        bool operator==(const_iterator const& other) const;
        bool operator!=(const_iterator const& other) const;

        const reference operator*();
        const pointer operator->();

    private:
         std::vector<std::unique_ptr<InternalAccount>>::const_iterator it;
    };


    Model();

    size_t addAccount(std::string const& siteName, std::string const& login, std::string const& password);
    void removeAccount(size_t id);

    void save(std::string const& path);
    void load(std::string const& path);

    iterator begin();
    iterator end();

    const_iterator cbegin() const;
    const_iterator cend() const;


private:
    void addAccount(InternalAccount const& account);

    std::vector<std::unique_ptr<InternalAccount>> accounts;

    size_t nextId;
};

#endif // MODEL_H

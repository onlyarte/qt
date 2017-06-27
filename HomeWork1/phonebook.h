#ifndef PHONEBOOK_H
#define PHONEBOOK_H

#include <QHash>
#include <QList>
#include <QString>
#include <iostream>

using namespace std;

class PhoneBook
{
private:
    QHash<QString, QList<QString>> c;
    bool isValidNumber(QString number);

public:
    explicit PhoneBook();
    void show();
    void addContact();
    void removeContact();
    void findByName();
    void findByNumber();

};

#endif // PHONEBOOK_H

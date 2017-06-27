#include "phonebook.h"

PhoneBook::PhoneBook()
{
    cout << "Phone Book created!" << endl;
}

bool PhoneBook::isValidNumber(QString number){
    QRegExp rx("[0-9]{3,15}");
    if(rx.indexIn(number) == -1)
        return false;
    return true;
}

void PhoneBook::addContact(){
    cout << endl << "===ADD NUMBER===" << endl;
    string tempName;
    cout << "Name:" << endl; cin >> tempName;
    QString name = QString::fromUtf8(tempName.c_str());

    string tempNumber = "";
    while (tempNumber != "exit"){
        cout << "Phone number or 'exit': " << endl;
        cin >> tempNumber;
        QString number = QString::fromUtf8(tempNumber.c_str());
        if(this->isValidNumber(number)){
            if(!c[name].contains(number))
                c[name] << number;
            else
                cout << "The number has already been added" << endl;
        } else if(number != "exit") {
            cout << "It seems not to be a phone number" << endl;
        }
    }
    cout << endl;
    show();
}

void PhoneBook::removeContact(){
    cout << endl << "===REMOVE NUMBER===" << endl;
    string tempName;
    cout << "Name:" << endl; cin >> tempName;
    QString name = QString::fromUtf8(tempName.c_str());
    if(c.contains(name)){
        c.remove(name);
        cout << endl << "Removed" << endl;
    } else{
        cout << "There is no such contact" << endl;
    }
    system("pause");
    cout << endl;
    show();
}

void PhoneBook::show(){
    cout << endl << "===PHONE BOOK===" << endl;

    QHashIterator<QString, QList<QString>> i(c);
    while (i.hasNext()) {
        i.next();
        cout << i.key().toStdString() << endl;

        QListIterator<QString> j(i.value());
        while (j.hasNext())
            cout << j.next().toStdString() << endl;
        cout << endl;
    }
    cout << "Type"<< endl << "1 - to add" << endl << "2 - to remove" << endl
         << "3 - to search by name" << endl << "4 - to search by number" << endl << ":";
    int next;
    cin >> next;
    switch(next){
    case 1:
        addContact();
        break;
    case 2:
        removeContact();
        break;
    case 3:
        findByName();
        break;
    case 4:
        findByNumber();
        break;
    default:
        cout << "There is no such action" << endl;
        show();
    }
}

void PhoneBook::findByName(){
    cout << endl << "===SEARCH BY NAME===" << endl;
    string tempName;
    cout << "Name:" << endl; cin >> tempName;
    QString name = QString::fromUtf8(tempName.c_str());

    if(c.contains(name)){
        cout << endl << name.toStdString() << endl;
        QListIterator<QString> i(c[name]);
        while (i.hasNext())
            cout << i.next().toStdString() << endl;
    } else{
        cout << "Sorry. Not found!";
    }
    system("pause");
    show();
}

void PhoneBook::findByNumber(){
    cout << endl << "===SEARCH BY NUMBER===" << endl;
    bool found = false;
    string tempNumber;
    cout << "Number:" << endl; cin >> tempNumber;
    QString number = QString::fromUtf8(tempNumber.c_str());

    if(isValidNumber(number)){
        QHashIterator<QString, QList<QString>> i(c);
        while (i.hasNext()) {
            i.next();

            QListIterator<QString> j(i.value());
            while (j.hasNext()){
                QString temp(j.next());
                if(temp == number){
                    cout << i.key().toStdString() << endl << temp.toStdString() << endl;
                    found = true;
                }
            }
        }
        if(!found)
            cout << "Sorry. Not found" << endl;
    } else {
        cout << "It seems not to be a phone number" << endl;
    }
    system("pause");
    show();
}

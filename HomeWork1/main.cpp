#include <QCoreApplication>
#include <iostream>
#include "phonebook.cpp"

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    PhoneBook pb;
    pb.show();

    return a.exec();
}

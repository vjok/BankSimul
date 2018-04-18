#ifndef DLLMYSQLDLL_H
#define DLLMYSQLDLL_H
#include <QDebug>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

#include "dllmysqldll_global.h"
#include <mysqlengine.h>

class DLLMYSQLDLLSHARED_EXPORT DLLMySQLDLL
{

public:
    DLLMySQLDLL();

    bool interfaceFunctionStartConnection();
    void accountEvent();
    bool interfaceFunctionLogIn(QString pinCode, int cardIdentification, int loginTry);
    void interfaceFunctionLogOut();
    void interfaceFunctionShowBalance();
    void interfaceFunctionCashWithdrawal(double maara);
    void customerInf();
    void lockCard();
    void interfaceFunctionShowEvents();

    struct Customer
    {
        QString firstname;
        QString lastname;
        int customerID;
    } customerData;

    struct Card
    {
        int id;
        int password;
        int cardnumber;
    } cardData;

    struct Account
    {
        int id;
        double balance;
    } accountData;

    struct accountEvents
    {
        QString recipient;
        QString definition;
        double amount;
        QString datetime;
    } events;

private:
    MySQLEngine *objectMySQLEngine;
    QString nosto;
    int loginTry;
    int count;
    int interval;
};

#endif // DLLMYSQLDLL_H

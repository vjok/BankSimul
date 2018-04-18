#ifndef MYSQLENGINE_H
#define MYSQLENGINE_H
#include <QObject>
#include <QDebug>
#include <QtSql/QtSql>
#include <QDateTime>

class MySQLEngine : public QObject
{
    Q_OBJECT

public:
    MySQLEngine();
    ~MySQLEngine();
    bool StartConnection();
    void accountEvent();
    bool logIn(QString pinCode, int cardIdentification, int loginTry);
    void logOut();
    void showBalance();
    void cashWithdrawal(double maara);
    void customerInf();
    void lockCard();
    void showEvents();
    QString nosto;
    int loginTry;
    int count;
    int interval;

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

    MySQLEngine *objectDLLMySQL;

};

#endif // MYSQLENGINE_H

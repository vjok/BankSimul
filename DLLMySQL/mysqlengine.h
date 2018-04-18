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
    bool StartConnection();
    void accountEvent();
    bool logIn(QString pinCode, int loginTry);
    void cardIdentification(int cardID);
    void logOut();
    void showBalance();
    void cashWithdrawal(double maara);
    void customerInf();
    void lockCard();
    void showEvents();

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
    QString nosto;
    int loginTry;
    int count;
    int interval;
    MySQLEngine *objectDLLMySQL;
};

#endif // MYSQLENGINE_H

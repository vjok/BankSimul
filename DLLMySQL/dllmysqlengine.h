#ifndef DLLMYSQLENGINE_H
#define DLLMYSQLENGINE_H
#include <QObject>
#include <QDebug>
#include <QtSql/QtSql>
#include <QDateTime>

class DLLMySQLEngine : public QObject
{
    Q_OBJECT

public:
    DLLMySQLEngine();
    ~DLLMySQLEngine();
    bool StartConnection();
    void accountEvent();
    bool logIn(QString pinCode);
    bool cardIdentification(QString cardID);
    bool isLocked();
    void logOut();
    QString showBalance();
    QString getAllAccountEvents();
    QString getFiveAccountEvents();
    void cashWithdrawal(double amount);
    void customerInf();
    void lockCard();
    void showEvents();

signals:
    void changePage();

private:
    DLLMySQLEngine *objectDLLMySQL;
    QSqlDatabase db;
    QString nosto;
    int count;
    int interval;
    bool CardExist;
    double newAmount;
    int value;

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
        int lockState;
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


};

#endif // DLLMYSQLENGINE_H

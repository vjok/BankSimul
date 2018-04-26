#ifndef DLLMYSQL_H
#define DLLMYSQL_H
#include "dllmysql_global.h"
#include <dllmysqlengine.h>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <QObject>

class DLLMYSQLSHARED_EXPORT DLLMySQL : public QObject
{
    Q_OBJECT

public:
    DLLMySQL();
    ~DLLMySQL();
    bool interfaceFunctionStartConnection();
    void accountEvent();
    bool interfaceFunctionLogIn(QString pinCode);
    bool interfaceFunctionCardIdentification(QString cardID);
    bool interfaceFunctionIsLocked();
    void interfaceFunctionLogOut();
    void interfaceFunctionLockCard();
    QString interfaceFunctionShowBalance();
    QString interfaceFunctionGetAccountEvent();
    void interfaceFunctionCashWithdrawal(double amount);
    void interfaceFunctionCashWithdrawalSkipAd(double amount);
    void customerInf();
    void lockCard();
    void interfaceFunctionShowEvents();

private slots:
    void receivePage();

signals:
    void sendPage();

private:
    DLLMySQLEngine *objectDLLMySQLEngine;
    QString nosto;
    int count;
    int interval;
};

#endif // DLLMYSQL_H

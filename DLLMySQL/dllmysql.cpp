#include "dllmysql.h"

DLLMySQL::DLLMySQL()
{
    objectDLLMySQLEngine = new DLLMySQLEngine;
    QObject::connect(objectDLLMySQLEngine, &DLLMySQLEngine::changePage, this, &DLLMySQL::receivePage);
}

DLLMySQL::~DLLMySQL()
{
    delete objectDLLMySQLEngine;
    objectDLLMySQLEngine = NULL;
}

bool DLLMySQL::interfaceFunctionStartConnection()
{
    objectDLLMySQLEngine->StartConnection();
    return true;
}

bool DLLMySQL::interfaceFunctionCardIdentification(QString cardID)
{
    return objectDLLMySQLEngine->cardIdentification(cardID);
}

bool DLLMySQL::interfaceFunctionIsLocked()
{
    return objectDLLMySQLEngine->isLocked();
}

bool DLLMySQL::interfaceFunctionLogIn(QString pinCode)
{
    bool login = objectDLLMySQLEngine->logIn(pinCode);
    return login;
}

void DLLMySQL::interfaceFunctionLockCard()
{
    objectDLLMySQLEngine->lockCard();
}

QString DLLMySQL::interfaceFunctionShowBalance()
{
    return objectDLLMySQLEngine->showBalance();
}

QString DLLMySQL::interfaceFunctionGetAllAccountEvents()
{
    return objectDLLMySQLEngine->getAllAccountEvents();
}

QString DLLMySQL::interfaceFunctionGetFiveAccountEvents()
{
    return objectDLLMySQLEngine->getFiveAccountEvents();
}

void DLLMySQL::interfaceFunctionCashWithdrawal(double amount)
{
    objectDLLMySQLEngine->cashWithdrawal(amount);
}

void DLLMySQL::interfaceFunctionShowEvents()
{
    objectDLLMySQLEngine->showEvents();
}

void DLLMySQL::receivePage()
{
    emit sendPage();
}

void DLLMySQL::interfaceFunctionLogOut()
{
    objectDLLMySQLEngine->logOut();
}

#include "dllmysqldll.h"

DLLMySQLDLL::DLLMySQLDLL()
{
    objectMySQLEngine = new MySQLEngine;
}

bool DLLMySQLDLL::interfaceFunctionStartConnection()
{
    objectMySQLEngine->StartConnection();
    return true;
}

bool DLLMySQLDLL::interfaceFunctionLogIn(QString pinCode, int cardIdentification, int loginTry)
{
    bool login = objectMySQLEngine->logIn(pinCode, cardIdentification, loginTry);
    return login;
}

void DLLMySQLDLL::interfaceFunctionShowBalance()
{
    objectMySQLEngine->showBalance();
}

void DLLMySQLDLL::interfaceFunctionCashWithdrawal(double maara)
{
    objectMySQLEngine->cashWithdrawal(maara);
}

void DLLMySQLDLL::interfaceFunctionShowEvents()
{
    objectMySQLEngine->showEvents();
}

void DLLMySQLDLL::interfaceFunctionLogOut()
{
    objectMySQLEngine->logOut();
}

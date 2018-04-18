#include "dllmysqldll.h"

DLLMySQLDLL::DLLMySQLDLL()
{
    objectMySQLEngine = new MySQLEngine;
}

DLLMySQLDLL::~DLLMySQLDLL()
{
    delete objectMySQLEngine;
    objectMySQLEngine = NULL;
}

void DLLMySQLDLL::interfaceFunction(QString pinCode, int cardIdentification, int loginTry, double maara)
{
    objectMySQLEngine->StartConnection();
    objectMySQLEngine->logIn(pinCode, cardIdentification, loginTry);
    objectMySQLEngine->showBalance();
    objectMySQLEngine->cashWithdrawal(maara);
    objectMySQLEngine->showEvents();
    objectMySQLEngine->logOut();
}

#include "dllmysqldll.h"


void DLLMySQLDLL::interfaceFunction(QString pinCode, int cardIdentification, int loginTry, double maara)
{
    objectMySQLEngine->StartConnection();
    objectMySQLEngine->logIn(pinCode, cardIdentification, loginTry);
    objectMySQLEngine->showBalance();
    objectMySQLEngine->cashWithdrawal(maara);
    objectMySQLEngine->showEvents();
    objectMySQLEngine->logOut();
}

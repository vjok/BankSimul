#ifndef DLLMYSQLDLL_H
#define DLLMYSQLDLL_H
#include <QDebug>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include "dllmysqldll_global.h"
#include <mysqlengine.h>

class DLLMYSQLDLLSHARED_EXPORT DLLMySQLDLL : public QObject
{

public:
    DLLMySQLDLL();
    ~DLLMySQLDLL();
    void interfaceFunction(QString pinCode, int cardIdentification, int loginTry, double maara);

private:
    MySQLEngine *objectMySQLEngine;
};

#endif // DLLMYSQLDLL_H

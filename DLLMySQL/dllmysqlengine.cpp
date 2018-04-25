#include "dllmysqlengine.h"
#include <QDebug>

DLLMySQLEngine::DLLMySQLEngine()
{
}

DLLMySQLEngine::~DLLMySQLEngine()
{
    delete objectDLLMySQL;
    objectDLLMySQL = NULL;
}

bool DLLMySQLEngine::StartConnection()
{
    db = QSqlDatabase::addDatabase("QMYSQL", "bankDB");
    db.setHostName("mysli.oamk.fi");
    db.setDatabaseName("opisk_t7kavi01");
    db.setUserName("t7kavi01");
    db.setPassword("WqcGWZj897hFUSjP");
    db.open();
        if (!db.open())
        {
            qDebug() << "Yhteys ei toimi";
            return false;
        }
    return true;
}

bool DLLMySQLEngine::cardIdentification(QString cardID)
{
    QSqlQuery query(db);
    query.prepare("SELECT idKortti, idTili  FROM Kortti WHERE korttitunniste = ?");
    // cardID = RFID:llä luettu kortintunniste
    query.addBindValue(cardID);
    query.exec();

    while (query.next())
    {
        this->cardData.id = query.value(0).toInt();
        this->accountData.id = query.value(1).toInt();
    }

    if(query.size() > 0)
    {
        return true;
    }
    else
    {
        return false;
    }

}

bool DLLMySQLEngine::isLocked()
{
    QSqlQuery query(db);
    query.prepare("SELECT lukitus FROM Kortti WHERE idKortti = ?");
    query.addBindValue(this->cardData.id);
    query.exec();
    while (query.next())
    {
        this->cardData.lockState = query.value(0).toInt();
    }
    if (cardData.lockState == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool DLLMySQLEngine::logIn(QString pinCode)
{
    // pinCode = syötetty pin-koodi
    QSqlQuery query(db);
    query.prepare("SELECT salasana FROM Kortti WHERE idKortti = ?");
    query.addBindValue(this->cardData.id);
    query.exec();

    while (query.next())
    {
        this->cardData.password = query.value(0).toInt();
    }
    //tehdään salasanasta QString, jota voidaan verrata syötetyn kanssa
    QString passString = QString::number(cardData.password);

    if (pinCode != passString)
    {
        return false;
    }

        QSqlQuery accountQuery(db);
        accountQuery.prepare("SELECT idAsiakas FROM Tili WHERE idTili = ?");
        accountQuery.addBindValue(this->accountData.id);
        accountQuery.exec();

        while (accountQuery.next())
        {
            this->customerData.customerID = accountQuery.value(0).toInt();
        }


        return true;
}

void DLLMySQLEngine::lockCard()
{
    QSqlQuery query(db);
    query.prepare("UPDATE Kortti SET lukitus = 1 WHERE idKortti = ?");
    query.addBindValue(this->cardData.id);
    query.exec();
}

void DLLMySQLEngine::customerInf()
// OK
{
    QSqlQuery query(db);
    query.prepare("SELECT * from Asiakas WHERE idAsiakas = ?");
    query.addBindValue(this->customerData.customerID);
    query.exec();

    while(query.next())
    {
        this->customerData.firstname = query.value(1).toString();
        this->customerData.lastname = query.value(2).toString();
    }

}

QString DLLMySQLEngine::getAccountEvent()
{
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Tilitapahtumat WHERE idTili = ?");
    query.addBindValue(this->accountData.id);
    query.exec();
    query.last();
    QString eventString;
    for (int i = 0; i < 10; i++)
    {
        this->events.recipient = query.value(2).toString();
        this->events.definition = query.value(3).toString();
        this->events.amount = query.value(4).toDouble();
        this->events.datetime = query.value(5).toString();
        //qDebug() << events.recipient << endl << events.definition << endl << events.amount << endl << events.datetime;
        eventString.append(events.recipient + "|" + events.definition + "|" + QString::number(events.amount) + "|" +  events.datetime + "|");
        query.previous();
    }
    return eventString;
}



void DLLMySQLEngine::accountEvent()
//aikalailla OK
{
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Tilitapahtumat WHERE idTili = ? ORDER BY idTapahtuma DESC LIMIT ? OFFSET ?");
    query.addBindValue(this->accountData.id);
    query.addBindValue(count);
    query.addBindValue(interval);
    query.exec();

    while (query.next())
    {
        this->events.recipient = query.value(2).toString();
        this->events.definition = query.value(3).toString();
        this->events.amount = query.value(4).toDouble();
        this->events.datetime = query.value(5).toString();

        qDebug() << events.recipient << endl << events.definition << endl << events.amount << endl << events.datetime;
    }
}

void DLLMySQLEngine::showEvents()
//korjausta
{
    count = 10, interval = 0;
    this->accountEvent();
    // 'seuraavat 10'-nappia painettu
    interval = 10;
    this->accountEvent();
    // taas 'seuraavat 10'-nappia painettu
    interval = 20;
    this->accountEvent();
}


QString DLLMySQLEngine::showBalance()
// OK
{
    //'näytä saldo'-nappia painettu
    this->customerInf();
    QSqlQuery query(db);
    query.prepare("SELECT saldo FROM Tili WHERE idTili = ?");
    query.addBindValue(this->accountData.id);
    query.exec();
    while (query.next())
    {
        this->accountData.balance = query.value(0).toDouble();
    }

    //count = 5;
    QString returnValue = customerData.firstname + "|" + customerData.lastname + "|" + QString::number(accountData.balance);
    return returnValue;

}

void DLLMySQLEngine::cashWithdrawal(double amount)
// vaatii vielä korjausta
{
    newAmount = 0;
    this->customerInf();

    QSqlQuery query(db);
    QSqlQuery updatedAmount(db);

    query.prepare("SELECT saldo FROM Tili WHERE idTili = ?");
    query.addBindValue(this->accountData.id);
    query.exec();
    while (query.next())
    {
        this->accountData.balance = query.value(0).toDouble();
    }
    if (this->accountData.balance < amount)
    {
        qDebug() << "Tilillä ei ole riittävästi rahaa";
        emit changePage();
    }

    else
    {
    // jos mainos katsotaan
    newAmount = this->accountData.balance - amount;
    updatedAmount.prepare("UPDATE Tili SET saldo = ? WHERE idTili = ?");
    updatedAmount.addBindValue(newAmount);
    updatedAmount.addBindValue(this->accountData.id);
    updatedAmount.exec();

    query.prepare("INSERT INTO Tilitapahtumat (idTili, selite, maara) VALUES(?, 'NOSTO', -?)");
    query.addBindValue(this->accountData.id);
    query.addBindValue(amount);
    query.exec();

    //jos mainos skipataan
    /*
    paySkip = maara * 0,1;
    amountAfterSkip = newAmount - paySkip;
    query.prepare("UPDATE Tili SET saldo = ? WHERE idTili = ?");
    query.addBindValue(amountAfterSkip);
    query.addBindValue(this->accountData.id);
    query.exec();

    query.prepare("INSERT INTO Tilitapahtumat (idTili, saaja, selite, maara) VALUES(?, BANKSIMUL, MAINOSMAKSU, ?)");
    query.addBindValue(this->accountData.id);
    query.addBindValue(paySkip);
    query.exec();
    }
*/
    }
}

void DLLMySQLEngine::logOut()
{
    db.close();
    db = QSqlDatabase();
    QSqlDatabase::removeDatabase("bankDB");
    qDebug() << "Yhteys suljettu";
}

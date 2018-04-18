#include "mysqlengine.h"

MySQLEngine::MySQLEngine()
{
    objectDLLMySQL = new MySQLEngine;
}

MySQLEngine::~MySQLEngine()
{

}

bool MySQLEngine::StartConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
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


bool MySQLEngine::logIn(QString pinCode, int cardIdentification, int loginTry)
// vielä pientä viilausta vailla
{
    // pinCode = syötetty pin-koodi
    QSqlQuery query;
    query.prepare("SELECT idKortti, idTili, salasana FROM Kortti WHERE korttitunniste = ?");
    // cardIdentification = RFID:llä luettu kortintunniste
    query.addBindValue(cardIdentification);
    query.exec();

    while (query.next())
    {
        this->cardData.id = query.value(0).toInt();
        this->accountData.id = query.value(1).toInt();
        this->cardData.password = query.value(2).toInt();
    }

    if (pinCode != this->cardData.password)
    {
        return false;
        loginTry ++;
        if (loginTry == 3)
        {
            this->lockCard();
        }
    }

    QSqlQuery accountQuery;
    accountQuery.prepare("SELECT idAsiakas FROM Tili WHERE idTili = ?");
    accountQuery.addBindValue(this->accountData.id);
    accountQuery.exec();

    while (query.next())
    {
        this->customerData.customerID = accountQuery.value(0).toInt();
    }

    loginTry = 0;
    return true;
}


void MySQLEngine::lockCard()
// OK
{
    QSqlQuery query;
    query.prepare("UPDATE Kortti SET lukitus = 1 WHERE idKortti = 1");
    //query.addBindValue(this->cardData.id);
    query.exec();
}


void MySQLEngine::customerInf()
// OK
{
    QSqlQuery query;
    query.prepare("SELECT etunimi, sukunimi from Asiakas WHERE idAsiakas=?");
    query.addBindValue(this->customerData.customerID);
    query.exec();

    while(query.next())
    {
        this->customerData.firstname = query.value(0).toString();
        this->customerData.lastname = query.value(1).toString();
    }
}


void MySQLEngine::accountEvent()
//aikalailla OK
{
    QSqlQuery query;
    query.prepare("SELECT * FROM Tilitapahtumat WHERE idTili = 1 ORDER BY idTapahtuma DESC LIMIT ? OFFSET ?");
    //query.addBindValue(this->accountData.id);
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

void MySQLEngine::showEvents()
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


void MySQLEngine::showBalance()
// OK
{
    //'näytä saldo'-nappia painettu

    this->customerInf();

    QSqlQuery query;
    query.prepare("SELECT saldo FROM Tili WHERE idTili = ?");
    query.addBindValue(this->accountData.id);
    query.exec();
    while (query.next())
    {
        this->accountData.balance = query.value(0).toDouble();
    }

    count = 5;
    this->accountEvent();

}


void MySQLEngine::cashWithdrawal(double maara)
// vaatii vielä korjausta
{
    // maara = annettu summa

    QSqlQuery query;
    QSqlQuery updatedAmount;
    QSqlQuery event;

    query.prepare("SELECT saldo FROM Tili WHERE idTili = 4");
    //query.addBindValue(this->accountData.id);
    query.exec();
    while (query.next())
    {
        this->accountData.balance = query.value(0).toDouble();
    }


    if (this->accountData.balance < maara)
    {
        qDebug() << "Tilillä ei ole riittävästi rahaa";
    }

    // jos mainos skipataan
    updatedAmount.prepare("UPDATE Tili SET saldo = ? WHERE idTili = 4");
    updatedAmount.addBindValue(maara);
    //query.addBindValue(this->accountData.id);
    updatedAmount.exec();
    event.prepare("INSERT INTO Tilitapahtumat (idTili, saaja, selite, maara) VALUES(4, BANKSIMUL, MAINOSMAKSU, ?)");
    //event.addBindValue(this->accountData.id);
    event.addBindValue(maara);
    event.exec();

    //jos mainos katsotaan

/*
    query.prepare("UPDATE Tili SET saldo = ? WHERE idTili = ?");
    query.addBindValue(maara);
    query.addBindValue(this->accountData.id);
    query.exec();

    query.prepare("INSERT INTO Tilitapahtumat (idTili, selite, maara) VALUES(?, NOSTO, ?)");
    query.addBindValue(this->accountData.id);
    query.addBindValue(maara);
    query.exec();
*/

}

void MySQLEngine::logOut()
{
    QSqlDatabase db;
    db.close();
    qDebug() << "Yhteys suljettu";
}

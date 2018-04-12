#ifndef DLLSERIALPORT_H
#define DLLSERIALPORT_H

#include <QObject>

#include "dllserialport_global.h"
#include "dllserialportengine.h"

class DLLSERIALPORTSHARED_EXPORT DLLSerialPort : public QObject
{
    Q_OBJECT
public:
    DLLSerialPort();
    ~DLLSerialPort();
    void interfaceOpenConnection();
    void interfaceCloseConnection();

private slots:
    void receiveValue(QString);
signals:
    void returnValue(QString);

private:
    DLLSerialPortEngine *objectDLLSerialPortEngine;
};

#endif // DLLSERIALPORT_H

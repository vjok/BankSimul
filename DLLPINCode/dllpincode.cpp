#include "dllpincode.h"

void DLLPINCode::interfaceFunctionControlEngine()
{
    objectDialog = new Dialog;
    objectDialog->showFullScreen();
    objectDialog->exec();
}

QString DLLPINCode::interfaceFunctionReturnPIN()
{
    PinToReturn = objectDialog->returnValue();
    return PinToReturn;
}

#include "dllpincode.h"


void DLLPINCode::interfaceFunctionControlEngine()
{
    objectDialog = new Dialog;
    objectDialog->exec();
}


QString DLLPINCode::interfaceFunctionReturnPIN()
{
    PinToReturn = objectDialog->returnValue();
    return PinToReturn;
}

#include "banksimul.h"
#include "ui_mainwindow.h"

BankSimul::BankSimul(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) // constructor
{
    ui->setupUi(this); // create instances of widgets
    ui->stackedWidget->setCurrentIndex(0);  // set default page to page-1 (mainmenu)
    timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));
    timer->stop();  // timer is stopped when in default page
    objectDLLSerialPort = new DLLSerialPort;    //create objects
    objectDLLPINCode = new DLLPINCode;
    objectDLLMySQL = new DLLMySQL;
    QObject::connect(objectDLLSerialPort, &DLLSerialPort::returnValue, this, &BankSimul::checkId);  // send read card-id to checkId function
    QObject::connect(objectDLLPINCode, &DLLPINCode::returnPIN, this, &BankSimul::checkPIN); // send pin-code that user inputs to checkPIN function
    QObject::connect(objectDLLMySQL, &DLLMySQL::sendPage, this, &BankSimul::vaihdaSivu);
    objectDLLSerialPort->interfaceFunctionOpenConnection(); // open serial-port connection for RFID-card reader
    attempts = 0;   // Login attempts
    loggedIn = false;   // logged in state
}

BankSimul::~BankSimul() // Destructor
{
    delete ui;
    delete timer;
    delete objectDLLMySQL;
    delete objectDLLPINCode;
    delete objectDLLSerialPort;
    ui = NULL;
    timer = NULL;
    objectDLLMySQL = NULL;
    objectDLLPINCode = NULL;
    objectDLLSerialPort = NULL;
}

void BankSimul::checkId(QString CardId) // RFID-card check function when card-input
{
    if (loggedIn == false)  // if user is not logged in, start db-connection
    {
        objectDLLMySQL->interfaceFunctionStartConnection();
        if (objectDLLMySQL->interfaceFunctionCardIdentification(CardId)) // Check if card exists
        {
            if (objectDLLMySQL->interfaceFunctionIsLocked())    // If card is locked, display 10 second error on page 2
            {
                ui->stackedWidget->setCurrentIndex(1);
                page = 2;
                Timer10();
            }
            else
            {
                objectDLLPINCode->interfaceFunctionControlEngine();     // If card is not locked, open pin-code dialog
            }
        }
    }
}

void BankSimul::checkPIN(QString checkedPIN)
{
    objectDLLPINCode->interfaceFunctionSetLabel("Syötä Pin-koodi"); // set text "Syötä Pin-koodi" in case it's "Väärä tunnusluku!"
    bool result = objectDLLMySQL->interfaceFunctionLogIn(checkedPIN);   // Database returns true or false
    if(result)  // if pin-code is correct, close pin-code dialog -> open main atm interface -> set Logged in state as true
    {
        ui->stackedWidget->setCurrentIndex(2);
        objectDLLPINCode->interfaceFunctionCloseDialog();
        Timer30();
        page = 3;
        attempts = 0;
        loggedIn = true;
    }
    else    // if user inputs pin-code wrong, add one attempt, set error text to the label
    {
        attempts++;
        objectDLLPINCode->interfaceFunctionSetLabel("Tunnusluku väärin!\nYritä uudelleen!");
    }
    if(attempts == 3)   // if user has used all 3 attempts inputting the pin-code:
    {
        objectDLLMySQL->interfaceFunctionLockCard();        // Lock card
        objectDLLPINCode->interfaceFunctionCloseDialog();   // Close pin-code dialog
        ui->stackedWidget->setCurrentIndex(1);              // Display error page
        page = 2;   // Set page as page-2
        Timer10();  // start 10 second timer

        //loggedIn = false;    //necessary?
    }
}

void BankSimul::updateTime()    // updateTime function
{
    time--;
    ui->lcdNumber->display(time);
    timer->setInterval(1000);
    timer->start();
    if(time == 0)   // when time is null:
    {
        if(page == 3 || page == 8 || page == 5) // if user is on page 3, 8 or 5
        {
            timer->stop();      // stop the timer, login state false, go to default page, close all database connections
            loggedIn = false;
            ui->stackedWidget->setCurrentIndex(0);
            objectDLLMySQL->interfaceFunctionLogOut();
        }
        else if(page < 8 && page > 3)   // user can view withdrawal, activity or balance -pages for 10 seconds
        {
            timer->stop();
            ui->stackedWidget->setCurrentIndex(2);
            Timer30();
            page = 3;
        }
        else if(page == 2)  // if user has locked the card, stop timer, go to default page, set login state false
        {
            timer->stop();
            ui->stackedWidget->setCurrentIndex(0);
            loggedIn = false;   //necessary?
        }

        else if(page == 9)
        {
            timer->stop();
            ui->stackedWidget->setCurrentIndex(3);
            Timer10();
            page = 4;
        }
    }
}

void BankSimul::Timer10()   // 10 second timer
{
    timer->stop();
    time = 11;
    timer->setInterval(1000);
    timer->start();
    updateTime();
}

void BankSimul::Timer30()   // 30 second timer
{
    timer->stop();
    time = 16;
    timer->setInterval(1000);
    timer->start();
    updateTime();
}

// when each button is pressed, the configured page is set and timer is set to start

void BankSimul::on_NostaRahaa_clicked()
{
    page = 4;
    ui->stackedWidget->setCurrentIndex(3);
    Timer10();
    QString returnString = objectDLLMySQL->interfaceFunctionShowBalance();
    QStringList balanceList = returnString.split('|');
    QFont font = ui->labelNostoSaldo->font();
    font.setPointSize(40);
    ui->labelNostoSaldo->setAlignment(Qt::AlignCenter);
    ui->labelNostoSaldo->setFont(font);
    ui->labelNostoSaldo->setText(balanceList[0] + " " + balanceList[1] + "\nSaldo: " + balanceList[2] + "€");
}

void BankSimul::on_NaytaSaldo_clicked()
{
    page = 7;
    ui->stackedWidget->setCurrentIndex(6);
    Timer10();
    QString returnString = objectDLLMySQL->interfaceFunctionShowBalance();
    QStringList balanceList = returnString.split('|');
    QString eventString = objectDLLMySQL->interfaceFunctionGetAccountEvent();
    QStringList eventList = eventString.split('|');
    QFont font = ui->labelSaldo->font();
    font.setPointSize(40);
    ui->labelSaldo->setAlignment(Qt::AlignCenter);
    ui->labelSaldo->setFont(font);
    ui->labelSaldo->setText(balanceList[0] + " " + balanceList[1] + "\nSaldo: " + balanceList[2] + "€");
    font.setPointSize(24);
    ui->labelTapahtuma->setFont(font);
    ui->labelTapahtuma->setText("1. " + eventList[0] + " " + eventList[1] + " " + eventList[2] + "€ " + eventList[3]
                                + "\n2. " + eventList[4] + " " + eventList[5] + " " + eventList[6] + "€ " + eventList[7]
                                + "\n3. " + eventList[8] + " " + eventList[9] + " " + eventList[10] + "€ " + eventList[11]
                                + "\n4. " + eventList[12] + " " + eventList[13] + " " + eventList[14] + "€ " + eventList[15]
                                + "\n5. " + eventList[16] + " " + eventList[17] + " " + eventList[18] + "€ " + eventList[19]);
}

void BankSimul::on_SelaaTili_clicked()
{
    page = 6;
    ui->stackedWidget->setCurrentIndex(5);
    Timer10();
    QString returnString = objectDLLMySQL->interfaceFunctionShowBalance();
    QStringList balanceList = returnString.split('|');
    QFont font = ui->labelTiliSaldo->font();
    font.setPointSize(40);
    ui->labelTiliSaldo->setAlignment(Qt::AlignCenter);
    ui->labelTiliSaldo->setFont(font);
    ui->labelTiliSaldo->setText(balanceList[0] + " " + balanceList[1] + "\nSaldo: " + balanceList[2] + "€");

    QString eventString = objectDLLMySQL->interfaceFunctionGetAccountEvent();
    QStringList eventList = eventString.split('|');
    font.setPointSize(24);
    ui->label1->setFont(font);
    ui->label1->setText(           "1. " + eventList[0] + " " + eventList[1] + " " + eventList[2] + "€ " + eventList[3]
                                + "\n2. " + eventList[4] + " " + eventList[5] + " " + eventList[6] + "€ " + eventList[7]
                                + "\n3. " + eventList[8] + " " + eventList[9] + " " + eventList[10] + "€ " + eventList[11]
                                + "\n4. " + eventList[12] + " " + eventList[13] + " " + eventList[14] + "€ " + eventList[15]
                                + "\n5. " + eventList[16] + " " + eventList[17] + " " + eventList[18] + "€ " + eventList[19]
                                + "\n6. " + eventList[20] + " " + eventList[21] + " " + eventList[22] + "€ " + eventList[23]
                                + "\n7. " + eventList[24] + " " + eventList[25] + " " + eventList[26] + "€ " + eventList[27]
                                + "\n8. " + eventList[28] + " " + eventList[29] + " " + eventList[30] + "€ " + eventList[31]
                                + "\n9. " + eventList[32] + " " + eventList[33] + " " + eventList[34] + "€ " + eventList[35]
                                + "\n10. " + eventList[36] + " " + eventList[37] + " " + eventList[38] + "€ " + eventList[39]);

}

void BankSimul::on_Eteenpain_clicked()
{

}

void BankSimul::on_Taaksepain_clicked()
{

}


void BankSimul::on_KirjauduUlos_clicked()   // logout button clicked:
{
    ui->stackedWidget->setCurrentIndex(0);      // go to default page
    timer->stop();                              // stop the timer
    loggedIn = false;                           // set logged in state false
    objectDLLMySQL->interfaceFunctionLogOut();  // close all database connections
}

void BankSimul::on_Nosto20e_clicked()
{
    page = 5;
    ui->stackedWidget->setCurrentIndex(4);
    Timer30();
    objectDLLMySQL->interfaceFunctionCashWithdrawal(20.00);
}

void BankSimul::on_Nosto40e_clicked()
{
    page = 5;
    ui->stackedWidget->setCurrentIndex(4);
    Timer30();
    objectDLLMySQL->interfaceFunctionCashWithdrawal(40.00);

}

void BankSimul::on_Nosto60e_clicked()
{
    page = 5;
    ui->stackedWidget->setCurrentIndex(4);
    Timer30();
    objectDLLMySQL->interfaceFunctionCashWithdrawal(60.00);

}

void BankSimul::on_Nosto100e_clicked()
{
    page = 5;
    ui->stackedWidget->setCurrentIndex(4);
    Timer30();
    objectDLLMySQL->interfaceFunctionCashWithdrawal(100.00);
}

void BankSimul::on_Nosto200e_clicked()
{
    page = 5;
    ui->stackedWidget->setCurrentIndex(4);
    Timer30();
    objectDLLMySQL->interfaceFunctionCashWithdrawal(200.01);
}

void BankSimul::on_Nosto500e_clicked()
{
    page = 5;
    ui->stackedWidget->setCurrentIndex(4);
    Timer30();
    objectDLLMySQL->interfaceFunctionCashWithdrawal(500.00);
}

void BankSimul::on_Peruuta_clicked()
{
    page = 3;
    ui->stackedWidget->setCurrentIndex(2);
    Timer30();
}

void BankSimul::vaihdaSivu()
{
    page = 9;
    ui->stackedWidget->setCurrentIndex(8);
    Timer10();
}

void BankSimul::on_Jatka_clicked()
{
    page = 8;
    ui->stackedWidget->setCurrentIndex(7);
    Timer10();
}

void BankSimul::on_Sulje_clicked()
{
    page = 3;
    ui->stackedWidget->setCurrentIndex(2);
    Timer30();
}

void BankSimul::on_Sulje_2_clicked()
{
    page = 3;
    ui->stackedWidget->setCurrentIndex(2);
    Timer30();
}

void BankSimul::on_KirjauduUlos_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    timer->stop();
    loggedIn = false;
    objectDLLMySQL->interfaceFunctionLogOut();
}

// these functions will not be in the last version


void BankSimul::on_Paavalikko_clicked(){
    ui->stackedWidget->setCurrentIndex(2);
    Timer30();
    page = 3;
}

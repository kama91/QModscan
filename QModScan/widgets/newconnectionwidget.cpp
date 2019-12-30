#include "newconnectionwidget.h"
#include "ui_newconnectionwidget.h"

NewConnectionWidget::NewConnectionWidget(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::NewConnectionWidget)
{
    ui->setupUi(this);
    ui->lineEditIpAddress->setText("127.0.0.1");
    ui->lineEditPort->setText("502");
    ui->lineEditSlaveId->setText("1");
    ui->lineEditPointAddress->setText("0");
    ui->lineEditScanRate->setText("1000");
    ui->lineEditLength->setText("10");
    connect(ui->rbTypeRtuRadio,  &QAbstractButton::toggled, this, &NewConnectionWidget::updateConnectOptions);
    connect(ui->rbTypeTcpRadio,  &QAbstractButton::toggled, this, &NewConnectionWidget::updateConnectOptions);
    ui->rbTypeTcpRadio->setChecked(true);
    initComboBoxes();
    for(int i = 1; i < 20; i++)
    ui->comboBoxSerialPort->addItem(tr("COM%1").arg(i));
}

NewConnectionWidget::~NewConnectionWidget()
{
    delete ui;
}

void NewConnectionWidget::initComboBoxes()
{
    _baudRateOptions =  new QMap<QString, QSerialPort::BaudRate>();
    _baudRateOptions->insert("1200", QSerialPort::Baud1200);
    _baudRateOptions->insert("2400", QSerialPort::Baud2400);
    _baudRateOptions->insert("4800", QSerialPort::Baud4800);
    _baudRateOptions->insert("9600", QSerialPort::Baud9600);
    _baudRateOptions->insert("19200", QSerialPort::Baud19200);
    _baudRateOptions->insert("38400", QSerialPort::Baud38400);
    _baudRateOptions->insert("57600", QSerialPort::Baud57600);
    _baudRateOptions->insert("115200", QSerialPort::Baud115200);
    ui->comboBoxBaudRate->addItems(QStringList(_baudRateOptions->keys()));

    _dataBitsOptions = new QMap<QString, QSerialPort::DataBits>();
    _dataBitsOptions->insert("5", QSerialPort::Data5);
    _dataBitsOptions->insert("6", QSerialPort::Data6);
    _dataBitsOptions->insert("7", QSerialPort::Data7);
    _dataBitsOptions->insert("8", QSerialPort::Data8);
    ui->comboBoxWordLength->addItems(QStringList(_dataBitsOptions->keys()));


    _parityOptions = new QMap<QString, QSerialPort::Parity>();
    _parityOptions->insert("Even", QSerialPort::EvenParity);
    _parityOptions->insert("Odd", QSerialPort::OddParity);
    _parityOptions->insert("No parity", QSerialPort::NoParity);
    ui->comboBoxParity->addItems(QStringList(_parityOptions->keys()));

    _stopBitsOptions = new QMap<QString, QSerialPort::StopBits>();
    _stopBitsOptions->insert("1", QSerialPort::OneStop);
    _stopBitsOptions->insert("2", QSerialPort::TwoStop);
    ui->comboBoxStopBits->addItems(QStringList(_stopBitsOptions->keys()));
}

BaseDeviceConfig *NewConnectionWidget::getDeviceConfig() const
{
    return _deviceConfig;
}
void NewConnectionWidget::updateConnectOptions()
{
    bool IsTcp = ui->rbTypeTcpRadio->isChecked();
    ui->lineEditIpAddress->setEnabled(IsTcp);
    ui->lineEditPort->setEnabled(IsTcp);
    ui->comboBoxSerialPort->setEnabled(!IsTcp);
    ui->comboBoxBaudRate->setEnabled(!IsTcp);
    ui->comboBoxParity->setEnabled(!IsTcp);
    ui->comboBoxStopBits->setEnabled(!IsTcp);
    ui->comboBoxWordLength->setEnabled(!IsTcp);
}

void NewConnectionWidget::on_buttonBox_accepted()
{
     bool IsTcp = ui->rbTypeTcpRadio->isChecked();
     if (IsTcp)
     {
         auto tcpDeviceConfig = new TcpDeviceConfig(this);
         tcpDeviceConfig->setHost(ui->lineEditIpAddress->text());
         tcpDeviceConfig->setPort(ui->lineEditPort->text().toUInt());
         tcpDeviceConfig->setSlave(ui->lineEditSlaveId->text().toUInt());
         tcpDeviceConfig->setLength(ui->lineEditLength->text().toUInt());
         tcpDeviceConfig->setPointAddress(ui->lineEditPointAddress->text().toUInt());
         tcpDeviceConfig->setScanRate(ui->lineEditScanRate->text().toInt());
         _deviceConfig = tcpDeviceConfig;
     }
     else if (!IsTcp)
     {
         auto rtuDeviceConfig = new RtuDeviceConfig(this);
         rtuDeviceConfig->setSlave(ui->lineEditSlaveId->text().toUInt());
         rtuDeviceConfig->setLength(ui->lineEditLength->text().toUInt());
         rtuDeviceConfig->setPointAddress(ui->lineEditPointAddress->text().toUInt());
         rtuDeviceConfig->setScanRate(ui->lineEditScanRate->text().toInt());
         rtuDeviceConfig->setSerialPortName(ui->comboBoxSerialPort->currentText());
         rtuDeviceConfig->setParity(_parityOptions->value(ui->comboBoxParity->currentText()));
         rtuDeviceConfig->setBaud(_baudRateOptions->value(ui->comboBoxBaudRate->currentText()));
         rtuDeviceConfig->setDataBits(_dataBitsOptions->value(ui->comboBoxWordLength->currentText()));
         rtuDeviceConfig->setStopBits(_stopBitsOptions->value(ui->comboBoxStopBits->currentText()));
         _deviceConfig = rtuDeviceConfig;
     }
}

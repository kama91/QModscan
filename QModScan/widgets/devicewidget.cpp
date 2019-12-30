#include "devicewidget.h"
#include "ui_devicewidget.h"
#include <QtWidgets>
#include <loggingcategories.h>

static int deviceNumber = 1;

DeviceWidget::DeviceWidget(BaseModbusClient* modbusClient, QWidget* parent):
    QMainWindow(parent),
    ui(new Ui::DeviceWidget),
    _modbusClient(modbusClient)
{
    ui->setupUi(this);
    ui->tableView->setModel(_modbusClient->model());
    connect(ui->actionConnection, &QAction::triggered, this, &DeviceWidget::updateConnect);
    connect(ui->actionDisconnection, &QAction::triggered,this,&DeviceWidget::updateConnect);
    connect(_modbusClient, &BaseModbusClient::dataUpdate, this, &DeviceWidget::updateTextData);
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), _modbusClient, SLOT(updateRegisterType(int)));
    deviceFileName = tr("QModSca%1").arg(deviceNumber++);
    setWindowTitle(deviceFileName+ "[*]");
    ui->actionDisconnection->setEnabled(false);
}

DeviceWidget::~DeviceWidget()
{
    delete ui;
    _modbusClient->stop();
}

void DeviceWidget::updateConnect()
{
    _modbusClient->switchConnect();
    if (_modbusClient->deviceConnectState)
    {
        ui->pushButtonConnect->setText("Disconnect");
        ui->actionConnection->setEnabled(false);
        ui->actionDisconnection->setEnabled(true);
    }
    else
    {
       ui->pushButtonConnect->setText("Connect");
       ui->actionDisconnection->setEnabled(false);
       ui->actionConnection->setEnabled(true);
       ui->plainTextEdit->appendHtml("<font color = \"red\">** DEVICE NOT CONNECTED! **</font>");
    }
}

void DeviceWidget::on_pushButtonConnect_clicked()
{
    updateConnect();
}

void DeviceWidget::updateButtonText(QModbusDevice::State state)
{
    QMetaEnum metaEnum = QMetaEnum::fromType<QModbusDevice::State>();
    ui->pushButtonConnect->setText(metaEnum.valueToKey(state));
}

void DeviceWidget::updateTextData(QString data)
{
    ui->plainTextEdit->appendPlainText(data);
}

void DeviceWidget::on_pushButtonClear_clicked()
{
    ui->plainTextEdit->clear();
}

QString DeviceWidget::userFriendlyCurrentFile()
{
    return strippedName(deviceFileName);
}

QString DeviceWidget::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}


bool DeviceWidget::deviceSave()
{
    return saveFile(deviceFileName);
}

bool DeviceWidget::saveFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("DEVICE"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(QDir::toNativeSeparators(fileName), file.errorString()));
        qInfo(logInfo()) << QMessageBox::warning(this, tr("DEVICE"),
                                                 tr("Cannot write file %1:\n%2.")
                                                 .arg(QDir::toNativeSeparators(fileName), file.errorString()));
        return false;
    }
    QTextStream out(&file);
    out << "123";
    setCurrentFile(fileName);
    return true;

}

void DeviceWidget::setCurrentFile(const QString &fileName)
{
    deviceFileName = QFileInfo(fileName).canonicalFilePath();
    setWindowModified(false);
    setWindowTitle(userFriendlyCurrentFile() + "[*]");
}



void DeviceWidget::on_spinBox_valueChanged(int countRegisters)
{
    _modbusClient->setLength(static_cast<quint16>(countRegisters));
    //_modbusClient->model()->UpdateSize(countRegisters);
}

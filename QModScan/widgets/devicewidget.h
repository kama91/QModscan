#ifndef DEVICEFORM_H
#define DEVICEFORM_H

#include <QMainWindow>
#include "basedeviceconfig.h"
#include "tcpdeviceconfig.h"
#include "modbus/tcpmodbusclient.h"
#include <QMetaEnum>
#include <QSpinBox>

namespace Ui {
class DeviceWidget;
}

class DeviceWidget : public QMainWindow
{
    Q_OBJECT

public:
    explicit DeviceWidget(BaseModbusClient* modbusTcpClient, QWidget* parent = nullptr);
    QString userFriendlyCurrentFile();
    bool deviceSave();
    bool saveFile(const QString &fileName);
    ~DeviceWidget();

public slots:


private slots:
    void on_pushButtonConnect_clicked();
    void updateButtonText(QModbusDevice::State state);
    void updateTextData(QString data);
    void updateConnect();
    void on_pushButtonClear_clicked();

    void on_spinBox_valueChanged(int arg1);

private:
    Ui::DeviceWidget* ui;
    BaseModbusClient* _modbusClient;
    QString deviceFileName;
    QString strippedName(const QString &fullFileName);
     void setCurrentFile(const QString &fileName);
};

#endif // DEVICEFORM_H

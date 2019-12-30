#ifndef NEWCONNECTIONWIDGET_H
#define NEWCONNECTIONWIDGET_H

#include <QDialog>
#include <QUrl>
#include "tcpdeviceconfig.h"
#include "rtudeviceconfig.h"
#include "devicewidget.h"


namespace Ui {
class NewConnectionWidget;
}

class NewConnectionWidget : public QDialog
{
    Q_OBJECT

public:
    explicit NewConnectionWidget(QWidget* parent = nullptr);
    ~NewConnectionWidget();
    BaseDeviceConfig* getDeviceConfig() const;

private slots:
    void on_buttonBox_accepted();
    void updateConnectOptions();

private:
    Ui::NewConnectionWidget* ui;
    BaseDeviceConfig* _deviceConfig;
    QMap<QString, QSerialPort::BaudRate>* _baudRateOptions;
    QMap<QString, QSerialPort::DataBits>* _dataBitsOptions;
    QMap<QString, QSerialPort::Parity>* _parityOptions;
    QMap<QString, QSerialPort::StopBits>* _stopBitsOptions;

    void initComboBoxes();
};

#endif // NEWCONNECTIONWIDGET_H

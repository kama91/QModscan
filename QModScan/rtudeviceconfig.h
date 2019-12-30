#ifndef RTUDEVICECONFIG_H
#define RTUDEVICECONFIG_H

#include "basedeviceconfig.h"
#include <QtSerialPort/QSerialPort>

class RtuDeviceConfig : public BaseDeviceConfig
{
public:
    explicit RtuDeviceConfig(QObject* pobj = nullptr);

    QString serialPortName() const;
    void setSerialPortName(const QString &serialPortName);

    int parity() const;
    void setParity(int parity);

    int baud() const;
    void setBaud(int baud);

    int dataBits() const;
    void setDataBits(int dataBits);

    int stopBits() const;
    void setStopBits(int stopBits);

private:
    QString _serialPortName;
    int _parity;
    int _baud;
    int _dataBits;
    int _stopBits;
};

#endif // RTUDEVICECONFIG_H

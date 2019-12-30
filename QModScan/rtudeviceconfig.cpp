#include "rtudeviceconfig.h"

RtuDeviceConfig::RtuDeviceConfig(QObject* pobj) : BaseDeviceConfig (pobj)
{

}

QString RtuDeviceConfig::serialPortName() const
{
    return _serialPortName;
}

void RtuDeviceConfig::setSerialPortName(const QString& serialPortName)
{
    _serialPortName = serialPortName;
}

int RtuDeviceConfig::parity() const
{
    return _parity;
}

void RtuDeviceConfig::setParity(int parity)
{
    _parity = parity;
}

int RtuDeviceConfig::baud() const
{
    return _baud;
}

void RtuDeviceConfig::setBaud(int baud)
{
    _baud = baud;
}

int RtuDeviceConfig::dataBits() const
{
    return _dataBits;
}

void RtuDeviceConfig::setDataBits(int dataBits)
{
    _dataBits = dataBits;
}

int RtuDeviceConfig::stopBits() const
{
    return _stopBits;
}

void RtuDeviceConfig::setStopBits(int stopBits)
{
    _stopBits = stopBits;
}

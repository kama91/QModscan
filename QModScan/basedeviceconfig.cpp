#include "basedeviceconfig.h"

BaseDeviceConfig::BaseDeviceConfig(QObject* pobj) : QObject (pobj)
{

}

QString BaseDeviceConfig::title() const
{
    return _title;
}

void BaseDeviceConfig::setTitle(const QString& title)
{
    _title = title;
}

int BaseDeviceConfig::pointAddress() const
{
    return _pointAddress;
}

void BaseDeviceConfig::setPointAddress(int pointAddress)
{
    _pointAddress = pointAddress;
}

quint16 BaseDeviceConfig::length() const
{
    return _length;
}

void BaseDeviceConfig::setLength(quint16 length)
{
    _length = length;
}

unsigned int BaseDeviceConfig::slave() const
{
    return _slave;
}

void BaseDeviceConfig::setSlave(unsigned int slave)
{
    _slave = slave;
}

int BaseDeviceConfig::scanRate() const
{
    return _scanRate;
}

void BaseDeviceConfig::setScanRate(int scanRate)
{
    _scanRate = scanRate;
}

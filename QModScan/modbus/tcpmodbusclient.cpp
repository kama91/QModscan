#include "tcpmodbusclient.h"

TcpModbusClient::TcpModbusClient(TcpDeviceConfig* deviceConfig, QObject* parent) : BaseModbusClient (parent)
{
    _deviceConfig = deviceConfig;
    QVariant host(deviceConfig->host());
    _modbusClient = new QModbusTcpClient();
    _modbusClient->setConnectionParameter(QModbusDevice::NetworkAddressParameter, host);
    _modbusClient->setConnectionParameter(QModbusDevice::NetworkPortParameter, deviceConfig->port());
    _modbusClient->setTimeout(deviceConfig->scanRate());
}

void TcpModbusClient::updateDeviceConfig(BaseDeviceConfig* deviceConfig)
{
    auto newConfig = dynamic_cast<TcpDeviceConfig*>(deviceConfig); //TODO stop client before updateConfig
    if (newConfig == nullptr) return;
    _modbusClient->setConnectionParameter(QModbusDevice::NetworkAddressParameter, newConfig->host());
    _modbusClient->setConnectionParameter(QModbusDevice::NetworkPortParameter, newConfig->port());
    _modbusClient->setTimeout(newConfig->scanRate()); //TODO
    BaseModbusClient::updateDeviceConfig(deviceConfig);
}

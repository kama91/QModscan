#include "rtumodbusclient.h"

RtuModbusClient::RtuModbusClient(RtuDeviceConfig* deviceConfig, QObject* pobj) : BaseModbusClient (pobj)
{
    _deviceConfig = deviceConfig;
    _modbusClient = new QModbusRtuSerialMaster();
    _modbusClient->setConnectionParameter(QModbusDevice::SerialPortNameParameter, deviceConfig->serialPortName());
    _modbusClient->setConnectionParameter(QModbusDevice::SerialParityParameter, deviceConfig->parity());
    _modbusClient->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, deviceConfig->baud());
    _modbusClient->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, deviceConfig->dataBits());
    _modbusClient->setConnectionParameter(QModbusDevice::SerialStopBitsParameter, deviceConfig->stopBits());
    _modbusClient->setTimeout(deviceConfig->scanRate());
}

void RtuModbusClient::updateDeviceConfig(BaseDeviceConfig* deviceConfig)
{

}

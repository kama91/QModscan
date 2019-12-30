#include "basemodbusclient.h"
#include "loggingcategories.h"

BaseModbusClient::BaseModbusClient(QObject* parent) : QObject(parent)
{
}

void BaseModbusClient::start()
{
    if (_modbusClient->connectDevice())
    {
        startTimer(_deviceConfig->scanRate());
        deviceConnectState = true;
        auto messageConnect = "Device connected";
        qDebug(logDebug()) << messageConnect;
    }
    else
    {
        auto messageNotConnect = "Device not connected";
        qDebug(logDebug()) << messageNotConnect;
        deviceConnectState = false;
    }
}

void BaseModbusClient::stop()
{
    _modbusClient->disconnectDevice();
    deviceConnectState = false;
}

void BaseModbusClient::switchConnect()
{
    if (_modbusClient->state() == QModbusDevice::ConnectedState)
        stop();
    else
        start();
}

void BaseModbusClient::updateDeviceConfig(BaseDeviceConfig* deviceConfig)
{
    _deviceConfig = deviceConfig;
    _model->UpdateSize(_deviceConfig->length());
}

void BaseModbusClient::setLength(quint16 countRegisters)
{
    _deviceConfig->setLength(countRegisters);
    _model->UpdateSize(_deviceConfig->length());
}

ModbusModel* BaseModbusClient::model() const
{
    return _model;
}

void BaseModbusClient::timerEvent(QTimerEvent*)
{
    qDebug() << "timer event";
    if (auto* reply = _modbusClient->sendReadRequest(getModbusDataUnit(), _deviceConfig->slave()))
    {
        if (!reply->isFinished())
            connect(reply, &QModbusReply::finished, this, &BaseModbusClient::readReady);
        else
            delete reply;
    }
}

QModbusDataUnit BaseModbusClient::getModbusDataUnit()
{
    return QModbusDataUnit(_registerType, _deviceConfig->pointAddress(), _deviceConfig->length());
}

void BaseModbusClient::readReady()
{
    auto reply = qobject_cast<QModbusReply*>(sender());
        if (!reply)
            return;
        qDebug() << reply->error();
        qDebug() << reply->errorString();
        if (reply->error() == QModbusDevice::NoError)
        {
            const QModbusDataUnit unit = reply->result();
            QString output;
            if (_model->columnCount() < _deviceConfig->length())
                _model->UpdateSize(_deviceConfig->length()); //TODO
            for (int i =0; i < static_cast<int>(unit.valueCount()); i++)
            {
                output += QString::number(unit.value(i)) + " ";
                _model->setData(_model->index(0, i), unit.value(i));
                _model->dataChanged(_model->index(0, i),_model->index(0, i));
            }
            emit dataUpdate(output);

            qDebug() << output;
        }
}

void BaseModbusClient::updateRegisterType(int registerType)
{
    _registerType = static_cast<QModbusDataUnit::RegisterType>(registerType + 1);
}

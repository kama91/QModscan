#ifndef BASEMODBUSCLIENT_H
#define BASEMODBUSCLIENT_H

#include <QObject>
#include <QModbusClient>
#include "model/modbusmodel.h"
#include "basedeviceconfig.h"

class BaseModbusClient : public QObject
{
    Q_OBJECT
public:
    explicit BaseModbusClient(QObject* parent = nullptr);
    void start();
    void stop();
    void switchConnect();
    bool deviceConnectState;
    virtual void updateDeviceConfig(BaseDeviceConfig* deviceConfig);
    void setLength(quint16 countRegisters);
    ModbusModel *model() const;

private:    
    ModbusModel* _model = new ModbusModel();
    void timerEvent(QTimerEvent* event) override;
    QModbusDataUnit::RegisterType _registerType = QModbusDataUnit::DiscreteInputs;
    QModbusDataUnit getModbusDataUnit(); //todo rename

protected:
    BaseDeviceConfig* _deviceConfig;
    QModbusClient* _modbusClient;

signals:
    void dataUpdate(QString data);

public slots:
    void readReady();
    void updateRegisterType(int registerType);
};

#endif // BASEMODBUSCLIENT_H

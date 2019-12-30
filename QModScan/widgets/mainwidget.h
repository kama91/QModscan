#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGlobal>
#include <QtDebug>
#include "widgets/newconnectionwidget.h"
#include "modbus/tcpmodbusclient.h"
#include "modbus/rtumodbusclient.h"
#include <QMdiArea>
#include <QAction>
#include <QtWidgets>



namespace Ui {
class MainWidget;
}

class MainWidget : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget* parent = nullptr);
    ~MainWidget();

private:
    Ui::MainWidget* ui;
    QMenu* fileMenu;
    QMenu* windowMenu;
    QMenu* helpMenu;
    QAction* newDeviceAct;
    QAction* saveAct;
    QAction* closeWindowAct;
    QAction* closeAllWindowsAct;
    QAction* tileAct;
    QAction* cascadeAct;
    QAction* nextAct;
    QAction* previousAct;
    QAction* windowMenuSeparatorAct;
    QAction* callAboutWindow;
    DeviceWidget *activeWindow() const;
    BaseModbusClient* createDevice(BaseDeviceConfig* deviceConfig); //TODO do it another
    QMdiArea* mdiArea;


private slots:
    void newDevice();
    void createActions();
    void createMenus();
    void updateMenus();
    void deviceSave();
    void aboutWindow();
};

#endif // MAINWINDOW_H

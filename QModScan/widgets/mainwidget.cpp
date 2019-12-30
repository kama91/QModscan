#include "widgets/mainwidget.h"
#include "ui_mainwidgetui.h"
#include "LoggingCategories.h"

MainWidget::MainWidget(QWidget *parent) : mdiArea(new QMdiArea),
    //QMainWindow(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setCentralWidget(mdiArea);
    connect(mdiArea, &QMdiArea::subWindowActivated,
            this, &MainWidget::updateMenus);
    createActions();
    createMenus();
    updateMenus();
}

MainWidget::~MainWidget()
{
    delete ui;
}


void MainWidget::createActions()
{   
    auto *fileToolBar = addToolBar(tr("File"));

    const QIcon newIcon = QIcon::fromTheme("document-new", QIcon(":/images/connect.png"));
    newDeviceAct = new QAction(newIcon,tr("&New device"), this);
    newDeviceAct->setStatusTip(tr("Create a new device"));
    connect(newDeviceAct,&QAction::triggered,this,&MainWidget::newDevice);
    fileToolBar->addAction(newDeviceAct);

    const QIcon saveIcon = QIcon::fromTheme("document-new", QIcon(":/images/save.png"));
    saveAct= new QAction(saveIcon,"&Save File",this);
    saveAct->setText("&Save As");
    saveAct->setToolTip("Save device config");
    saveAct->setStatusTip("Save the file to disk");
    connect(saveAct,&QAction::triggered,this,&MainWidget::deviceSave);
    fileToolBar->addAction(saveAct);

    callAboutWindow = new QAction(tr("&About"), this);
    callAboutWindow->setStatusTip(tr("Call information about developer"));
    connect(callAboutWindow, &QAction::triggered, this, &MainWidget::aboutWindow);

    closeWindowAct = new QAction(tr("&Close window"), this);
    closeWindowAct->setStatusTip(tr("Close the active window"));
    connect(closeWindowAct, &QAction::triggered,
            mdiArea, &QMdiArea::closeActiveSubWindow);

    closeAllWindowsAct = new QAction(tr("&Close all windows"), this);
    closeAllWindowsAct->setStatusTip(tr("Close all opened the windows"));
    connect(closeAllWindowsAct, &QAction::triggered, mdiArea, &QMdiArea::closeAllSubWindows);

    tileAct = new QAction(tr("&Tile"), this);
    tileAct->setStatusTip(tr("Tile the windows"));
    connect(tileAct, &QAction::triggered, mdiArea, &QMdiArea::tileSubWindows);

    cascadeAct = new QAction(tr("&Cascade"), this);
    cascadeAct->setStatusTip(tr("Cascade the windows"));
    connect(cascadeAct, &QAction::triggered, mdiArea, &QMdiArea::cascadeSubWindows);

    nextAct = new QAction(tr("&Next"), this);
    nextAct->setShortcuts(QKeySequence::NextChild);
    nextAct->setStatusTip(tr("Move the focus to the next window"));
    connect(nextAct, &QAction::triggered, mdiArea, &QMdiArea::activateNextSubWindow);

    previousAct = new QAction(tr("&Previous"), this);
    previousAct->setShortcuts(QKeySequence::PreviousChild);
    previousAct->setStatusTip(tr("Move the focus to the previous "
                                 "window"));
    connect(previousAct, &QAction::triggered, mdiArea, &QMdiArea::activatePreviousSubWindow);

    windowMenuSeparatorAct = new QAction(this);
    windowMenuSeparatorAct->setSeparator(true);
}

void MainWidget::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    windowMenu = menuBar()->addMenu(tr("&Window"));
    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(callAboutWindow);
    fileMenu->addAction(newDeviceAct);
    fileMenu->addAction(saveAct);
}


void MainWidget::updateMenus()
{

    bool hasDeviceWidgetAct = activeWindow() != 0;
    closeWindowAct->setEnabled(hasDeviceWidgetAct);
    closeAllWindowsAct->setEnabled(hasDeviceWidgetAct);
    tileAct->setEnabled(hasDeviceWidgetAct);
    cascadeAct->setEnabled(hasDeviceWidgetAct);
    nextAct->setEnabled(hasDeviceWidgetAct);
    windowMenu->addAction(previousAct);
    previousAct->setEnabled(hasDeviceWidgetAct);
    windowMenuSeparatorAct->setVisible(hasDeviceWidgetAct);

    windowMenu->clear();
    windowMenu->addAction(closeWindowAct);
    windowMenu->addAction(closeAllWindowsAct);
    windowMenu->addSeparator();
    windowMenu->addAction(tileAct);
    windowMenu->addAction(cascadeAct);
    windowMenu->addSeparator();
    windowMenu->addAction(nextAct);
    windowMenu->addAction(previousAct);
    windowMenu->addAction(windowMenuSeparatorAct);

    QList<QMdiSubWindow *> windows = mdiArea->subWindowList();
    windowMenuSeparatorAct->setVisible(!windows.isEmpty());

    for (int i = 0; i < windows.size(); ++i) {
        QMdiSubWindow *mdiSubWindow = windows.at(i);
        auto *devicewidget = qobject_cast<DeviceWidget *>(mdiSubWindow->widget());

        QString text;
        if (i < 9) {
            text = tr("&%1 %2").arg(i + 1)
                               .arg(devicewidget->userFriendlyCurrentFile());
        } else {
            text = tr("%1 %2").arg(i + 1)
                              .arg(devicewidget->userFriendlyCurrentFile());
        }
        auto *action = windowMenu->addAction(text, mdiSubWindow, [this, mdiSubWindow]() {
            mdiArea->setActiveSubWindow(mdiSubWindow);
        });
        action->setCheckable(true);
        action ->setChecked(devicewidget == activeWindow());
    }
}

DeviceWidget *MainWidget::activeWindow() const
{
    if (QMdiSubWindow *activeSubWindow = mdiArea->activeSubWindow())
        return qobject_cast<DeviceWidget *>(activeSubWindow->widget());
    return 0;
}

void MainWidget::newDevice()
{
    auto newConnectionWidget = new NewConnectionWidget(this);
    switch (newConnectionWidget->exec())
    {
        case QDialog::Accepted:
            auto deviceConfig = newConnectionWidget->getDeviceConfig();
            if (deviceConfig == nullptr) return; //TODO make messagebox after
            auto modbusClient = createDevice(deviceConfig);
            auto deviceWidget = new DeviceWidget(modbusClient, this);
            mdiArea->addSubWindow(deviceWidget);
            deviceWidget->show();
            break;
    }
}


void MainWidget::deviceSave()
{
    if(activeWindow() && activeWindow()->deviceSave())
        statusBar()->showMessage(tr("File Saved"),2000);
    //qInfo(logInfo()) << "Text message";
}

void MainWidget::aboutWindow()
{
    QMessageBox* msgBox = new QMessageBox(this);
    msgBox->setText("QModScan version 1.0");
    msgBox->setText("The program was created by the Nazyrov Kamil,2019");
    msgBox->setWindowTitle("About");
    msgBox->setStandardButtons(QMessageBox::Ok);
    msgBox->setIcon(QMessageBox::Icon::Information);
    msgBox->show();
}


BaseModbusClient* MainWidget::createDevice(BaseDeviceConfig* deviceConfig)
{
    if (dynamic_cast<TcpDeviceConfig*>(deviceConfig))
        return new TcpModbusClient(dynamic_cast<TcpDeviceConfig*>(deviceConfig));
    if (dynamic_cast<RtuDeviceConfig*>(deviceConfig))
        return new RtuModbusClient(dynamic_cast<RtuDeviceConfig*>(deviceConfig));
    return nullptr;
}

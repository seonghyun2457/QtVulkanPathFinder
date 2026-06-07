#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QVulkanWindow>

#include <QPlainTextEdit>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ui(std::make_unique<Ui::MainWindow>())
    , m_pVulkanWidget(new VulkanWidget())
{
    m_ui->setupUi(this);

    initializeGuiWidgets();
    initializeVulkanWidget();
}

MainWindow::~MainWindow()
{

}

void MainWindow::displayVulkanInfo(const QString &iVulkanInfo)
{
    m_ui->vulkanInfo->appendPlainText(iVulkanInfo);
}

void MainWindow::displayDebugInfo(const QString &iDebugInfo)
{
    m_ui->debugLog->appendPlainText(iDebugInfo);
}

void MainWindow::onMousePressed(Qt::MouseButton button, const QPointF &position)
{
    QString msg = QString("%1 button clicked at (%2, %3)").arg(button).arg(position.x()).arg(position.y());
    displayDebugInfo(msg);
}

void MainWindow::setRowCount(const int iIndex)
{
    bool ok = false;
    const uint32_t rowCount = m_ui->cbRow->itemText(iIndex).toUInt(&ok);
    if (ok) emit transferRowCount(rowCount);
}

void MainWindow::setColumnCount(const int iIndex)
{
    bool ok = false;
    const uint32_t columnCount = m_ui->cbCol->itemText(iIndex).toUInt(&ok);
    if (ok) emit transferColumnCount(columnCount);
}

void MainWindow::initializeGuiWidgets()
{
    // CONNECT
    connect(m_ui->cbRow,  &QComboBox::activated, this, &MainWindow::setRowCount);
    connect(m_ui->cbCol,  &QComboBox::activated, this, &MainWindow::setColumnCount);
    connect(this,  &MainWindow::transferRowCount, m_pVulkanWidget, &VulkanWidget::setRowCount);
    connect(this,  &MainWindow::transferColumnCount, m_pVulkanWidget, &VulkanWidget::setColumnCount);


    // initialize cbRow
    for (size_t i = 0; i <= MAX_ROW_COUNT; ++i) {
        if (i >= 2) {
            m_ui->cbRow->addItem(QString::number(i));
        }
    }

    // initialize cbCol
    for (size_t i = 0; i <= MAX_COLUMN_COUNT; ++i) {
        if (i >= 2) {
            m_ui->cbCol->addItem(QString::number(i));
        }
    }
}


void MainWindow::initializeVulkanWidget()
{
    if (!m_pVulkanWidget) {
        displayDebugInfo("Failed to instantiate Vulkan window.");
        return;
    }

    // CONNECT
    // - Logging
    connect(m_pVulkanWidget, &VulkanWidget::sendVulkanInfo, this, &MainWindow::displayVulkanInfo);
    connect(m_pVulkanWidget, &VulkanWidget::sendDebugInfo, this, &MainWindow::displayDebugInfo);

    // - Mouse events
    connect(m_pVulkanWidget,  &VulkanWidget::mousePressed, this, &MainWindow::onMousePressed);

    qDebug() << "m_pVulkanWidget->width(): " << m_pVulkanWidget->width();
    qDebug() << "m_pVulkanWidget->height(): " << m_pVulkanWidget->height();

    m_pVulkanWidget->setWidth(900);
    m_pVulkanWidget->setHeight(500);

    qDebug() << "m_pVulkanWidget->width(): " << m_pVulkanWidget->width();
    qDebug() << "m_pVulkanWidget->height(): " << m_pVulkanWidget->height();

    // Window Container
    QWidget* pWindowContainer = QWidget::createWindowContainer(m_pVulkanWidget, m_ui->vulkanWindow->parentWidget());
    //pWindowContainer->setMouseTracking(true);
    pWindowContainer->setSizePolicy(m_ui->vulkanWindow->sizePolicy());
    pWindowContainer->setMinimumSize(m_ui->vulkanWindow->minimumSize());

    qDebug() << "pWindowContainer->sizePolicy(): " << pWindowContainer->sizePolicy();
    qDebug() << "pWindowContainer->minimumSize(): " << pWindowContainer->minimumSize();
    qDebug() << "pWindowContainer->width(): " << pWindowContainer->width();
    qDebug() << "pWindowContainer->height(): " << pWindowContainer->height();
    pWindowContainer->resize(900, 500);
    qDebug() << "pWindowContainer->width(): " << pWindowContainer->width();
    qDebug() << "pWindowContainer->height(): " << pWindowContainer->height();

    // Replace Window widget
    m_ui->vulkanLayout->replaceWidget(m_ui->vulkanWindow, pWindowContainer);
    delete m_ui->vulkanWindow;
    m_ui->vulkanWindow = pWindowContainer;
}

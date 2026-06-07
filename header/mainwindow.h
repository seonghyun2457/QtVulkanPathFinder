#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "vulkanwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();

signals:
    void transferRowCount(const uint32_t iRowCount);
    void transferColumnCount(const uint32_t iColumnCount);

private slots:
    // Logging slot
    void displayVulkanInfo(const QString& iVulkanInfo);
    void displayDebugInfo(const QString& iDebugInfo);

    // Mouse event slot
    void onMousePressed(Qt::MouseButton button, const QPointF& position);

    // Row & Column slot
    void setRowCount(const int iIndex);
    void setColumnCount(const int iIndex);
private:
    void initializeGuiWidgets();
    void initializeVulkanWidget();

private:
    std::unique_ptr<Ui::MainWindow> m_ui;
    VulkanWidget* m_pVulkanWidget;

    static constexpr size_t MAX_ROW_COUNT{30};
    static constexpr size_t MAX_COLUMN_COUNT{40};
};
#endif // MAINWINDOW_H

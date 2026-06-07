#ifndef VULKANWIDGET_H
#define VULKANWIDGET_H

#include <QWindow>
#include <QMouseEvent>

#include "vulkanrenderer.h"
#include "rectangle.h"

class VulkanWidget : public QWindow
{
    Q_OBJECT
public:
    VulkanWidget();
    virtual ~VulkanWidget();

signals:
    // Logging
    void sendVulkanInfo(const QString& iVulkanInfoString);
    void sendDebugInfo(const QString& iDebugString);

    // Mouse Event signals
    void mousePressed(Qt::MouseButton iButton, const QPointF& iPosition);
    void mouseMoved(const QPointF& iPosition);

public slots:
    void setRowCount(const uint32_t iRowCount);
    void setColumnCount(const uint32_t iColumnCount);

protected:
    virtual void exposeEvent(QExposeEvent* event) override;
    virtual bool event(QEvent* e) override;
    virtual void resizeEvent(QResizeEvent* event) override;

    // Mouse Events
    virtual void mousePressEvent(QMouseEvent* event) override;
    virtual void mouseMoveEvent(QMouseEvent* event) override;

private:
    void initializeRenderer();
    void draw();

private:
    std::unique_ptr<VulkanRenderer> m_pVulkanRenderer;
    bool m_initisialized{false};

    uint32_t m_rowCount{2};
    uint32_t m_colCount{2};

    std::vector<bool> m_occupied;
};

#endif // VULKANWIDGET_H

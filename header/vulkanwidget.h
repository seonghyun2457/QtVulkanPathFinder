#ifndef VULKANWIDGET_H
#define VULKANWIDGET_H

#include <QWindow>
#include <QMouseEvent>

#include "vulkanrenderer.h"

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
};

#endif // VULKANWIDGET_H

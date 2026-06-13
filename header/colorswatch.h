#ifndef COLORSWATCH_H
#define COLORSWATCH_H

#include <QWidget>
#include <QColor>

QT_BEGIN_NAMESPACE
namespace Ui {
class ColorSwatch;
}
QT_END_NAMESPACE

class ColorSwatch : public QWidget
{
    Q_OBJECT

public:
    explicit ColorSwatch(QWidget *parent = nullptr);
    ~ColorSwatch();

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent* event) override;

private:
    void applyStyle();
    void changeColor();

private:
    QColor m_color{Qt::black};
};

#endif // COLORSWATCH_H

#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItemGroup>

class PaintScene : public QGraphicsScene
{
    Q_OBJECT
    Q_PROPERTY(QPointF prevPos READ prevPos WRITE setPrevPos NOTIFY prevPosChanged)

public:
    explicit PaintScene(QObject *parent = 0);
    ~PaintScene();

    // Загрузка изображения
    void setPixmap(const QPixmap pixmap);
    // Цвет линий и текста
    void setColor(const Qt::GlobalColor color);
    // Задание обрезки изображения
    void setResizing(const bool Resizing);
    // Обрезка изображения
    QPixmap Resize();

    QPointF prevPos() const;
    void setPrevPos(const QPointF prevPos);

    // Тип рисуемого элемента
    enum drawType {
        none = 0,
        pen,
        line,
        elipse,
        rectangle,
        text
    };
    // Тип текущего элемента
    drawType drawElement = drawType::pen;

signals:
    // Изменена позиция мыши
    void prevPosChanged();

public slots:
    // Отмена предыдущего действия
    void removePrevItem();


private:
    QPointF m_prevPos;  // Координаты предыдущей точки
    Qt::GlobalColor currentColor = Qt::red; // Цвет линий
    // Текущий отрисовываемый элемент
    QGraphicsItem *currentItem;
    // Индикатор нажатой кнопки мыши
    bool m_leftMouseBtnPressed {false};
    // Индикатор ввода текста
    bool isTyping {false};
    // Индикатор обрезания изображения
    bool isResizing {false};
    // Резервное изображение для обрезания
    QGraphicsPixmapItem* m_currentImageItem {nullptr};
    // Прямоугольник выбора области для обрезания
    QGraphicsRectItem* m_selection {nullptr};

protected:
    // Для рисования используются события мыши
    void mousePressEvent(QGraphicsSceneMouseEvent * event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // PAINTSCENE_H

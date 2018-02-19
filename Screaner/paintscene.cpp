#include "paintscene.h"

PaintScene::PaintScene(QObject *parent) : QGraphicsScene(parent)
{

}

PaintScene::~PaintScene()
{
    delete currentItem;
}

void PaintScene::setPixmap(const QPixmap pixmap)
{
    // Загрузка изображения

    clear();

    addPixmap(pixmap);

    // Резервное сохранение изображение для использования его при обрезке,
    // если потребуется
    m_currentImageItem = new QGraphicsPixmapItem(pixmap);
}

void PaintScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // При нажатии кнопки мыши отрисовать элемент
    switch (drawElement) {
    case drawType::pen :
        addEllipse(event->scenePos().x() - 3, event->scenePos().y() - 3, 6, 6,
                   QPen(Qt::NoPen), QBrush(currentColor));
        m_leftMouseBtnPressed = true;
        break;
    case drawType::line :
        if (event->button() & Qt::LeftButton) {
            m_leftMouseBtnPressed = true; // Зажата ЛКМ
            QGraphicsLineItem *line = new QGraphicsLineItem();
            // Сохранить элемент
            currentItem = line;
            // Вывести на графическую сцену
            addItem(currentItem);
            line->setPen(QPen(QBrush(currentColor), 6));
            line->setLine(QLineF(m_prevPos, m_prevPos));
        }
        break;
    case drawType::elipse :
        if (event->button() & Qt::LeftButton) {
            m_leftMouseBtnPressed = true;
            QGraphicsEllipseItem *elipse = new QGraphicsEllipseItem();
            currentItem = elipse;
            addItem(currentItem);
            elipse->setPen(QPen(QBrush(currentColor), 6));
            elipse->setRect(QRectF(m_prevPos, m_prevPos));
        }
        break;
    case drawType::rectangle :
        if (event->button() & Qt::LeftButton) {
            m_leftMouseBtnPressed = true;            
            QGraphicsRectItem *rect = new QGraphicsRectItem();
            currentItem = rect;
            addItem(currentItem);
            rect->setPen(QPen(QBrush(currentColor), 6));
            rect->setRect(QRectF(m_prevPos, m_prevPos));
        }
        break;
    case drawType::text :
        if(isTyping) {
            QGraphicsTextItem * text =
                    qgraphicsitem_cast<QGraphicsTextItem *>(currentItem);
            // Отключить интерактивный вод текста
            text->setTextInteractionFlags(Qt::NoTextInteraction);
            isTyping = false;
        }
        else {
            QGraphicsTextItem *textItem = new QGraphicsTextItem();
            // Сохранить элемент
            currentItem = textItem;
            // Вывести на графическую сцену
            addItem(currentItem);
            textItem->setPos(event->scenePos());
            textItem->setDefaultTextColor(currentColor);
            textItem->setFont(QFont("Arial", 14));
            // Включить интерактивный ввод текста
            textItem->setTextInteractionFlags(Qt::TextEditorInteraction);
            textItem->setFocus();
            textItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
            textItem->setFlag(QGraphicsItem::ItemIsMovable, true);
            isTyping = true;
        }
        break;
    case drawType::none :
        if(isTyping) {
            QGraphicsTextItem * text =
                    qgraphicsitem_cast<QGraphicsTextItem *>(currentItem);
            // Отключить интерактивный вод текста
            text->setTextInteractionFlags(Qt::NoTextInteraction);
            // Изменить значение индикатора ввода
            isTyping = false;
        }
        else if(isResizing & (event->button() & Qt::LeftButton)) {
            // При выбранном режиме обрезки изображения и
            // зажатой левой кнопке мыши
            // Запомнить позицию
            m_leftMouseBtnPressed = true;
            setPrevPos(event->scenePos());

            // Создать квадрат выделения
            m_selection = new QGraphicsRectItem();
            m_selection->setBrush(QBrush(QColor(158, 182, 255, 96)));
            m_selection->setPen(QPen(QColor(158, 182, 255, 200), 1));
            // Запомнить объект
            currentItem = m_selection;
            // Вывести на графическую сцену
            addItem(currentItem);
        }
        break;
    }
    // Сохранить координаты точки нажатия
    setPrevPos(event->scenePos());
    QGraphicsScene::mousePressEvent(event);
}

void PaintScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseMoveEvent(event);
    if (!m_leftMouseBtnPressed) return; // Если не зажата ЛКМ - выход

    switch (drawElement) {
    case drawType::pen :
        // Отрисовать линии с использованием предыдущей координаты
        addLine(m_prevPos.x(), m_prevPos.y(), event->scenePos().x(),
                event->scenePos().y(), QPen(currentColor, 6, Qt::SolidLine,
                                            Qt::RoundCap));
        // Обновить данные о предыдущей координате
        m_prevPos = event->scenePos();
        break;
    case drawType::line :
    {
        QGraphicsLineItem *line =
                qgraphicsitem_cast<QGraphicsLineItem *>(currentItem);
        // Изменить координаты конечной точки
        line->setLine(QLineF(m_prevPos, event->scenePos()));
    }
        break;
    case drawType::elipse :
    {
        QGraphicsEllipseItem *elipse =
                qgraphicsitem_cast<QGraphicsEllipseItem *>(currentItem);
        elipse->setRect(QRectF(m_prevPos, event->scenePos()));
    }
        break;
    case drawType::rectangle :
    {
        QGraphicsRectItem *rect =
                qgraphicsitem_cast<QGraphicsRectItem *>(currentItem);
        rect->setRect(QRectF(m_prevPos, event->scenePos()));
    }
        break;
    case drawType::text :        
        break;
    case drawType::none :
        if(isResizing & m_leftMouseBtnPressed) {
            // Создать область выделения при движениюю мышью при зажатой левой кнопке
            auto dx = event->scenePos().x() - m_prevPos.x();
            auto dy = event->scenePos().y() - m_prevPos.y();
            m_selection->setRect(QRectF(m_prevPos.x(), m_prevPos.y(), dx, dy));
        }
        break;
    }    
}

void PaintScene::setColor(const Qt::GlobalColor color)
{
    // Цвет линий или текста
    currentColor = color;
}

QPointF PaintScene::prevPos() const
{
    // Предыдущая позиция клика мышью
    return m_prevPos;
}

void PaintScene::setPrevPos(const QPointF prevPos)
{
    // Запомнить позицию
    if (m_prevPos == prevPos)
        return;

    m_prevPos = prevPos;
    // Позиция изменена
    emit prevPosChanged();
}

void PaintScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    // Установить индикатор зажатой левой клопки мыши
    if (event->button() & Qt::LeftButton) {
        m_leftMouseBtnPressed = false;
        // Изменить индикатор обрезания изображения
        isResizing = false;
    }
    QGraphicsScene::mouseReleaseEvent(event);
}

void PaintScene::removePrevItem()
{
    // Отмена предыдущего действия
    QList<QGraphicsItem *> item = items();

    if (item.isEmpty() || (item.count() == 1)) return;

    // Удалить элемент
    delete item.first();
}

void PaintScene::setResizing(const bool Resizing)
{
    // Задание обрезки изображения
    isResizing = Resizing;
}

QPixmap PaintScene::Resize()
{
    // Обрезание изображения и передача его в главное окно приложения
    // для установки на сцену
    QRect selectionRect = m_selection->boundingRect().toRect();
    // Удалить выделение
    delete m_selection;
    // Передать изображение
    return m_currentImageItem->pixmap().copy(selectionRect);
}

#ifndef IMAGESCENE_H
#define IMAGESCENE_H

#include <QObject>
#include <QGraphicsScene>

class ImageScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit ImageScene(QObject *parent = 0);
    ~ImageScene();

    // Загрузка изображения
    void setPixmap(const QPixmap pixmap);
};


#endif //IMAGESCENE_H

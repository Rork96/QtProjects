#include "ImageScene.h"

#include <QGraphicsPixmapItem>
#include <QScreen>

ImageScene::ImageScene(QObject *parent) : QGraphicsScene(parent)
{
    // Размеры сцены
    //setSceneRect(0, 0, width()/2, height()/2);
}

ImageScene::~ImageScene()
{

}

void ImageScene::setPixmap(const QPixmap pixmap)
{
    // Загрузка изображения

    clear();

    QList<QGraphicsItem *> item = items();

    // Если в сцене больше одного элемента, то
    // удалить предыдущий
    if(item.count() > 1) delete item.last();

    QGraphicsPixmapItem *pix = new QGraphicsPixmapItem(pixmap);
    //pixmap.scaled(100, 100); //sceneRect().width()/3, sceneRect().height()/3, Qt::KeepAspectRatio);
    pix->setPos(sceneRect().width()/2-pixmap.width()/2, height()/2-pixmap.height()/2);
    pix->setScale(0.5);


    addItem(pix);

    //addPixmap(pixmap);
}
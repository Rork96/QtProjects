#include "ImageScene.h"

#include <QScreen>

ImageScene::ImageScene(QObject *parent) : QGraphicsScene(parent)
{
    // Размеры сцены
    setSceneRect(0, 0, sceneRect().width(), sceneRect().height());
}

ImageScene::~ImageScene()
{

}

void ImageScene::setPixmap(const QPixmap pixmap)
{
    // Загрузка изображения

    clear();

    addPixmap(pixmap);
}
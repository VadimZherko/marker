#include "mark.h"

Mark::Mark(int x, int y, int angular)
{
    this->setOffset(x, y);
    this->angular = angular;
    this->x = x;
    this->y = y;
    QPixmap QrImage(":/new/prefix1/img/markIcon.png");
    if(angular == 90) QrImage.load(":/new/prefix1/img/markIcon_90.png");
    else if(angular == 180) QrImage.load(":/new/prefix1/img/markIcon_180.png");
    else if (angular == 270) QrImage.load(":/new/prefix1/img/markIcon_270.png");

    this->setPixmap(QrImage);
    this->setFlag(QGraphicsItem::ItemIsMovable);
    this->setFlag(QGraphicsItem::ItemIsSelectable);
}

int Mark::getAngular()
{
    return this->angular;
}

int Mark::getX()
{
    return this->x;
}

int Mark::getY()
{
    return this->y;
}

void Mark::setAngular(int angular)
{
    this->angular = angular;
    QPixmap new_pixmap;
    if(angular == 0) new_pixmap.load(":/new/prefix1/img/markIcon.png");
    else if(angular == 90) new_pixmap.load(":/new/prefix1/img/markIcon_90.png");
    else if(angular == 180) new_pixmap.load(":/new/prefix1/img/markIcon_180.png");
    else if (angular == 270) new_pixmap.load(":/new/prefix1/img/markIcon_270.png");

    this->setPixmap(new_pixmap);
}

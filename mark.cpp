#include "mark.h"

Mark::Mark(int x, int y, int angular)
{
    this->setOffset(x, y);
    QPixmap QrImage(":/new/prefix1/img/markIcon.png");
    if(angular == 90) QrImage.load(":/new/prefix1/img/markIcon_90.png");
    else if(angular == 180) QrImage.load(":/new/prefix1/img/markIcon_180.png");
    else if (angular == 270) QrImage.load(":/new/prefix1/img/markIcon_270.png");

    this->setPixmap(QrImage);
    this->setFlag(QGraphicsItem::ItemIsMovable);
    this->setFlag(QGraphicsItem::ItemIsSelectable);
}

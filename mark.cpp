#include "mark.h"

Mark::Mark(int x, int y)
{
    this->setOffset(x, y);
    QPixmap QrImage(":/new/prefix1/img/barcode.png");
    this->setPixmap(QrImage);
    this->setFlag(QGraphicsItem::ItemIsMovable);
    this->setFlag(QGraphicsItem::ItemIsSelectable);
}

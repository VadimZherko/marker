#ifndef MARK_H
#define MARK_H

#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>

class Mark : public QGraphicsPixmapItem
{
public:
    Mark(int, int, int);
    int getAngular();
    int getY();
    int getX();

    void setAngular(int);

private:
    int angular;
    int x;
    int y;
};

#endif // MARK_H

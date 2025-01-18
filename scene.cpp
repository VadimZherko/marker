#include "scene.h"


Scene::Scene() {}

void Scene::drawBackground(QPainter* painter, const QRectF& rect)
{
    QColor color(225,79,0,255);
    QPen pen(color,1);
    painter->setPen(pen);

    int gridSize = 40; //ПЕРЕДЕЛАТЬ

    auto left = this->sceneRect().left();
    auto right = this->sceneRect().right();
    auto top = this->sceneRect().top();
    auto bottom = this->sceneRect().bottom();

    for(int y = top; y < bottom; y += gridSize) //Grid
    {
        painter->drawLine(QLineF(left, y, right, y));
        painter->drawLine(QLineF());
    }

    for(int x = left; x < right; x += gridSize) //Grid
    {
        painter->drawLine(QLineF(x, top, x, bottom));
    }

    pen.setWidthF(0.2);
    painter->setPen(pen);

    for(int y = top; y < bottom; y += gridSize / 5) //Grid
    {
        painter->drawLine(QLineF(left, y, right, y));
    }

    for(int x = left; x < right; x += gridSize / 5) //Grid
    {
        painter->drawLine(QLineF(x, top, x, bottom));
    }

    pen.setWidth(3);
    painter->setPen(pen);
    painter->drawLine(QLineF(0, top, 0, bottom));

    painter->drawLine(QLineF(left, 0, right, 0));

    color.setRgb(255,255,255,255);
    QPen pen_text(color);
    painter->setPen(pen_text);

    for(int x = left, i = -10; x < right; x+= gridSize, i++) //Lines on axis X
    {
        if(i == 0) continue;

        painter->setPen(pen);
        painter->drawLine(QLineF(x, -3, x, 3));

        painter->setPen(pen_text);
        painter->drawText(QPointF(x,10), QString::number(i));
    }

    for(int y = bottom, i = -10; y > top; y -= gridSize, i++) //Lines on axis Y
    {
        if(i == 0) continue;
        painter->setPen(pen);
        painter->drawLine(QLineF(-3, y, 3, y));

        painter->setPen(pen_text);
        painter->drawText(QPointF(10,y), QString::number(i));
    }

    painter->drawText(QPointF(10,10), QString::number(0));
}

void Scene::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Delete)
    {
        auto selectedItems = this->selectedItems();
        for(auto item : selectedItems)
        {
            this->removeItem(item);
            delete item;
        }
    }
}

#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QGraphicsSimpleTextItem>
#include <QPainter>
#include <QLineF>
#include <QKeyEvent>

enum Sides
{
    Top,
    Bottom,
    Left,
    Right
};

class Scene : public QGraphicsScene
{
public:
    Scene();
    void resize(double, double, Sides, Sides);
    int gridSize = 40;

protected:
    void drawBackground(QPainter* painter, const QRectF& rect) override;
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // SCENE_H

#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include "config.h"
#include "item.h"

//编辑时间：2021.2.9
//editor：SPJ
//qt版本：5.13.0
//编译器：MinGW 64-bit

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

protected:
    void paintEvent(QPaintEvent *);

    void mousePressEvent(QMouseEvent *e);

private:
    void init();

    void DrawChessBoard();

    void DrawItems();

    void DrawItemWithMouse();

    void DrawChessAtPoint(QPainter& painter,QPoint& pt);

    int CountNearItem(Item item, QPoint ptDirection);

private:

    QVector<Item> mItems;
    bool mIsBlackTurn;
};

#endif // WIDGET_H

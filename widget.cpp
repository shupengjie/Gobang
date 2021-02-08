#include "widget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>
#include <QIcon>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    init();
}

Widget::~Widget()
{

}

void Widget::init()
{
    //初始化窗口大小
    this->resize((CHESS_COLUMES + 1) * RECT_WIDTH,(CHESS_ROWS + 1) * RECT_HEIGHT);
    //设置窗体标题
    this->setWindowTitle("五子棋");
    //设置窗体图标
    this->setWindowIcon(QIcon(WINDOW_ICO_PATH));
    //第一步下黑棋
    mIsBlackTurn = true;
}

void Widget::paintEvent(QPaintEvent *)
{
    //绘制棋盘
    DrawChessBoard();
    //绘制棋子
    DrawItems();
    //下一步的棋子跟随鼠标
    DrawItemWithMouse();
    //绘制
    update();
}

void Widget::mousePressEvent(QMouseEvent *e)
{
    //求鼠标点击处棋子的位置
    QPoint pt;
    pt.setX(e->pos().x() / RECT_WIDTH);
    pt.setY(e->pos().y() / RECT_HEIGHT);

    //如果棋子已经存在
    for(int i = 0; i < mItems.size(); ++i)
    {
        if(mItems[i].mPt == pt)
        {
            return;
        }
    }

    //不存在就画一个
    Item item(pt,mIsBlackTurn);
    mItems.push_back(item);

    //求当前的棋子的八个方向连续同色棋子的数量
    int nLeft =			CountNearItem(item,QPoint(-1,0));
    int nLeftUp =		CountNearItem(item,QPoint(-1,-1));
    int nUp =			CountNearItem(item,QPoint(0,-1));
    int nRightUp =		CountNearItem(item,QPoint(1,-1));
    int nRight =		CountNearItem(item,QPoint(1,0));
    int nRightDown =	CountNearItem(item,QPoint(1,1));
    int nDown =			CountNearItem(item,QPoint(0,1));
    int nLeftDown =		CountNearItem(item,QPoint(-1,1));

    if ( (nLeft + nRight) >= 4 ||
         (nLeftUp + nRightDown) >= 4 ||
         (nUp + nDown) >= 4 ||
         (nRightUp + nLeftDown) >= 4 )
    {
        QString str = mIsBlackTurn ? "black" : "white";

        QMessageBox::information(NULL,"GAME OVER",str,QMessageBox::Yes , QMessageBox::Yes);

        mItems.clear();

        return;
    }

    mIsBlackTurn = !mIsBlackTurn;
}



void Widget::DrawChessBoard()
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::HighQualityAntialiasing, true);
    painter.setBrush(Qt::darkYellow);
    painter.setPen(QPen(QColor(Qt::black),2));

    for(int i = 0; i < CHESS_COLUMES; ++i)
    {
        for(int j = 0; j < CHESS_ROWS; ++j)
        {
            painter.drawRect((i+0.5)*RECT_WIDTH,(j+0.5)*RECT_HEIGHT,RECT_WIDTH,RECT_HEIGHT);
        }
    }
}

void Widget::DrawItems()
{
    QPainter painter(this);

    painter.setPen(QPen(QColor(Qt::transparent)));

    Item it;
    for(int i = 0; i < mItems.size(); ++i)
    {
        it = mItems[i];

        if(it.mBlack == true)
        {
            painter.setBrush(Qt::black);
        }
        else
        {
            painter.setBrush(Qt::white);
        }

        DrawChessAtPoint(painter,it.mPt);
    }

}

void Widget::DrawItemWithMouse()
{
    QPainter painter(this);

    painter.setPen(QPen(QColor(Qt::transparent)));

    if(mIsBlackTurn == true)
    {
        painter.setBrush(Qt::black);
    }
    else {
        painter.setBrush(Qt::white);
    }

    painter.drawEllipse(mapFromGlobal(QCursor::pos()),RECT_WIDTH / 2, RECT_HEIGHT / 2);

}

void Widget::DrawChessAtPoint(QPainter &painter, QPoint &pt)
{
    QPoint ptCenter((pt.x() + 0.5) * RECT_WIDTH,
                    (pt.y() + 0.5) * RECT_HEIGHT);
    painter.drawEllipse(ptCenter,RECT_WIDTH / 2,RECT_HEIGHT / 2);
}

int Widget::CountNearItem(Item item, QPoint ptDirection)
{
    int nCount = 0;
    item.mPt += ptDirection;

    while(mItems.contains(item))
    {
        ++nCount;
        item.mPt += ptDirection;
    }

    return nCount;
}

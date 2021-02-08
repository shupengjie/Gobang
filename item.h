#ifndef ITEM_H
#define ITEM_H

#include <QPoint>

class Item
{
public:
    Item();

    Item(QPoint pt,bool bBlack);

    ~Item();

    bool operator == (const Item& t1)const
    {
        return((mPt == t1.mPt) && (mBlack == t1.mBlack));
    }

    QPoint mPt;
    bool mBlack;
};

#endif // ITEM_H

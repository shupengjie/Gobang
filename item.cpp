#include "item.h"

Item::Item()
{

}

Item::Item(QPoint pt, bool bBlack)
{
    this->mPt = pt;
    this->mBlack = bBlack;
}

Item::~Item()
{

}


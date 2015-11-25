/*********************************************************************************
NixNote - An open-source client for the Evernote service.
Copyright (C) 2013 Randy Baumgarte

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
***********************************************************************************/

#include "ntagviewdelegate.h"
#include "ntagview.h"
#include "ntagviewitem.h"
#include "global.h"

#include <QPainter>

extern Global global;

NTagViewDelegate::NTagViewDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}



void NTagViewDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    QStyleOptionViewItemV4 options = option;
    initStyleOption(&options, index);

    options.widget->style()->drawControl(QStyle::CE_ItemViewItem, &options, painter);

    if (global.countBehavior == Global::CountNone)
        return;

    painter->save();

    qint32 lid = index.data(Qt::UserRole).toInt();
    if (lid > 0) {

        NTagView  *tree = (NTagView*)options.widget;
        NTagViewItem *item = tree->getItem(lid);
        qint32 subTotal = item->subTotal;
        qint32 total = item->total;
        QString countString;
        if (total == subTotal) {
            countString = QString("(")+QString::number(total) + QString(")");
        } else {
            countString = QString("(")+QString::number(subTotal) +QString("/") +QString::number(total) + QString(")");
        }

        QSize iconSize = options.icon.actualSize(options.rect.size());
        painter->translate(options.rect.left()+iconSize.width(), options.rect.top());
        QRect clip(0, 0, options.rect.width()+iconSize.width(), options.rect.height());

        painter->setClipRect(clip);
        QFontMetrics fm = options.fontMetrics;
        QFont f = options.font;
        f.setBold(false);
        painter->setFont(f);
        painter->setPen(Qt::darkGray);
        painter->drawText(10+fm.width(index.data().toString()+QString(" ")),fm.ascent(),countString);
//        painter->drawText(6+fm.width(index.data().toString()+QString("   ")),fm.ascent(),countString);
    }
    painter->restore();
}

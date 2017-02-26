/**
  * This file is part of the KDE project
  * Copyright (C) 2007 Rafael Fernández López <ereslibre@gmail.com>
  *
  * This library is free software; you can redistribute it and/or
  * modify it under the terms of the GNU Library General Public
  * License as published by the Free Software Foundation; either
  * version 2 of the License, or (at your option) any later version.
  *
  * This library is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  * Library General Public License for more details.
  *
  * You should have received a copy of the GNU Library General Public License
  * along with this library; see the file COPYING.LIB.  If not, write to
  * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
  * Boston, MA 02110-1301, USA.
  */

#include "piechart.h"

#include <QLinearGradient>

#include <kapplication.h>
#include <kcmdlineargs.h>
#include <kcolorscheme.h>
#include <kaboutdata.h>
#include <klocalizedstring.h>

int main(int argc, char **argv)
{
    KCmdLineArgs::init(argc, argv, new KAboutData("robus", "robus", ki18n("robus"), "robus"));
    KApplication app(true);

    KColorScheme scheme(QPalette::Normal);
    PieChart *widget = new PieChart();

    widget->addSlice("Free", 15, QColor(50,255,255,255));
    widget->addSlice("Used", 85, QColor(50,50,255,255));

//     widget->addSlice("Slice 1", 30, QColor(50,255,255,255), QPen(QColor(0,125,125,255), 1, Qt::SolidLine, Qt::FlatCap,  Qt::RoundJoin));
//     widget->addSlice("Slice 2", 40, QColor(50,50,255,255), QPen(QColor(0,0,125,255),1, Qt::SolidLine, Qt::FlatCap,  Qt::RoundJoin));
//     widget->addSlice("Slice 3", 10, QColor(255,50,50,255), QPen(QColor(125,0,0,255), 1, Qt::SolidLine, Qt::FlatCap,  Qt::RoundJoin));
//     widget->addSlice("Slice 4", 5, QColor(255,255,50,255), QPen(QColor(125,125,0,255), 1, Qt::SolidLine, Qt::FlatCap,  Qt::RoundJoin));
//     widget->addSlice("Slice 5", 10, QColor(255,50,255,255), QPen(QColor(125,0,125,255), 1, Qt::SolidLine, Qt::FlatCap,  Qt::RoundJoin));
//     widget->addSlice("Slice 6", 5, QColor(50,255,50,255), QPen(QColor(0,125,0,255), 1,Qt::SolidLine, Qt::FlatCap,  Qt::RoundJoin));

    widget->setKeysPosition(PieChart::Left);
    widget->setShowKeys(true);
    widget->show();

    return app.exec();
}

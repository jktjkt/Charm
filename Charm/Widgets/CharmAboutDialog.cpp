/*
  CharmAboutDialog.cpp

  This file is part of Charm, a task-based time tracking application.

  Copyright (C) 2014-2016 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com

  Author: Frank Osterfeld <frank.osterfeld@kdab.com>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "CharmAboutDialog.h"
#include "ui_CharmAboutDialog.h"

#include <CharmCMake.h>

CharmAboutDialog::CharmAboutDialog( QWidget* parent )
    : QDialog( parent )
    , m_ui( new Ui::CharmAboutDialog )
{
    m_ui->setupUi( this );
    QString versionText = m_ui->versionLabel->text();
    versionText.replace( "CHARM_VERSION", CHARM_VERSION );
    m_ui->versionLabel->setText( versionText );
}

CharmAboutDialog::~CharmAboutDialog()
{
}

#include "moc_CharmAboutDialog.cpp"

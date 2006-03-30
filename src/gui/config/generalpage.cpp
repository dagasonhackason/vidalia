/****************************************************************
 *  Vidalia is distributed under the following license:
 *
 *  Copyright (C) 2006,  Matt Edman, Justin Hipple
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; either version 2
 *  of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, 
 *  Boston, MA  02110-1301, USA.
 ****************************************************************/

/** 
 * \file generalpage.cpp
 * \version $Id$
 */

#include "generalpage.h"

/** Constructor */
GeneralPage::GeneralPage(QWidget *parent)
: QWidget(parent)
{
  /* Invoke the Qt Designer generated object setup routine */
  ui.setupUi(this);

  /* Bind event to actions */
  connect(ui.btnBrowseTorPath, SIGNAL(clicked()), this, SLOT(browseTorPath()));

  /* Hide platform specific features */
#ifndef Q_WS_WIN
  ui.chkRunWithSys->setVisible(false);
#endif
}

/* Open a QFileDialog to browse for Tor executable */
void
GeneralPage::browseTorPath()
{
  QString filename = QDir::convertSeparators(
                          QFileDialog::getExistingDirectory(this,
                              tr("Select Path to Tor"), 
                              ui.lineTorPath->text()));
  if (!filename.isEmpty()) {
    ui.lineTorPath->setText(filename);
  }
}

/* Saves all settings for this page */
void
GeneralPage::saveChanges(VidaliaSettings *vidaliaSettings, TorSettings *torSettings)
{
  torSettings->setPath(ui.lineTorPath->text());
  vidaliaSettings->setRunTorAtStart(ui.chkRunTor->isChecked());
  vidaliaSettings->setRunVidaliaOnBoot(ui.chkRunWithSys->isChecked());
}

/* Loads previously saved settings */
void
GeneralPage::loadSettings(VidaliaSettings *vidaliaSettings, TorSettings *torSettings)
{
  ui.lineTorPath->setText(torSettings->getPath());
  ui.chkRunTor->setChecked(vidaliaSettings->runTorAtStart());
  ui.chkRunWithSys->setChecked(vidaliaSettings->runVidaliaOnBoot());
}


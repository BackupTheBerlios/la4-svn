/******************************************************************************
 * LAStartDialog.cpp                                                          *
 ******************************************************************************
 *                                                                            *
 *   This program is free software; you can redistribute it and/or modify     *
 *   it under the terms of the GNU Lesser General Public License as           *
 *   published by the Free Software Foundation; either version 2 of the       *
 *   License, or (at your option) any later version.                          *
 *                                                                            *
 *   This program is distributed in the hope that it will be useful,          *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of           *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            *
 *   GNU Lesser General Public License for more details.                      *
 *                                                                            *
 *   You should have received a copy of the GNU Lesser General Public License *
 *   along with this program; if not, write to the                            *
 *   Free Software Foundation, Inc.,                                          *
 *   59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.                 *
 *                                                                            *
 ******************************************************************************
 * LA4: Tool for real-time systems design                                     *
 * Copyright (C) 2002-2007 by LA4 team <la4-dev@lists.berlios.de>             *
 ******************************************************************************/

#include "LAStartDialog.h"

/* Qt includes */
#include <QFileDialog>
#include <QtDebug>

/* LA4 includes */
#include "LAPlatform.h"
#include "LAPlatformManager.h"

/* Debugging levels */
#define DEBUG

/************************************************** Constructors/Destructor */
LAStartDialog::LAStartDialog(QWidget * parent)
	: QDialog(parent)
{

	/* First, let Qt do its stuff */
	m_ui.setupUi(this);

}

LAStartDialog::~LAStartDialog()
{
}

/************************************************************* Public slots */
void LAStartDialog::openBrowseDialog()
{

  QString filename = QFileDialog::getOpenFileName(this, tr("LA4 - Get LA4 file"), "", tr("LA4 files (*.la4)"));

  /* If the user accepted the dialog, set new text to line edit */
	if (!filename.isNull())
    {
      m_ui.filenamePath->setText(filename);

#ifdef DEBUG
      qDebug() << "LAStartDialog: Browse - Filename was" << filename;
#endif /* DEBUG */

    }
  else
    {

#ifdef DEBUG
      qDebug() << "LAStartDialog: Browse - No file selected";
#endif /* DEBUG */

    }

}

void LAStartDialog::show()
{

	/* Initialise fields */

  /* Get platforms and add them to list */
  m_ui.PlatformZoneList->clear();
  LAPlatform* platformPtr;
  foreach (platformPtr, *LAPlatformManager::getPlatforms())
    {

#ifdef DEBUG
      qDebug() << "LAStartDialog: Adding platform" << platformPtr->getName();
#endif /* DEBUG */

      m_ui.PlatformZoneList->addItem(platformPtr->getName());

    }

  /* This dialog is modal */
  setModal(true);

	/* Show the dialog */
	QDialog::show();

}

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
 * Copyright (C) 2002-2008 by LA4 team <la4-dev@lists.berlios.de>             *
 ******************************************************************************/

#include "LAStartDialog.h"

/* Qt includes */
#include <QFileDialog>
#include <QtDebug>

/* LA4 includes */
#include "LALogger.h"
#include "LAPlatform.h"
#include "LAPlatformManager.h"

/* Debugging levels */
#undef DEBUG

/************************************************** Constructors/Destructor */
LAStartDialog::LAStartDialog(QWidget * parent)
	: QDialog(parent)
{
  LALogger::TraceConstructor(LA_DEBUG_ARGS);

	/* First, let Qt do its stuff */
	m_ui.setupUi(this);
}

LAStartDialog::~LAStartDialog()
{
  LALogger::TraceDestructor(LA_DEBUG_ARGS);
}

/************************************************************* Public slots */
void LAStartDialog::openBrowseDialog()
{
  LALogger::TraceBeginMethod(LA_DEBUG_ARGS);

  QString filename = QFileDialog::getOpenFileName(this, tr("LA4 - Get LA4 file"), "", tr("LA4 files (*.la4)"));

  /* If the user accepted the dialog, set new text to line edit */
	if (!filename.isNull())
    {
      m_ui.filenamePath->setText(filename);

      /* Select the correct check box */
      m_ui.RadioButtonOpen->setChecked(true);

      LALogger::Trace(LALogger::DEBUG,
                      LALogger::MAIN,
                      "Browse - Filename was " + filename,
                      LA_DEBUG_ARGS);
    }
  else
    {
      LALogger::Trace(LALogger::DEBUG,
                      LALogger::MAIN,
                      "Browse - No file selected",
                      LA_DEBUG_ARGS);
    }

  LALogger::TraceEndMethod(LA_DEBUG_ARGS);
}

void LAStartDialog::show()
{
  LALogger::TraceBeginMethod(LA_DEBUG_ARGS);

	/* Initialise fields */

  /* Get platforms and add them to list */
  m_ui.PlatformList->clear();
  int firstItemIndex = -1;
  LAPlatform* platformPtr;
  foreach (platformPtr, *LAPlatformManager::getPlatforms())
    {
      LALogger::Trace(LALogger::DEBUG,
                      LALogger::MAIN,
                      "Adding platform " + platformPtr->getName(),
                      LA_DEBUG_ARGS);

      m_ui.PlatformList->addItem(platformPtr->getName());
      if (-1 == firstItemIndex)
        {
          firstItemIndex = m_ui.PlatformList->findText(platformPtr->getName());
        }
    }

  /* Select first item */
  m_ui.PlatformList->setCurrentIndex(firstItemIndex);

  /* This dialog is modal */
  setModal(true);

	/* Show the dialog */
	QDialog::show();

  LALogger::TraceEndMethod(LA_DEBUG_ARGS);
}

/******************************************************************************
 * LADocumentPropertiesDialog.cpp                                             *
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

#include "LADocumentPropertiesDialog.h"

/* Qt includes */

/* LA4 includes */
#include "LALogger.h"
#include "LAPlatform.h"
#include "LAPlatformManager.h"

/************************************************** Constructors/Destructor */
LADocumentPropertiesDialog::LADocumentPropertiesDialog(QWidget * parent)
	: QDialog(parent)
{
  LALogger::TraceConstructor(LA_DEBUG_ARGS);

	/* First, let Qt do its stuff */
	m_ui.setupUi(this);
}

LADocumentPropertiesDialog::~LADocumentPropertiesDialog()
{
  LALogger::TraceDestructor(LA_DEBUG_ARGS);
}

/************************************************************* Public slots */
void LADocumentPropertiesDialog::show()
{
  LALogger::TraceBeginMethod(LA_DEBUG_ARGS);

	/* Initialise fields */

  /* Get platforms and add them to list */
  m_ui.PlatformComboBox->clear();
  int firstItemIndex = -1;
  LAPlatform* platformPtr;
  foreach (platformPtr, *LAPlatformManager::getPlatforms())
    {
      LALogger::Trace(LALogger::DEBUG,
                      LALogger::MAIN,
                      "Adding platform " + platformPtr->getName(),
                      LA_DEBUG_ARGS);

      m_ui.PlatformComboBox->addItem(platformPtr->getName());
      if (-1 == firstItemIndex)
        {
          firstItemIndex = m_ui.PlatformComboBox->findText(platformPtr->getName());
        }
    }

  /* Select first item */
  m_ui.PlatformComboBox->setCurrentIndex(firstItemIndex);

  /* We test for now */
  m_ui.DocumentTitle->setText("This is not functional for now");

  /* This dialog is modal */
  setModal(true);

	/* Show the dialog */
	QDialog::show();

  LALogger::TraceEndMethod(LA_DEBUG_ARGS);
}

/******************************************************************************
 * LACATRE_Doc.cpp                                                            *
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

#include "LACATRE_Doc.h"

/* Qt includes */
#include "LALogger.h"

/* LA4 includes */

/* Globals */
/* Comments inserted in the default new document file */
/* Hack \n after comments are inserted by SaveFilePlugin */
#define LACATRE_DEF_TEXT	" This is a Lacatre save file. It was generated with La4: http://developer.berlios.de/projects/la4 "
#define LACATRE_INFO_TEXT	" Lacatre is a graphical language for designing multi-tasking applications,including IPCs, resource life cycle and simple algorithms. "

/************************************************** Constructors/Destructor */
LACATRE_Doc::LACATRE_Doc(QObject * parent)
	: QObject(parent)
{
	// createEmptyDocument();
  LALogger::TraceConstructor(LA_DEBUG_ARGS);
}

LACATRE_Doc::~LACATRE_Doc()
{
  LALogger::TraceDestructor(LA_DEBUG_ARGS);
}

/*********************************************************** Public methods */
void LACATRE_Doc::setDocumentFileName(const QString& aDocumentFilename)
{
  m_documentFilename = aDocumentFilename;
  LALogger::Trace(LALogger::DEBUG, LALogger::MAIN, "Setting new filename for document: " + aDocumentFilename, LA_DEBUG_ARGS);
}

void LACATRE_Doc::setTargetPlatform(const QString& aPlatformName)
{
  m_targetPlatform = aPlatformName;
  LALogger::Trace(LALogger::DEBUG, LALogger::MAIN, "New platform for document is " + aPlatformName, LA_DEBUG_ARGS);
}

/************************************************************* Public slots */
void LACATRE_Doc::beginAction(QString message)
{
	emit performingAction(message);
}

void LACATRE_Doc::endAction(QString message)
{
	emit actionPerformed(message);
}

void LACATRE_Doc::modified(LACATRE_Plugin * p)
{

  (void)p;

  LALogger::Trace(LALogger::DEBUG, LALogger::MAIN, "Document modified by the plugin " + QString().sprintf("%p", p), LA_DEBUG_ARGS);

}

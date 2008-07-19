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

/* LA4 includes */

/* Debugging levels */
#undef DEBUG

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
}

LACATRE_Doc::~LACATRE_Doc()
{
}

/*********************************************************** Public methods */
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

#ifdef DEBUG
	qDebug("LACATRE_Doc: Document %p modified by the plugin %p", (void *)this, (void *)p);
#endif /* DEBUG */

}

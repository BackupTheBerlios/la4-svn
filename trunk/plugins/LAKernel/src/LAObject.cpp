/******************************************************************************
 * LAObject.cpp                                                              *
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
 * Copyright (C) 2002-2006 by LA4 team <la4-dev@lists.berlios.de>             *
 ******************************************************************************/

#include "LAObject.h"

/* Qt includes */

/* LA4 includes */

/* Debugging levels */
#undef DEBUG
#undef XML_DEBUG

/************************************************** Constructors/Destructor */
/* Note: this constructor is protected */
LAObject::LAObject():
    QObject(),
    m_height(0),
    m_width(0),
    m_xCoordinate(0),
    m_yCoordinate(0)
{

#ifdef DEBUG
    qDebug("LAObject: %p constructed.", this);
#endif /* DEBUG */

}

/* Note: this constructor is protected */
LAObject::LAObject(const LAObject & s):
	QObject()
{
	
    /*! \todo Object ID is set to 0 when copying. */
    m_objectID    = 0;
    m_height      = s.m_height;
    m_width       = s.m_width;
    m_xCoordinate = s.m_xCoordinate;
    m_yCoordinate = s.m_yCoordinate;

#ifdef DEBUG
	qDebug("LAObject: %p constructed from a copy %p.", this, &s);
#endif /* DEBUG */

}

LAObject::~LAObject()
{
	
#ifdef DEBUG
	qDebug("LAObject: %p deleted.", this);
#endif /* DEBUG */

}

/*********************************************************** Public methods */

/******************************************************** Protected methods */

/******************************************************************************
 * LAMetaObject.cpp                                                           *
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

#include "LAMetaObject.h"

/* Qt includes */
#include <QtDebug>

/* LA4 includes */

/* Debugging levels */
#undef DEBUG
#define XML_DEBUG

/* XML constants */
const QString LAMetaObject::XML_MINIMUM_HEIGHT_ATTRIBUTE = "minimumHeight";
const QString LAMetaObject::XML_MINIMUM_WIDTH_ATTRIBUTE  = "minimumWidth";

/************************************************** Constructors/Destructor */
/* Note: this constructor is protected */
LAMetaObject::LAMetaObject(QDomNode& aNode)
{

#ifdef XML_DEBUG
  qDebug() << "LAMetaObject::LAMetaObject:Begin";
#endif /* XML_DEBUG */

	/* Convert node to element and work with that element */
	QDomElement element = aNode.toElement();

  /* Set width and height according to default values */
	m_minimumHeight = element.attribute(XML_MINIMUM_HEIGHT_ATTRIBUTE, "0").toFloat();
	m_minimumWidth  = element.attribute(XML_MINIMUM_WIDTH_ATTRIBUTE, "0").toFloat();

#ifdef XML_DEBUG
  qDebug() << "LAMetaObject::LAMetaObject: Minimum height =" << m_minimumHeight;
  qDebug() << "LAMetaObject::LAMetaObject: Minimum width  =" << m_minimumWidth;
#endif /* XML_DEBUG */

#ifdef XML_DEBUG
  qDebug() << "LAMetaObject::LAMetaObject:End";
#endif /* XML_DEBUG */

#ifdef DEBUG
    qDebug("LAMetaObject: %p constructed.", this);
#endif /* DEBUG */

}

LAMetaObject::~LAMetaObject()
{
	
#ifdef DEBUG
	qDebug("LAObject: %p deleted.", this);
#endif /* DEBUG */

}

/******************************************************** Protected methods */
double LAMetaObject::getMinimumHeight() const
{
  return m_minimumHeight;
}

double LAMetaObject::getMinimumWidth() const
{
  return m_minimumWidth;
}

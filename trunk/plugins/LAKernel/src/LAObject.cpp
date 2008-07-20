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
#include <QtDebug>

/* LA4 includes */

/* Debugging levels */
#undef DEBUG
#define XML_DEBUG

/* XML constants */
const QString LAObject::XML_DEFAULT_HEIGHT_ATTRIBUTE = "defaultHeight";
const QString LAObject::XML_DEFAULT_WIDTH_ATTRIBUTE  = "defaultWidth";
const QString LAObject::XML_TYPE_ID_ATTRIBUTE        = "typeID";

/************************************************** Constructors/Destructor */
/* Note: this constructor is protected */
LAObject::LAObject():
    QObject      (),
    m_height     (0),
    m_objectID   (0),
    m_typeID     (0),
    m_width      (0),
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
    m_typeID      = s.m_typeID;
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
LAObject* LAObject::Clone(double x, double y, double w, double h)
{
  (void)x;
  (void)y;
  (void)w;
  (void)h;

  qDebug() << "LAObject::Clone: NOT IMPLEMENTED";

  return NULL;
}

int LAObject::LoadDescription(QDomNode& aNode)
{

  /* Returned value */
  int success = 0;

#ifdef XML_DEBUG
  qDebug() << "LAObject::LoadDescription:Begin";
#endif /* XML_DEBUG */

	/* Convert node to element and work with that element */
	QDomElement element = aNode.toElement();

	/* ID is set to 0!!! */
	m_objectID = 0;

  /* Get type ID */
 	m_typeID  = element.attribute(XML_TYPE_ID_ATTRIBUTE, "-1").toInt();

#ifdef XML_DEBUG
  qDebug() << "LAObject::LoadDescription: Type ID        =" << m_typeID;
#endif /* XML_DEBUG */

  /* Set width and height according to default values */
	m_height = element.attribute(XML_DEFAULT_HEIGHT_ATTRIBUTE, "0").toFloat();
	m_width  = element.attribute(XML_DEFAULT_WIDTH_ATTRIBUTE, "0").toFloat();

#ifdef XML_DEBUG
  qDebug() << "LAObject::LoadDescription: Default height =" << m_height;
  qDebug() << "LAObject::LoadDescription: Default width  =" << m_width;
#endif /* XML_DEBUG */

#ifdef XML_DEBUG
  qDebug() << "LAObject::LoadDescription:End";
#endif /* XML_DEBUG */

  return success;
}

/******************************************************** Protected methods */

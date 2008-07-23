/******************************************************************************
 * LAMetaObject.h                                                             *
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

#ifndef _LAMETAOBJECT_H_
#define _LAMETAOBJECT_H_

/* Qt includes */
#include <QDomNode>
#include <QObject>

/* LA4 includes */

/* Forward declarations */

/*!
 * This class is used to represent all Lacatre objects except connectors
 */
class LAMetaObject : public QObject
{

	Q_OBJECT
  /****************************************************** Frient declarations */
public:
  friend class LAObject;

	/************************************************** Constructors/Destructor */
public:
	/*!
	 * Default constructor can not be used at all. It is not defined at all.
	 */

	/*!
	 * Destructor of LAMetaObject.
	 */
	~LAMetaObject();

	/*********************************************************** Public methods */
public:

	/******************************************************** Protected methods */
protected:
	/*!
	 * Default constructor. Not implemented.
	 */
	LAMetaObject();

	/*!
	 * Constructor of LAMetaObject to use.
	 */
	LAMetaObject(QDomNode& aNode);

  /*!
   * Returns the minimum height of the object
   */
  double getMinimumHeight() const;
	
  /*!
   * Returns the minimum width of the object
   */
  double getMinimumWidth() const;
	
	/******************************************************** Protected members */
protected:
	/*! Minimum height of the object */
	double m_minimumHeight;

	/*! Minimum width of the object */
	double m_minimumWidth;

	/******************************************************** Private constants */
private:
  /* Attribute names */
  static const QString XML_MINIMUM_HEIGHT_ATTRIBUTE;
  static const QString XML_MINIMUM_WIDTH_ATTRIBUTE;

};

#endif /* _LAMETAOBJECT_H_ */

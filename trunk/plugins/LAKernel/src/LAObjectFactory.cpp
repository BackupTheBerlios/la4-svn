/******************************************************************************
 * LAObjectFactory.cpp                                                        *
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

#include "LAObjectFactory.h"

/* Qt includes */

/* LA4 includes */
#include "LAObjectFactoryManager.h"
#include "LAObject.h"

/* Other includes */

/* Debugging levels */
#undef DEBUG
#undef XML_DEBUG

/* Static next ID value */
int LAObjectFactory::M_nextID;

/************************************************** Constructors/Destructor */
LAObjectFactory::LAObjectFactory(LAObjectFactoryManager* aFactoryManager):
    QObject(aFactoryManager)
{
    m_factoryObject = NULL;
    M_nextID = 1;
}

LAObjectFactory::~LAObjectFactory()
{

    if (m_factoryObject)
        {
            delete m_factoryObject;
        }

}

/*********************************************************** Public methods */
QString LAObjectFactory::getName() const
{
    return m_name;
}

int LAObjectFactory::getTypeID() 
{
    Q_ASSERT(m_factoryObject); 
    return 0/*m_factoryObject->getTypeID()*/;
}

int LAObjectFactory::LoadDescription(const QString & aFactoryDirectory,
                                     const QString & aFactoryFile)
{

    (void)aFactoryDirectory;
    (void)aFactoryFile;

// 	QFile file(factDir + "/" + factFile);

// 	if (file.exists() && file.open(IO_ReadOnly))
// 		{
// 			/* Load and parse the object description file */
// 			QDomDocument doc;
// 			doc.setContent(&file);

// 			QDomElement object = doc.documentElement();
// 			QDomNodeList objectChildren = object.childNodes();

// #ifdef XML_DEBUG
// 			qDebug("LAObjectFactory: document has %d childrens.", objectChildren.count());
// #endif /* XML_DEBUG */

// 			/* Load the attributes of the object factory */
// 			for(QDomNode n = object.firstChild() ; !n.isNull() ; n = n.nextSibling())
// 				{

// #ifdef XML_DEBUG
// 					qDebug("LAObjectFactory: met tag " + n.nodeName());
// #endif /* XML_DEBUG */

// 					/* We find the french description of the factory in the DOM tree
// 					 * and set it as factory name */
// 					/*! \todo Why french??? Change to ID! */
// 					if ((n.nodeName() == "description")
// 							&& (n.toElement().attribute("lang") == "fr"))
// 						{

// #ifdef XML_DEBUG
// 							qDebug("LAObjectFactory: Description found: " + n.toElement().text());
// #endif /* XML_DEBUG */

// 							name = n.toElement().text();
// 						}

// 					/* Find the path of the factory's icon to include in the palette and create the icon. */
// 					QString iconFile;
// 					if (n.toElement().tagName() == "icon")
// 						{
// 							iconFile = n.toElement().text();

// #ifdef XML_DEBUG
// 							qDebug("LAObjectFactory: trying to create an icon from file '%s'.", iconFile.latin1());
// #endif /* XML_DEBUG */

// 							icon = new QPixmap(factDir + "/icons/" + iconFile);

// 							if (icon->isNull())
// 								{

// #ifdef XML_DEBUG
// 									qDebug("LAObjectFactory: the file '%s' is an invalid icon file.", iconFile.latin1());
// #endif /* XML_DEBUG */

// 									delete icon;
// 									icon = NULL;
// 								}
// 						}

// 				}

// 			/* Create a default icon if no valid one has been found */
// 			if (!icon)
// 				{

// #ifdef XML_DEBUG
// 					qDebug("LAObjectFactory: No icon loaded. Creating a default one.");
// #endif /* XML_DEBUG */
// 					icon = new QPixmap(object_xpm);
// 				}


// 			/* Check if the file is OK. */
// 			/* \todo Implement file check */
// 			if (true)
// 				{

// #ifdef DEBUG
// 					qDebug("LAObjectFactory: '%s' : loading the object.", name.latin1());
// #endif /* DEBUG */

// 					/* Looking for the node with description of the object */
// 					QDomElement n = doc.documentElement();

// 					/* Creation of appropriate object object (CObject or PObject) */
// 					if (n.nodeName() == "objectConfigObject")
// 						{
// 							factoryObject = new LAObjectObject(this);
// 						}
// 					else
// 						{
// 							if (n.attribute("child", "false") == "false")
// 								{
// 									factoryObject = new LAObjectPObject(this);
// 								}
// 							else
// 								{
// 									factoryObject = new LAObjectPChild(this);
// 								}
// 						}

// 					/* Load object and return result */
// 					int result = factoryObject->LoadDescription(n);
// 					return result;

// 				}
// 			else
// 				{
// 					qWarning("LAObjectFactory %s: Check of factory description FAILED. Please check your XML definitions.", name.latin1());
// 					return -1;
// 				}
// 		}

    /* If here, there has been an error */
    return -1;

}

LAObject* LAObjectFactory::NewInstance(double x, double y, double w , double h)
{

    LAObject * r = (LAObject *)(m_factoryObject->Clone(x, y, w, h));
    //    r->setObjectID(TakeNextID());

    return r;

}

LAObject * LAObjectFactory::NewInstance(const QDomElement& root)
{

    double x = root.attribute("x").toDouble();
    double y = root.attribute("y").toDouble();
    double w = root.attribute("w").toDouble();
    double h = root.attribute("h").toDouble();
//     int ID   = root.attribute("ID").toInt();

    LAObject * r = (LAObject *)(m_factoryObject->Clone(x, y, w, h));
//     r->setObjectID(TakeNextID(ID));

    return r;

}

/**************************************************** Public static methods */
int LAObjectFactory::TakeNextID(int ID)
{

    if (ID < 0)
        {
            ID = M_nextID;
        }
    if (ID >= M_nextID)
        {
            M_nextID = ID;
        }

    /* Only increment if nextID will be returned */
    if (ID == M_nextID)
        {
            M_nextID++;
        }

    return ID;

}

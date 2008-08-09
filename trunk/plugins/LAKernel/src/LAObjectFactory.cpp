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
#include <QDomDocument>
#include <QFile>

/* LA4 includes */
#include "LALogger.h"
#include "LAPlatform.h"
#include "LAObject.h"

/* Other includes */

/* Static next ID value */
int LAObjectFactory::M_nextID = 1;

/************************************************** Constructors/Destructor */
LAObjectFactory::LAObjectFactory(LAPlatform* aPlatform):
  QObject          (aPlatform),
  m_factoryObject  (NULL)
{
  LALogger::TraceConstructor(LA_DEBUG_ARGS);
}

LAObjectFactory::~LAObjectFactory()
{

  if (m_factoryObject)
    {
      delete m_factoryObject;
    }

  LALogger::TraceDestructor(LA_DEBUG_ARGS);
}

/*********************************************************** Public methods */
QString LAObjectFactory::getName() const
{
  return m_name;
}

int LAObjectFactory::getTypeID() 
{
  Q_ASSERT(m_factoryObject); 
  return m_factoryObject->getTypeID();
}

int LAObjectFactory::LoadDescription(const QString & aFactoryDirectory,
                                     const QString & aFactoryFilename)
{
  LALogger::TraceBeginMethod(LA_DEBUG_ARGS);

  /* Returned value */
  int result = -1;

  QFile factoryFile(aFactoryDirectory + "/" + aFactoryFilename);

  if (factoryFile.exists() && factoryFile.open(QIODevice::ReadOnly))
    {
      /* Load and parse the object description file */
      QDomDocument objectDocument;
      objectDocument.setContent(&factoryFile);

      /* Check if the file is OK. */
      /* @todo Implement file check */
      if (true)
        {

          LALogger::Trace(LALogger::DEBUG, LALogger::MAIN, "LAObjectFactory::LoadDescription: Loading factory from file " + factoryFile.fileName(), LA_DEBUG_ARGS);

          /* Looking for the node with description of the object */
          QDomElement rootNode = objectDocument.documentElement();

          /* Create object */
          m_factoryObject = new LAObject();

          /* Load object */
          result = m_factoryObject->LoadDescription(rootNode);
        }
      else
        {
          LALogger::Trace(LALogger::ERROR,
                          LALogger::MAIN,
                          "LAObjectFactory::LoadDescription:"
                            + factoryFile.fileName()
                            + "Check of factory description FAILED. Please check your XML definitions.",
                          LA_DEBUG_ARGS);
        }

     }

  LALogger::TraceEndMethod(LA_DEBUG_ARGS);
  /* Return the result */
  return result;
}

LAObject* LAObjectFactory::NewInstance(double x, double y, double w , double h)
{

  LAObject * r = (LAObject *)(m_factoryObject->Clone(x, y, w, h));
  //    r->setObjectID(TakeNextID());

  return r;
}

LAObject * LAObjectFactory::NewInstance(const QDomElement& root)
{
  LALogger::TraceBeginMethod(LA_DEBUG_ARGS);

  double x = root.attribute("x").toDouble();
  double y = root.attribute("y").toDouble();
  double w = root.attribute("w").toDouble();
  double h = root.attribute("h").toDouble();
//     int ID   = root.attribute("ID").toInt();

  LAObject * r = (LAObject *)(m_factoryObject->Clone(x, y, w, h));
//     r->setObjectID(TakeNextID(ID));

  LALogger::TraceEndMethod(LA_DEBUG_ARGS);
  return r;
}

/**************************************************** Public static methods */
int LAObjectFactory::TakeNextID(int aID)
{
  LALogger::TraceBeginMethod(LA_DEBUG_STATIC_ARGS);

  if (aID < 0)
    {
      aID = M_nextID;
    }
  if (aID >= M_nextID)
    {
      M_nextID = aID;
    }

  /* Only increment if nextID will be returned */
  if (aID == M_nextID)
    {
      M_nextID++;
    }

  LALogger::TraceEndMethod(LA_DEBUG_STATIC_ARGS);
  return aID;
}

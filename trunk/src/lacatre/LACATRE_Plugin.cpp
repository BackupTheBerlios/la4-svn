/******************************************************************************
 * LACATRE_Plugin.cpp                                                         *
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

#include "LACATRE_Plugin.h"
 
/* Qt includes */
 
/* LA4 includes */
#include "LALogger.h"
 
/************************************************** Constructors/Destructor */
LACATRE_Plugin::LACATRE_Plugin(LACATRE_PluginPool::PluginType type,
                               QString name,
                               QString d) :
  QObject(NULL)
{
  LACATRE_PluginPool::getInstance()->registerPlugin(this, type, name, d);
}

LACATRE_Plugin::~LACATRE_Plugin()
{
	/* There is nothing to destroy */
}

LACATRE_Plugin::LACATRE_Plugin(const LACATRE_Plugin& aPlugin, LACATRE_Doc* aDocument) :
  QObject(),
  m_doc(aDocument)
{
  /* We do not copy anything from the originating plugin */
  (void)aPlugin;

  LALogger::Trace(LALogger::DEBUG,
                  LALogger::MAIN,
                  QString().sprintf("Copying plugin %p", &aPlugin),
                  LA_DEBUG_ARGS);

  /* Connect the modified signals correctly */
  QObject::connect(this,
                   SIGNAL(modified(LACATRE_Plugin*)),
                   m_doc,
                   SLOT(modified(LACATRE_Plugin*)));
}

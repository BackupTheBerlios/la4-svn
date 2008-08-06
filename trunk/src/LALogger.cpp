/******************************************************************************
 * LALogger.cpp                                                               *
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

#include "LALogger.h"

/* Standard includes */
#include <stdio.h>

/* Qt includes */
#include <QtDebug>

/* LA4 includes */

/************************************************** Constructors/Destructor */
/*! Constructors and destructor are not defined because */
/*  they should not be used at all                      */

/*********************************************************** Public methods */
void LALogger::Log(int     aLevel,
                   int     aCategory,
                   QString aMessage,
                   QString aFilename,
                   int     aLineNumber)
{

  bool toLog       = false;
  QString level    = "";
  QString category = "";

  switch (aLevel)
    {
    case DEBUG:
      level = "DEBG";
      toLog = true;
      break;
    case WARNING:
      level = "WARN";
      toLog = true;
      break;
    case ERROR:
      level = "ERR ";
      toLog = true;
      break;
    case INFO:
    default:
      level = "INFO";
      toLog = true;
      break;
    }
  
  switch (aCategory)
    {
    case MAIN:
      category = "MAIN";
      toLog = true;
      break;
    case XML:
      category = "XML ";
      toLog = true;
      break;
    case MEMORY:
      category = "MEM ";
      toLog = true;
      break;
    case METHOD:
      category = "METH";
      toLog = true;
      break;
    default:
      category = "UNKN";
      toLog = true;
      break;
    }

  if (toLog)
    {
      LogMessage(level, category, aMessage, aFilename, aLineNumber);
    }

}

/********************************************************** Private methods */
void LALogger::LogMessage(QString aLevel,
                          QString aCategory,
                          QString aMessage,
                          QString aFilename,
                          int     aLineNumber)
{

  QString message = "[" + aLevel + "]";
  message += " ==" + aCategory + "== ";
  message += aFilename + ":" + QString().sprintf("%04d", aLineNumber) + ": ";
  message += aMessage;
  qDebug(message.toAscii());
}

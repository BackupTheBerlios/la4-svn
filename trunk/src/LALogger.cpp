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

/* Qt includes */
#include <QtDebug>

/* LA4 includes */

/************************************************** Constructors/Destructor */
/*! Constructors and destructor are not defined because */
/*  they should not be used at all                      */

/*********************************************************** Public methods */
void LALogger::Trace(int         aLevel,
                     int         aCategory,
                     QString     aMessage,
                     void*       aInstance,
                     const char* aFunction,
                     const char* aFilename,
                     int         aLineNumber)
{
  Log(aLevel,
      aCategory,
      QString().sprintf("%p +++ %s(): ", aInstance, aFunction) + aMessage,
      aFilename,
      aLineNumber);
}

void LALogger::Trace(int         aLevel,
                     int         aCategory,
                     QString     aMessage,
                     const char* aFunction,
                     const char* aFilename,
                     int         aLineNumber)
{
  Log(aLevel,
      aCategory,
      QString().sprintf("STATIC +++ %s(): ", aFunction) + aMessage,
      aFilename,
      aLineNumber);
}

void LALogger::TraceBeginMethod(void*       aInstance,
                                const char* aFunction,
                                const char* aFilename,
                                int         aLineNumber)
{
  Log(LALogger::DEBUG,
      LALogger::METHOD,
      QString().sprintf("%p >>> %s()", aInstance, aFunction),
      aFilename,
      aLineNumber);
}

void LALogger::TraceBeginMethod(const char* aFunction,
                                const char* aFilename,
                                int         aLineNumber)
{
  Log(LALogger::DEBUG,
      LALogger::METHOD,
      QString().sprintf("STATIC >>> %s()", aFunction),
      aFilename,
      aLineNumber);
}

void LALogger::TraceConstructor(void*       aInstance,
                                const char* aFunction,
                                const char* aFilename,
                                int         aLineNumber)
{
  (void)aFunction; // We do not use the constructor's name for now
  Log(LALogger::DEBUG,
      LALogger::MEMORY,
      QString().sprintf("%p created", aInstance),
      aFilename,
      aLineNumber);
}

void LALogger::TraceDestructor(void*       aInstance,
                               const char* aFunction,
                               const char* aFilename,
                               int         aLineNumber)
{
  (void)aFunction; // We do not use the destructor's name for now
  Log(LALogger::DEBUG,
      LALogger::MEMORY,
      QString().sprintf("%p deleted", aInstance),
      aFilename,
      aLineNumber);
}

void LALogger::TraceEndMethod(void*       aInstance,
                              const char* aFunction,
                              const char* aFilename,
                              int         aLineNumber)
{
  Log(LALogger::DEBUG,
      LALogger::METHOD,
      QString().sprintf("%p <<< %s()", aInstance, aFunction),
      aFilename,
      aLineNumber);
}

void LALogger::TraceEndMethod(const char* aFunction,
                              const char* aFilename,
                              int         aLineNumber)
{
  Log(LALogger::DEBUG,
      LALogger::METHOD,
      QString().sprintf("STATIC <<< %s()", aFunction),
      aFilename,
      aLineNumber);
}

/********************************************************** Private methods */
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
      QString message = "[" + level + "]";
      message += " ==" + category + "== ";
      message += aMessage;
      message += " (" + aFilename + ":" + QString().sprintf("%d", aLineNumber) + ")";
      qDebug(message.toAscii());
    }

}

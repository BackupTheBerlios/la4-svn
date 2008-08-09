/******************************************************************************
 * LALogger.h                                                                 *
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

#ifndef LA_LOGGER_H_
#define LA_LOGGER_H_

/* Qt include */
#include <QString>

/* Macros */
/* Parameters */
#define LA_DEBUG_ARGS this, __func__, __FILE__, __LINE__
#define LA_DEBUG_STATIC_ARGS __func__, __FILE__, __LINE__

/* Traces */
//#define LA_DEBUG(a); LALogger::Log(LALogger::DEBUG, LALogger::MAIN, QString().sprintf("%p +++ %s(): %s", this, __func__, a), __FILE__, __LINE__);
//#define LA_DEBUG_2(a, b); LALogger::Log(LALogger::DEBUG, LALogger::MAIN, QString().sprintf("%p +++ %s(): %s", this, __func__, a).arg(b), __FILE__, __LINE__);
//#define LA_DEBUG_3(a, b, c); LALogger::Log(LALogger::DEBUG, LALogger::MAIN, QString().sprintf("%p +++ %s(): %s", this, __func__, a).arg(b).arg(c), __FILE__, __LINE__);

//#define LA_STATIC_DEBUG(a); LALogger::Log(LALogger::DEBUG, LALogger::MAIN, QString().sprintf("STATIC   +++ %s(): %s", __func__, a), __FILE__, __LINE__);
//#define LA_STATIC_DEBUG_2(a, b); LALogger::Log(LALogger::DEBUG, LALogger::MAIN, QString().sprintf("STATIC   +++ %s(): %s", __func__, a).arg(b), __FILE__, __LINE__);
//#define LA_STATIC_DEBUG_3(a, b, c); LALogger::Log(LALogger::DEBUG, LALogger::MAIN, QString().sprintf("STATIC   +++ %s(): %s", __func__, a).arg(b).arg(c), __FILE__, __LINE__);

/*!
 * This class is responsible of the logging of all messages of
 * the application.
 */

class LALogger
{
  /************************************************************* Public types */
public:
  /*!
   * Level
   */
  typedef enum {
    INFO,             /* INFO messages */
    WARNING,          /* WARNING messages */
    ERROR,            /* ERROR messages */
    DEBUG             /* DEBUG messages */
  } LALogLevel;

  /*!
   * Categories
   */
  typedef enum {
    MAIN,              /* Main category */
    XML,               /* XML category */
    METHOD,            /* Debug for method calls */
    MEMORY             /* Debug for memory */
  } LALogCategory;

  /************************************************** Constructors/Destructor */
private:
  /*!
   * Default constructor: not provided
   *
   * Does nothing
   */
  LALogger();

  /*!
   * Destructor
   */
  ~LALogger();

  /*********************************************************** Public methods */
public:
  /*!
   * Trace a message in the given category with the given level
   */
  static void Trace(int aLevel, int aCategory, QString aMessage, void* aInstance, const char* aFunction, const char* aFilename, int aLineNumber);

  /*!
   * Trace a message in the given category with the given level (for static methods)
   */
  static void Trace(int aLevel, int aCategory, QString aMessage, const char* aFunction, const char* aFilename, int aLineNumber);

  /*!
   * Log a method use
   */
  static void TraceBeginMethod(void* aInstance, const char* aFunction, const char* aFilename, int aLineNumber);

  /*!
   * Log a method use (for static methods)
   */
  static void TraceBeginMethod(const char* aFunction, const char* aFilename, int aLineNumber);

  /*!
   * Log a constructor call
   */
  static void TraceConstructor(void* aInstance, const char* aFunction, const char* aFilename, int aLineNumber);

  /*!
   * Log a destructor call
   */
  static void TraceDestructor(void* aInstance, const char* aFunction, const char* aFilename, int aLineNumber);

  /*!
   * Log a method use
   */
  static void TraceEndMethod(void* aInstance, const char* aFunction, const char* aFilename, int aLineNumber);

  /*!
   * Log a method use (for static methods)
   */
  static void TraceEndMethod(const char* aFunction, const char* aFilename, int aLineNumber);

  /********************************************************** Private methods */
private:
  /*!
   * Log a message at the given level in the given category.
   *
   * This method only handles the level and category handling.
   */
  static void Log(int aLevel, int aCategory, QString aMessage, QString aFilename, int aLineNumber);

};

#endif /* LA_LOGGER_H_ */

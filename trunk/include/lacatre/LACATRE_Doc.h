/******************************************************************************
 * LACATRE_Doc.h                                                              *
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
 * Copyright (C) 2002-2007 by LA4 team <la4-dev@lists.berlios.de>             *
 ******************************************************************************/

#ifndef LACATRE_DOC_H_
#define LACATRE_DOC_H_

/* Qt includes */
#include <QObject>

/* LA4 includes */
#include "LACATRE_Plugin.h"

/* Forward declaration */
class LACATRE_Plugin;

/*!
 * LACATRE_Doc holds the internal representation of a LACATRE document.
 * 
 * It does not contain any semantics associated to the content of
 * the document. It only contains the XML data, knows the associated
 * platform, the title of the document.
 * 
 * The role of this class is to handle the file of a document, parse
 * it. The interpretation of the data is provided by other classes
 */
class LACATRE_Doc : public QObject
{
	Q_OBJECT
		
  	/************************************************** Constructors/Destructor */
public :
	/*!
	 * Default constructor.
	 *
	 * \param parent_ Parent of the document (passed to QObject's constructor)
	 */
	LACATRE_Doc(QObject * parent = 0);

	/*!
	 * Default destructor
	 */
	~LACATRE_Doc();
	
  	/****************************************************************** Signals */
signals:
	/*!
	 * This signal informs when an action has been performed by a plugin
	 */
	void actionPerformed(QString message);

	/*!
	 * This signal is fired when a plugin has modified the tree in order 
	 * to inform others plugins about it.
	 */
	void invalidated(LACATRE_Doc &);

	/*!
	 * This signal informs when an action is being performed by a plugin
	 */
	void performingAction(QString message);

	/*********************************************************** Public methods */
public:
  /*!
   * Sets the filenameof the document
   */
	void setDocumentFileName(const QString& aDocumentFilename);

  /*!
   * Sets the platform of the document
   */
	void setTargetPlatform(const QString& aPlatformName);

	/************************************************************* Public slots */
public slots:
	/*!
	 * This slot must be activated by a plugin to allow a global information
	 * about what is being performed on the document.
	 * 
	 * TODO Enhance this mechanism if needed to allow a precise recognition of the action
	 * 
	 */
	void beginAction(QString message);

	/*!
	 * This slot must be activated by a plugin to allow a global information
	 * about the fact that an action has been performed on the document.
	 */
	void endAction(QString message);

	/*!
	 * This slot must be called by a plugin if it modified the content 
	 * of its copy of the document. The XML tree will NOT get updated
	 * until someone else requests it (efficiency!).
	 *
	 * In order to preserve document consistency, it IS very important
	 * that each plugin handles the invalidated signal correctly. 
	 * 
	 * \param plugin_ Plugin that has modified the document
	 */
	void modified(LACATRE_Plugin * plugin_);

	/******************************************************** Protected methods */
protected:

  	/********************************************************** Protected slots */
protected slots:

	/******************************************************** Protected members */
protected:

	/********************************************************** Private members */
private:
  /*! Filename of the document */
	QString m_documentFilename;

  /*! Target platform of the document */
	QString m_targetPlatform;
};

#endif /* LACATRE_DOC_H_ */

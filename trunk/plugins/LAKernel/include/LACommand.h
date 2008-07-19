/******************************************************************************
 * LACommand.h                                                                *
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

#ifndef _LACOMMAND_H_
#define _LACOMMAND_H_

/* Qt includes */
#include <QUndoCommand>

/*!
 * LACommand holds a command executed on the document.
 *
 * This class is used to implement a command pattern. The command
 * pattern will for example be used for the undo implementation.
 */
class LACommand : public QUndoCommand
{

    /************************************************ Constructors/Destructor */
public:
    /*!
     * Default constructor
     *
     * \param parent_ Parent of the document (passed to QObject's constructor)
     */
    LACommand(QUndoCommand* parent = 0);

    /*!
     * Default destructor
     */
    ~LACommand();

    /********************************************************* Public methods */
public:
    /*!
     * Returns the command ID
     */
    int getCommandId();

    /*!
     * Sets a new command ID
     *
     * @param aCommandId   New command ID
     */
    void setCommandId(const int aCommandId);

    /****************************************************** Protected methods */
protected:

    /******************************************************** Private members */
private:
    /*! Command ID of the action */
    int m_commandId;

};

#endif /* _LACOMMAND_H_ */

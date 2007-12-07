/****************************************************************
 *  Vidalia is distributed under the following license:
 *
 *  Copyright (C) 2006,  Matt Edman, Justin Hipple
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; either version 2
 *  of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, 
 *  Boston, MA  02110-1301, USA.
 ****************************************************************/

/** 
 * \file controlsocket.h
 * \version $Id$
 * \brief Socket used to connect to Tor's control interface
 */

#ifndef _CONTROLSOCKET_H
#define _CONTROLSOCKET_H

#include <QTcpSocket>

#include "controlcommand.h"
#include "controlreply.h"


class ControlSocket : public QTcpSocket
{
  Q_OBJECT

public:
  /** Default constructor. */
  ControlSocket();

  /** Send a command to Tor */
  bool sendCommand(ControlCommand cmd, QString *errmsg = 0);
  /** Read a response from Tor */
  bool readReply(ControlReply &reply, QString *errmsg = 0);

  /** Returns true if the control socket is connected and ready to send or
   * receive. */
  bool isConnected();
  
  /** Returns the string description of <b>error</b>. */
  static QString toString(const QAbstractSocket::SocketError error);
  
protected:
  /** Reads line data off the socket in chunks. */
  bool readLineData(QString &line, QString *errmsg = 0);
  /** Reads a line of data from the socket (blocking) */
  bool readLine(QString &line, QString *errmsg = 0);
};

#endif

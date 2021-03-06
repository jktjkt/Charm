/*
  X11IdleDetector.cpp

  This file is part of Charm, a task-based time tracking application.

  Copyright (C) 2008-2016 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com

  Author: Jesper Pedersen <jesper.pedersen@kdab.com>
  Author: Frank Osterfeld <frank.osterfeld@kdab.com>
  Author: Mirko Boehm <mirko.boehm@kdab.com>
  Author: Mike McQuaid <mike.mcquaid@kdab.com>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "X11IdleDetector.h"
#include "CharmCMake.h"

#if QT_VERSION < QT_VERSION_CHECK(5,0,0)
#include <QX11Info>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/scrnsaver.h>
#else
#include <xcb/screensaver.h>
#endif

X11IdleDetector::X11IdleDetector( QObject* parent )
    : IdleDetector( parent )
{
    connect( &m_timer, SIGNAL(timeout()), this, SLOT(checkIdleness()) );
    m_timer.start( idlenessDuration() * 1000 / 5 );
    m_heartbeat = QDateTime::currentDateTime();
}

bool X11IdleDetector::idleCheckPossible()
{
#if QT_VERSION < QT_VERSION_CHECK(5,0,0)
    int event_base, error_base;
    if(XScreenSaverQueryExtension(QX11Info::display(), &event_base, &error_base))
        return true;
#else
    m_connection = xcb_connect(NULL, NULL); //krazy:exclude=null
    m_screen = xcb_setup_roots_iterator(xcb_get_setup (m_connection)).data;
    if (m_screen)
        return true;
#endif
    return false;
}

void X11IdleDetector::onIdlenessDurationChanged()
{
    m_timer.stop();
    m_timer.start( idlenessDuration() * 1000 / 5 );
}

void X11IdleDetector::checkIdleness()
{
#if QT_VERSION < QT_VERSION_CHECK(5,0,0)
    XScreenSaverInfo* _mit_info = XScreenSaverAllocInfo();
    if (!_mit_info)
        return;
    XScreenSaverQueryInfo(QX11Info::display(), QX11Info::appRootWindow(), _mit_info);
    const int idleSecs = _mit_info->idle / 1000;
    XFree(_mit_info);
#else
    xcb_screensaver_query_info_cookie_t cookie;
    cookie = xcb_screensaver_query_info( m_connection, m_screen->root );
    xcb_screensaver_query_info_reply_t* info;
    info = xcb_screensaver_query_info_reply( m_connection, cookie, NULL );  //krazy:exclude=null
    const int idleSecs = info->ms_since_user_input / 1000;
    free (info);
#endif

    if (idleSecs >= idlenessDuration())
        maybeIdle( IdlePeriod(QDateTime::currentDateTime().addSecs( -idleSecs ),
                              QDateTime::currentDateTime() ) );

    if ( m_heartbeat.secsTo( QDateTime::currentDateTime() ) > idlenessDuration() )
        maybeIdle( IdlePeriod( m_heartbeat, QDateTime::currentDateTime() ) );

    m_heartbeat = QDateTime::currentDateTime();
}

#include "moc_X11IdleDetector.cpp"

/*-
 * Copyright (c) 2012 Caoimhe Chaos <caoimhechaos@protonmail.com>,
 *                    Ancient Solutions. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions  of source code must retain  the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions  in   binary  form  must   reproduce  the  above
 *    copyright  notice, this  list  of conditions  and the  following
 *    disclaimer in the  documentation and/or other materials provided
 *    with the distribution.
 *
 * THIS  SOFTWARE IS  PROVIDED BY  ANCIENT SOLUTIONS  AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO,  THE IMPLIED WARRANTIES OF  MERCHANTABILITY AND FITNESS
 * FOR A  PARTICULAR PURPOSE  ARE DISCLAIMED.  IN  NO EVENT  SHALL THE
 * FOUNDATION  OR CONTRIBUTORS  BE  LIABLE FOR  ANY DIRECT,  INDIRECT,
 * INCIDENTAL,   SPECIAL,    EXEMPLARY,   OR   CONSEQUENTIAL   DAMAGES
 * (INCLUDING, BUT NOT LIMITED  TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE,  DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT  LIABILITY,  OR  TORT  (INCLUDING NEGLIGENCE  OR  OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#ifdef HAVE_QTCORE_QFILE
#include <QtCore/QDateTime>
#include <QtCore/QFileInfo>
#include <QtCore/QThread>
#include <QtCore/QUrl>

#include <glog/logging.h>

#ifdef HAVE_SYS_INOTIFY_H
#include <sys/inotify.h>
#endif /* HAVE_SYS_INOTIFY_H */
#include <unistd.h>

#ifndef EVENT_SIZE
#define EVENT_SIZE sizeof(struct inotify_event)
#endif /* EVENT_SIZE */
#ifndef EVENT_BUF_LEN
#define EVENT_BUF_LEN EVENT_SIZE + NAME_MAX + 1
#endif /* EVENT_BUF_LEN */

#include "QUrlFileWatcher.h"

namespace toolbox
{
namespace io
{

class QFileFileWatcher : public QThread
{
	Q_OBJECT

public:
	QFileFileWatcher(QUrl url, QUrlFileWatcherNotificationReceiver* cb);
	virtual ~QFileFileWatcher();

protected:
	void run();
	void Notify();

	QFile file_;
	QFileInfo file_info_;
	QUrlFileWatcherNotificationReceiver* cb_;

#ifdef HAVE_SYS_INOTIFY_H
	const int inotify_handle_;
	int file_handle_;
#endif /* HAVE_SYS_INOTIFY_H */
};

#ifdef HAVE_SYS_INOTIFY_H
QFileFileWatcher::QFileFileWatcher(QUrl url,
		QUrlFileWatcherNotificationReceiver* cb)
: file_(url.path()), file_info_(url.path()), cb_(cb),
	inotify_handle_(inotify_init())
{
	file_handle_ = inotify_add_watch(inotify_handle_,
			url.path().toStdString().data(),
			IN_CLOSE_WRITE);
}

QFileFileWatcher::~QFileFileWatcher()
{
	inotify_rm_watch(inotify_handle_, file_handle_);
	close(inotify_handle_);
}

void
QFileFileWatcher::run()
{
	char buffer[EVENT_BUF_LEN];
	ssize_t length, i = 0;

	LOG(INFO) << "Listening for inotify events";

	for (;;)
	{
		length = read(inotify_handle_, buffer, EVENT_BUF_LEN);
		if (length < 0)
			return;

		while (i < length)
		{
			struct inotify_event *event =
				( struct inotify_event * ) &buffer[i];
			if (event->len) {
				if (event->wd == file_handle_)
					Notify();
			}

			i += EVENT_SIZE + event->len;
		}

		memset(buffer, 0, EVENT_BUF_LEN);
		i = 0;
	}
}

void
QFileFileWatcher::Notify()
{
	if (!file_.open(QIODevice::ReadOnly))
		return;

	QByteArray data = file_.readAll();
	file_.close();

	file_info_.refresh();

	cb_->Receive(file_info_.lastModified().toTime_t(), data);
}
#endif /* HAVE_SYS_INOTIFY_H */

QUrlFileWatcher::QUrlFileWatcher(QUrl url,
		QUrlFileWatcherNotificationReceiver* cb)
: cb_(cb)
{
	if (url.scheme() == "file")
	{
		listener_.reset(new QFileFileWatcher(url, cb));
		listener_->start();
	}
}

QUrlFileWatcher::~QUrlFileWatcher()
{
	if (!listener_.isNull())
		listener_->terminate();
}

}  // namespace io
}  // namespace toolbox

#include "QUrlFileWatcher.moc"

#endif /* HAVE_QTCORE_QFILE */

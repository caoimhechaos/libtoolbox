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

#ifndef TOOLBOX_IO_QURLFILEWATCHER_H
#define TOOLBOX_IO_QURLFILEWATCHER_H 1

#include <QtCore/QByteArray>
#include <QtCore/QScopedPointer>
#include <QtCore/QUrl>

namespace toolbox
{
namespace io
{
class QUrlFileWatcherNotificationReceiver
{
public:
	virtual void Receive(int64_t revision, const QByteArray& data) = 0;
};

class QUrlFileWatcher
{
public:
	// Watches the file referenced by "url".
	// Sets the callback to call when new versions of the file have
	// become available to "cb". Takes ownership of "cb".
	// "cb" will be called with an increasing version counter equivalent
	// and the new file contents as parameters.
	QUrlFileWatcher(QUrl url, QUrlFileWatcherNotificationReceiver* cb);

	// Stops watching the file.
	virtual ~QUrlFileWatcher();

protected:
	QScopedPointer<QUrlFileWatcherNotificationReceiver> cb_;
	QScopedPointer<QThread> listener_;
};

}  // namespace io
}  // namespace toolbox

#endif /* TOOLBOX_IO_QURLFILEWATCHER_H */

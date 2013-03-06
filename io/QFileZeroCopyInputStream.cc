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
#endif

#ifdef HAVE_QTCORE_QFILE
#include "QFileZeroCopyInputStream.h"
#include <QtCore/QFile>
#include <zlib.h>

#define	QFILEINPUTSTREAM	65536

namespace toolbox
{
namespace io
{

QFileZeroCopyInputStream::QFileZeroCopyInputStream(QFile* filesource)
: file_(filesource), crc32_(crc32(0L, Z_NULL, 0))
{
	if (!file_->isOpen())
		file_->open(QIODevice::ReadOnly);
}

QFileZeroCopyInputStream::~QFileZeroCopyInputStream()
{
	if (file_->isOpen())
		file_->close();
}

bool
QFileZeroCopyInputStream::Next(const void** data, int* size)
{
	qint64 bytes_read;
	QScopedPointer<char> buf(new char[QFILEINPUTSTREAM]);

	bytes_read = file_->read(buf.data(), QFILEINPUTSTREAM);
	if (bytes_read <= 0)
	{
		*size = 0;
		return false;
	}
	else
	{
		*data = buf.take();
		*size = bytes_read;
		crc32_ = crc32(crc32_, (unsigned char*) buf.data(),
				bytes_read);
		return true;
	}
}

void
QFileZeroCopyInputStream::BackUp(int count)
{
	if (count > file_->pos())
		file_->seek(0);
	else
		file_->seek(file_->pos() - count);
}

bool
QFileZeroCopyInputStream::Skip(int count)
{
	if (file_->pos() + count > file_->size())
		return file_->seek(file_->size());
	else
		return file_->seek(file_->pos() + count);
}

google::protobuf::int64
QFileZeroCopyInputStream::ByteCount() const
{
	return file_->pos();
}

uint32_t
QFileZeroCopyInputStream::Checksum() const
{
	return crc32_;
}

}  // namespace io
}  // namespace toolbox

#endif /* HAVE_QTCORE_QFILE */

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

#ifndef TOOLBOX_IO_QFILEZEROCOPYINPUTSTREAM_H
#define TOOLBOX_IO_QFILEZEROCOPYINPUTSTREAM_H 1

#include <google/protobuf/io/zero_copy_stream.h>
#include <QtCore/QtCore>

class QFile;

namespace toolbox
{
namespace io
{

class QFileZeroCopyInputStream :
	public google::protobuf::io::ZeroCopyInputStream
{
public:
	// Create a new ZeroCopyInputStream for the file "filesource".
	QFileZeroCopyInputStream(QFile* filesource);
	virtual ~QFileZeroCopyInputStream();

	// Obtain a chunk of data from the file.
	virtual bool Next(const void** data, int* size);

	// Backs up "count" bytes so that the next call to Next() will return
	// them again.
	virtual void BackUp(int count);

	// Skip ahead "count" bytes.
	virtual bool Skip(int count);

	// Returns the total number of bytes read since this object was
	// created.
	virtual google::protobuf::int64 ByteCount() const;

	// Returns the checksum we collected so far.
	virtual uint32_t Checksum() const;

protected:
	QFile* file_;
	uint32_t crc32_;
};

}  // namespace io
}  // namespace toolbox

#endif /* TOOLBOX_IO_QFILEZEROCOPYINPUTSTREAM_H */

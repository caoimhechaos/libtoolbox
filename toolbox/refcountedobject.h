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

#ifndef TOOLBOX_REFCOUNTEDOBJECT_H
#define TOOLBOX_REFCOUNTEDOBJECT_H 1

#include <QtCore/QMutex>

namespace toolbox
{

class RefCountedObject
{
public:
	RefCountedObject();

	// Take a reference to the object.
	bool Reference();

	// Drop the reference to the object.
	void Dereference();

	// Check if the object is dereferenced, and if so, lock it against
	// further references so it can be destroyed.
	bool IsDereferencedAndTake();

protected:
	uint32_t num_references_;
	QMutex reference_lock_;
};

class ObjectReference
{
public:
	// Take an object reference of the given object. Will be released
	// upon destruction.
	ObjectReference(RefCountedObject* obj);

	// Release the object reference.
	~ObjectReference();

	// Indicates whether or not we were able to reference the given
	// object.
	bool IsValid();

protected:
	RefCountedObject* referenced_;
};

} // namespace toolbox

#endif /* TOOLBOX_REFCOUNTEDOBJECT_H */

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

#include "refcountedobject.h"

namespace toolbox
{
RefCountedObject::RefCountedObject()
: num_references_(0)
{
}

bool
RefCountedObject::Reference()
{
	// TODO(caoimhe): Ugh, race condition, anyone?
	if (!this) return false;
	QMutexLocker lock(&reference_lock_);

	num_references_++;
}

void
RefCountedObject::Dereference()
{
	QMutexLocker lock(&reference_lock_);

	num_references_--;
}

bool
RefCountedObject::IsDereferencedAndTake()
{
	// TODO(caoimhe): Ugh, race condition, anyone?
	if (!this) return false;
	reference_lock_.lock();

	if (num_references_)
	{
		reference_lock_.unlock();
		return false;
	}

	// No unlock here because we want to return the object locked.
	return true;
}

ObjectReference::ObjectReference(RefCountedObject* obj)
: referenced_(0)
{
	if (obj->Reference())
		referenced_ = obj;
}

ObjectReference::~ObjectReference()
{
	if (referenced_) referenced_->Dereference();
}

bool
ObjectReference::IsValid()
{
	return referenced_ != 0;
}

}  // namespace toolbox

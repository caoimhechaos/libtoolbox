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

namespace toolbox
{
// Scoped pointer implementation. Implements a pointer which points to a value
// of type T. When the pointer class is destroyed, so is the value.
template <class T>
class ScopedPtr
{
public:
	// Create a new ScopedPtr object pointing to "value". This takes
	// ownership of "value".
	ScopedPtr<T>(T* value)
	: pointee_(value)
	{
	}

	// Create a new ScopedPtr object and initialize it with 0.
	ScopedPtr<T>()
	: pointee_(0)
	{
	}

	// Clean up the value pointed to.
	~ScopedPtr<T>()
	{
		if (pointee_)
			delete pointee_;
	}

	// Determine if the ScopedPtr is currently pointing to nothing.
	bool IsNull() const
	{
		return pointee_ == 0;
	}

	// Retrieve the value pointed to by the ScopedPtr.
	T* Get() const
	{
		return pointee_;
	}

	// Retrieve the value pointed to by the ScopedPtr, reset the ScopedPtr
	// to point to 0 and take ownership of the released object.
	T* Release()
	{
		T* rv = pointee_;
		pointee_ = 0;
		return rv;
	}

	// Set the ScopedPtr to point to "newval". If any preexisting value is
	// still referenced, it will be deleted.
	void Reset(T* newval = 0)
	{
		if (pointee_)
			delete pointee_;

		pointee_ = newval;
	}

	// Returns true if the ScopedPtr is pointing to a non-zero value or
	// 
	bool operator!() const
	{
		return pointee_ != 0;
	}

	T& operator*() const
	{
		// TODO(caoimhe): Assert here or something.
		return *pointee_;
	}

	T* operator->() const
	{
		return pointee_;
	}

private:
	T* pointee_;
};
}  // namespace toolbox

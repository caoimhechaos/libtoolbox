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
 *
 * This API provides exported variables, like Go does.
 */

#ifndef TOOLBOX_EXPVAR_H
#define TOOLBOX_EXPVAR_H 1

#include <string>
#include <map>
#include "scopedptr.h"

#include <exception>

namespace toolbox
{
using std::map;
using std::pair;
using std::string;

class ExpVarBase;

namespace _private
{
class ExpvarRegistry
{
public:
	void Register(string key, ExpVarBase* var);
	ExpVarBase* Lookup(string key);

private:
	map<string, ExpVarBase*> expvars_;
};
}  // namespace _private

class ExpVarBase
{
public:
	ExpVarBase(const string& name);
	virtual ~ExpVarBase();
	virtual string Name();
	virtual string String() = 0;

private:
	const string name_;
};

template <typename T>
class ExpVar : public ExpVarBase
{
public:
	ExpVar(const string& name);
	ExpVar(const string& name, T* ref);
	virtual ~ExpVar();

	virtual T& operator+=(const T& increment);

	virtual void Add(const T& increment);
	virtual void Set(T* newval);
	virtual void SetValue(const T& newval);
	virtual T Get();
	virtual string String();

protected:
	T* value_;
	ScopedPtr<T> value_deleter_;
};

}

#endif // TOOLBOX_EXPVAR_H

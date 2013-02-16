/*-
 * Copyright (c) 2012 Tonnerre Lombard <tonnerre@ancient-solutions.com>,
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

#include <string>
#include <map>
#include <exception>
#include "qsingleton.h"
#include "expvar.h"

namespace toolbox
{

namespace _private
{

void
ExpvarRegistry::Register(string key, ExpVarBase* var)
{
	expvars_.insert(pair<string, ExpVarBase*>(key, var));
}

ExpVarBase*
ExpvarRegistry::Lookup(string key)
{
	auto val = expvars_.find(key);
	if (val != expvars_.end())
		return val->second;
	else
		return 0;
}
}  // namespace _private

ExpVarBase::~ExpVarBase()
{
}

template <typename T>
ExpVar<T>::ExpVar(string name, T* ref)
: name_(name), value_deleter_(new T)
{
	value_ = value_deleter_.data();
	QSingleton<_private::ExpvarRegistry>::GetInstance().Register(
			name, this);
}

template <typename T>
ExpVar<T>::~ExpVar()
{
}

template <typename T> T&
ExpVar<T>::operator+=(const T& increment)
{
	Add(increment);
	return *value_;
}

template <typename T> void
ExpVar<T>::Add(const T& increment)
{
	throw new std::exception();
}

template <typename T> void
ExpVar<T>::Set(T* newval)
{
	value_ = newval;
	value_deleter_.Reset(newval);
}

template <typename T> void
ExpVar<T>::SetValue(T newval)
{
	*value_ = newval;
}

template <typename T> string
ExpVar<T>::Name()
{
	return name_;
}

template <typename T> string
ExpVar<T>::String()
{
	return string();
}

template <>
ExpVar<int64_t>::ExpVar(string name, int64_t* ref)
: name_(name), value_(ref), value_deleter_(ref)
{
}

template <>
ExpVar<int64_t>::ExpVar(string name)
: name_(name), value_deleter_(new int64_t)
{
	value_ = value_deleter_.Get();
	*value_ = 0;
}

template <> void
ExpVar<int64_t>::Add(const int64_t& increment)
{
	*value_ += increment;
}

template <> int64_t
ExpVar<int64_t>::Get()
{
	return *value_;
}

template <> string
ExpVar<int64_t>::String()
{
	return std::to_string(*value_);
}

template <>
ExpVar<string>::ExpVar(string name, string* ref)
: name_(name), value_(ref), value_deleter_(ref)
{
}

template <>
ExpVar<string>::ExpVar(string name)
: name_(name), value_deleter_(new string)
{
	value_ = value_deleter_.Get();
}

template <> void
ExpVar<string>::Add(const string& increment)
{
	*value_ += increment;
}

template <> string
ExpVar<string>::Get()
{
	return *value_;
}

template <> string
ExpVar<string>::String()
{
	return *value_;
}

}  // namespace toolbox

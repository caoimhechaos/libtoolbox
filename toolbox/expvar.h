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
#include <list>
#include <map>
#include <toolbox/scopedptr.h>
#include <toolbox/qsingleton.h>

#include <exception>

namespace toolbox
{
using std::list;
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
	list<string> Keys();

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
	ExpVar(const string& name, T* ref=0)
	: ExpVarBase(name), value_deleter_(ref ? ref : new T)
	{
		value_ = value_deleter_.Get();
		QSingleton<_private::ExpvarRegistry>::GetInstance().Register(
				name, this);
	}
	virtual ~ExpVar()
	{}

	virtual T& operator+=(const T& increment)
	{
		Add(increment);
		return *value_;
	}

	virtual void Add(const T& increment)
	{
		throw std::exception();
	}

	virtual void Set(T* newval)
	{
		value_ = newval;
		value_deleter_.Reset(newval);
	}

	virtual void SetValue(const T& newval)
	{
		*value_ = newval;
	}

	virtual T Get()
	{
		return *value_;
	}

	virtual string String()
	{
		return string();
	}

protected:
	T* value_;
	ScopedPtr<T> value_deleter_;
};

template <typename T>
class ExpMap : public ExpVarBase
{
public:
	ExpMap(const string& name)
	: ExpVarBase(name)
	{
		QSingleton<_private::ExpvarRegistry>::GetInstance().Register(
				name, this);
	}

	virtual ~ExpMap()
	{
	}

	virtual void Add(const string& mapkey, const T& increment)
	{
		throw std::exception();
	}

	virtual void Set(const string& mapkey, T* newval)
	{
		if (values_[mapkey])
			delete values_[mapkey];

		values_[mapkey] = newval;
	}

	virtual void SetValue(const string& mapkey, const T& newval)
	{
		if (values_[mapkey])
			*values_[mapkey] = newval;
		else
			values_[mapkey] = new T(newval);
	}

	virtual T Get(const string& mapkey)
	{
		return values_[mapkey] ? *values_[mapkey] : T();
	}

	virtual string String()
	{
		return string();
	}

private:
	map<string, T*> values_;
};

template <>
ExpVar<int64_t>::ExpVar(const string& name, int64_t* ref)
: ExpVarBase(name), value_deleter_(ref ? ref : new int64_t)
{
		value_ = value_deleter_.Get();
		if (!ref) *value_ = 0;
		QSingleton<_private::ExpvarRegistry>::GetInstance().Register(
				name, this);
}

template <> void
ExpVar<int64_t>::Add(const int64_t& increment)
{
	*value_ += increment;
}

template <> string
ExpVar<int64_t>::String()
{
	return std::to_string(*value_);
}

template <> void
ExpMap<int64_t>::Add(const string& mapkey, const int64_t& increment)
{
	if (values_[mapkey])
		*values_[mapkey] += increment;
	else
		values_[mapkey] = new int64_t(increment);
}

template <> string
ExpMap<int64_t>::String()
{
	string ret;

	for (pair<string, int64_t*> it : values_)
		ret += " \"" + it.first + "\": " +
			std::to_string(*it.second) + ",";

	ret = "{" + ret.substr(ret.length() ? 1 : 0,
			ret.length() ? ret.length() - 2 : 0) + "}";

	return ret;
}

template <> void
ExpVar<string>::Add(const string& increment)
{
	*value_ += increment;
}

template <> string
ExpVar<string>::String()
{
	return *value_;
}

}

#endif // TOOLBOX_EXPVAR_H

/*
 * Tests for the exported variable implementation.
 *
 *  Created on: Nov 6, 2012
 *      Author: Caoimhe Clausen
 */

#include <gtest/gtest.h>
#include "toolbox/expvar.h"

namespace toolbox {
namespace testing {

class ExpVarTest : public ::testing::Test {
protected:
	virtual void SetUp()
	{
	}

	virtual void TearDown()
	{
	}
};

TEST_F(ExpVarTest, IntegerVariables)
{
	ExpVar<int64_t> exported(string("test-variable"));
	EXPECT_EQ(0, exported.Get());
	EXPECT_EQ(10, exported += 10);
	exported.Add(1);
	EXPECT_EQ(11, exported.Get());
	exported.SetValue(0);
	EXPECT_EQ(0, exported.Get());

	exported.Add(23);
	EXPECT_EQ("test-variable", exported.Name());
	EXPECT_EQ("23", exported.String());
}

TEST_F(ExpVarTest, IntegerMaps)
{
	ExpMap<int64_t> exported(string("test-variable"));
	EXPECT_EQ(0, exported.Get("foo"));
	exported.Add("foo", 1);
	EXPECT_EQ(1, exported.Get("foo"));
	exported.SetValue("foo", 0);
	EXPECT_EQ(0, exported.Get("foo"));
	exported.Add("bar", 2);

	exported.Add("baz", 23);
	EXPECT_EQ("test-variable", exported.Name());
	EXPECT_EQ("{\"bar\": 2, \"baz\": 23, \"foo\": 0}", exported.String());
}

TEST_F(ExpVarTest, StringVariables)
{
	ExpVar<string> exported("test-variable",
			new string("test-string"));
	EXPECT_EQ("test-string", exported.Get());
	EXPECT_EQ("test-variable", exported.Name());
	EXPECT_EQ("test-string", exported.String());

	exported += " test-value";
	EXPECT_EQ("test-string test-value", exported.Get());
	EXPECT_EQ("test-string test-value", exported.String());
}

TEST_F(ExpVarTest, ExpVarList)
{
	ExpVar<int64_t> v1("variable-one");
	ExpVar<int64_t> v2("variable-two");
	ExpVar<string> v3("variable-three", new string("bla"));
	list<string> values;
	values.push_back("test-variable");  // from above :S
	values.push_back("variable-one");
	values.push_back("variable-three");
	values.push_back("variable-two");

	toolbox::_private::ExpvarRegistry reg =
		QSingleton<toolbox::_private::ExpvarRegistry>::GetInstance();

	EXPECT_EQ(values, reg.Keys());
}

} /* namespace testing */
} /* namespace toolbox */

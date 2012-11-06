/*
 * Tests for the exported variable implementation.
 *
 *  Created on: Nov 6, 2012
 *      Author: tonnerre
 */

#include <gtest/gtest.h>
#include "expvar.h"

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
	ExpVar<int64_t> exported(QString("test-variable"));
	EXPECT_EQ(0, exported.Get());
	EXPECT_EQ(10, exported += 10);
	exported.Add(1);
	EXPECT_EQ(11, exported.Get());
	exported.SetValue(0);
	EXPECT_EQ(0, exported.Get());

	exported.Add(23);
	EXPECT_EQ(QString("test-variable"), exported.Name());
	EXPECT_EQ(QString("23"), exported.String());
}

TEST_F(ExpVarTest, StringVariables)
{
	ExpVar<QString> exported(QString("test-variable"),
			new QString("test-string"));
	EXPECT_EQ(QString("test-string"), exported.Get());
	EXPECT_EQ(QString("test-variable"), exported.Name());
	EXPECT_EQ(QString("test-string"), exported.String());

	exported += QString(" test-value");
	EXPECT_EQ(QString("test-string test-value"), exported.Get());
	EXPECT_EQ(QString("test-string test-value"), exported.String());
}

} /* namespace testing */
} /* namespace toolbox */

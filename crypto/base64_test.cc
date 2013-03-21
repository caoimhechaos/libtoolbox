/*
 * Tests for the QT Singleton implementation.
 *
 *  Created on: Nov 6, 2012
 *      Author: Caoimhe Clausen
 */

#include <gtest/gtest.h>
#include "toolbox/crypto/base64.h"

namespace toolbox {
namespace testing {

class Base64Test : public ::testing::Test {
protected:
	virtual void SetUp()
	{
	}

	virtual void TearDown()
	{
	}
};

TEST_F(Base64Test, Encode)
{
	EXPECT_EQ("YXNkZg==", Base64::Encode("asdf"));
}

TEST_F(Base64Test, Decode)
{
	EXPECT_EQ("asdf", Base64::Decode("YXNkZg==\n"));
}

} /* namespace testing */
} /* namespace toolbox */

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

#include <gtest/gtest.h>
#include "toolbox/scopedptr.h"

namespace toolbox {
namespace testing {
class Incrementer
{
public:
	explicit Incrementer(int* number)
	: number_(number)
	{
		(*number_)++;
	}

	~Incrementer()
	{
		(*number_)--;
	}

	int Get()
	{
		return *number_;
	}

protected:
	int* number_;
};

class ScopedPtrTest : public ::testing::Test
{
};

TEST_F(ScopedPtrTest, TestDestruction)
{
	int count = 0;

	do
	{
		ScopedPtr<Incrementer> incr(new Incrementer(&count));
		EXPECT_EQ(1, count);
	}
	while (0);

	EXPECT_EQ(0, count);
}

TEST_F(ScopedPtrTest, FollowPointer)
{
	int count = 0;
	ScopedPtr<Incrementer> incr(new Incrementer(&count));
	ScopedPtr<Incrementer> empty;
	ScopedPtr<int> number(new int(23));

	EXPECT_FALSE(incr.IsNull());
	EXPECT_TRUE(empty.IsNull());
	EXPECT_TRUE(!incr);
	EXPECT_FALSE(!empty);
	EXPECT_EQ(count, incr->Get());
	EXPECT_EQ(0, empty.Get());
	EXPECT_EQ(23, *number);

	number.Reset(new int(42));
	EXPECT_EQ(42, *number);

	EXPECT_EQ(1, count);
	incr.Reset();
	EXPECT_EQ(0, count);
}
} // namespace testing
} // namespace toolbox

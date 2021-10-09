#pragma once

#include "Asserts.h"

#define Assert(expression) \
	CORE_ASSERT_IMPL(expression, "Assertion failed.")

#define Assert2(expression, message) \
	CORE_ASSERT_IMPL(expression, message)

#define Verify(expression) \
	CORE_VERIFY_IMPL(expression, "Expession failed.")

#define Verify2(expession, message) \
	CORE_VERIFY_IMPL(expession, message)

#define CORE_VERIFY_IMPL(expession, message) \
	[value = !!(expession)]() -> bool { \
		Core::HandleAssertion(message, __LINE__, __FILE__); \
		return value; \
	}()

#define CORE_ASSERT_IMPL(expression, message) \
	do {\
		if (!(expression)) \
		{ \
			Core::HandleAssertion(message, __LINE__, __FILE__); \
		} \
	} while (false)

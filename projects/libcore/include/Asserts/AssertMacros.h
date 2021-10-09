#pragma once

#include "Asserts.h"

#define Assert(expression) \
	CORE_ASSERT_IMPL((expression), "Assertion failed.")

#define Assert2(expression, message) \
	CORE_ASSERT_IMPL((expression), message)

#define CORE_ASSERT_IMPL(expression, message) \
	if (!(expression)) \
	{ \
		Core::HandleAssertion(message, __LINE__, __FILE__); \
	}
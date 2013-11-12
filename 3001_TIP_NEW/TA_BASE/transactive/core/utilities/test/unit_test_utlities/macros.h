#ifndef UNIT_TEST_INCLUDE_MACROS_H
#define UNIT_TEST_INCLUDE_MACROS_H

#include "cpptest.h"


#define unit_test_unique_object(type) type BOOST_PP_CAT(this_is_a_unique_object_, __COUNTER__ )
#define unit_test_assert_throw( statement ) try { statement; CPPTEST_ASSERT(false); } catch (...) {}


#endif

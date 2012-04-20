//
// Copyright (c) 2012 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#define BOOST_DI_STATIC_ASSERT(cond, expr, types) typedef void _

#include <boost/test/unit_test.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include "boost/di/policies/check_for_creation_ownership.hpp"

namespace boost {
namespace di {
namespace policies {
namespace test {

BOOST_AUTO_TEST_CASE(creation_ownership_clear)
{
    BOOST_CHECK((is_base_of<mpl::true_, check_for_creation_ownership::verify<mpl::vector0<>, int>::type>::value));
    BOOST_CHECK((is_base_of<mpl::true_, check_for_creation_ownership::verify<mpl::vector0<>, int*>::type>::value));
    BOOST_CHECK((is_base_of<mpl::true_, check_for_creation_ownership::verify<mpl::vector0<>, const int*>::type>::value));
    BOOST_CHECK((is_base_of<mpl::true_, check_for_creation_ownership::verify<mpl::vector0<>, shared_ptr<int> >::type>::value));
}

BOOST_AUTO_TEST_CASE(creation_ownership_not_clear)
{
    BOOST_CHECK((is_base_of<mpl::false_, check_for_creation_ownership::verify<mpl::vector0<>, int&>::type>::value));
    BOOST_CHECK((is_base_of<mpl::false_, check_for_creation_ownership::verify<mpl::vector0<>, const int&>::type>::value));
}

} // namespace test
} // namespace policies
} // namespace di
} // namespace boost


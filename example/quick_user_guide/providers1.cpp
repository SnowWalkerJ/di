//
// Copyright (c) 2014 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#include <boost/di.hpp>
#include <new>
#include <cassert>

namespace di = boost::di;

class heap_no_throw {
public:
    template<class...>
    static constexpr auto is_creatable() {
        return true;
    }

    template<
      class // interface
    , class T // implementation
    , class TInit // direct()/uniform{}
    , class TMemory // heap/stack
    , class... TArgs>
    auto get(const TInit&, const TMemory&, TArgs&&... args) const noexcept {
        return new (std::nothrow) T{std::forward<TArgs>(args)...};
    }
};

template<class>
class my_provider : public di::config<> {
public:
    auto provider() const noexcept {
        return heap_no_throw{};
    }
};

int main() {
    auto injector = di::make_injector<my_provider>();
    assert(0 == injector.create<int>());
}


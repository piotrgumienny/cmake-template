#include "lockable.hpp"

#include <gtest/gtest.h>
#include <mutex>
#include <shared_mutex>
#include <string>
#include <type_traits>

namespace projname {
namespace {

using namespace std::string_literals;

template <typename MutexType>
struct LockableTest : testing::Test {};

template <typename MutexType>
using LockableString = Lockable<std::string, MutexType>;

using MutexTypes = testing::Types<std::mutex,
                                  std::recursive_mutex,
                                  std::timed_mutex,
                                  std::recursive_timed_mutex,
                                  std::shared_mutex>;

TYPED_TEST_SUITE(LockableTest, MutexTypes);

TYPED_TEST(LockableTest, lockAndUnlockManually) {
    LockableString<TypeParam> s1;
    s1.lock();
    s1.unlock();
}

TYPED_TEST(LockableTest, lockGuard) {
    LockableString<TypeParam> s1{"asd"s};
    EXPECT_TRUE((std::is_same_v<LockableString<TypeParam>, decltype(s1)>));

    Lock l1{s1};
    EXPECT_TRUE(
        (std::is_same_v<Lock<LockableString<TypeParam>>, decltype(l1)>));

    EXPECT_EQ("asd", *l1);
    EXPECT_EQ(3u, l1->size());
}

TYPED_TEST(LockableTest, initializeByCopy) {
    auto s0{"qwe"s};
    LockableString<TypeParam> s1{s0};
    EXPECT_TRUE((std::is_same_v<LockableString<TypeParam>, decltype(s1)>));

    Lock l1{s1};
    EXPECT_TRUE(
        (std::is_same_v<Lock<LockableString<TypeParam>>, decltype(l1)>));

    *l1 = "asd";
    EXPECT_EQ("qwe", s0);
    EXPECT_EQ("asd", *l1);
}

TYPED_TEST(LockableTest, lockAndSwap) {
    LockableString<TypeParam> s1{"asd"s};
    LockableString<TypeParam> s2{"qwe"s};
    std::lock(s1, s2);
    Lock l1{s1, std::adopt_lock};
    Lock l2{s2, std::adopt_lock};
    std::swap(*l1, *l2);
    EXPECT_EQ(6u, l1->size() + l2->size());
}

}  // namespace
}  // namespace projname

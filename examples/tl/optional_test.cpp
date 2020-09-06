#include <gtest/gtest.h>
#include <string>
#include <tl/optional.hpp>

using std::string_literals::operator""s;

namespace examples {
namespace {

[[nodiscard]] tl::optional<int> process(bool const result) noexcept {
    if (result) {
        return 12345;
    } else {
        return tl::nullopt;
    }
}

TEST(Optional, optional) {
    EXPECT_EQ(12345, process(true).value());
    EXPECT_THROW(process(false).value(), tl::bad_optional_access);
}

} // namespace
} // namespace examples

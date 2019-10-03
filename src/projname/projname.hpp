#ifndef PROJNAME_PROJNAME_HPP
#define PROJNAME_PROJNAME_HPP

#ifdef _WIN32
#include <SDKDDKVer.h>
#endif

#include <iostream>

#include <boost/asio/io_context.hpp>
#include <boost/beast/core/span.hpp>
#include <boost/system/error_code.hpp>

#include <projname/config.h>

namespace projname {

struct ContinuousGreeter {
    boost::asio::io_context& io;

    void operator()() const;
};

auto stop_io_context(boost::asio::io_context& io) noexcept {
    return [&io](boost::system::error_code const& ec) {
        if (!ec) {
            io.stop();
        } else {
            std::cerr << ec.message() << std::endl;
        }
    };
}

PROJNAME_EXPORT int run(boost::beast::span<char const* const> args);

}  // namespace projname

#endif  // PROJNAME_PROJNAME_HPP

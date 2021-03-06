/**
 * @project zapdos
 * @file include/http/AsioCompat.hpp
 * @author  S Roychowdhury < sroycode at gmail dot com >
 * @version 1.0.0
 *
 * @section LICENSE
 *
 * Copyright (c) 2018-2020 S Roychowdhury
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * @section DESCRIPTION
 *
 *  AsioCompat.hpp : Asio compatibility for Web Server ( Modified from eidheim/Simple-Web-Server )
 *
 */
#ifndef _ZPDS_HTTP_ASIO_COMPAT_HPP_
#define _ZPDS_HTTP_ASIO_COMPAT_HPP_

#include <memory>

#include <boost/asio.hpp>
#include <boost/asio/steady_timer.hpp>

namespace zpds {
namespace http {

namespace asio = boost::asio;
namespace error = asio::error;
using error_code = boost::system::error_code;
namespace errc = boost::system::errc;
using system_error = boost::system::system_error;
namespace make_error_code = boost::system::errc;

#if (BOOST_ASIO_VERSION >= 101300)
using io_context = asio::io_context;
using io_whatever = asio::io_context;
using resolver_results = asio::ip::tcp::resolver::results_type;
using async_connect_endpoint = asio::ip::tcp::endpoint;

template <typename handler_type>
inline void post(io_context &context, handler_type &&handler)
{
	asio::post(context, std::forward<handler_type>(handler));
}
inline void restart(io_context &context) noexcept
{
	context.restart();
}
inline asio::ip::address make_address(const std::string &str) noexcept
{
	return asio::ip::make_address(str);
}
template <typename socket_type, typename duration_type>
std::unique_ptr<asio::steady_timer> make_steady_timer(socket_type &socket, std::chrono::duration<duration_type> duration)
{
	return std::unique_ptr<asio::steady_timer>(new asio::steady_timer(socket.get_executor(), duration));
}
template <typename handler_type>
void async_resolve(asio::ip::tcp::resolver &resolver, const std::pair<std::string, std::string> &host_port, handler_type &&handler)
{
	resolver.async_resolve(host_port.first, host_port.second, std::forward<handler_type>(handler));
}
inline asio::executor_work_guard<io_context::executor_type> make_work_guard(io_context &context)
{
	return asio::make_work_guard(context);
}
#else
using io_context = asio::io_service;
using io_whatever = asio::io_service;
using resolver_results = asio::ip::tcp::resolver::iterator;
using async_connect_endpoint = asio::ip::tcp::resolver::iterator;

template <typename handler_type>
inline void post(io_context &context, handler_type &&handler)
{
	context.post(std::forward<handler_type>(handler));
}
inline void restart(io_context &context) noexcept
{
	context.reset();
}
inline asio::ip::address make_address(const std::string &str) noexcept
{
	return asio::ip::address::from_string(str);
}
template <typename socket_type, typename duration_type>
std::unique_ptr<asio::steady_timer> make_steady_timer(socket_type &socket, std::chrono::duration<duration_type> duration)
{
	return std::unique_ptr<asio::steady_timer>(new asio::steady_timer(socket.get_io_service(), duration));
}
template <typename handler_type>
void async_resolve(asio::ip::tcp::resolver &resolver, const std::pair<std::string, std::string> &host_port, handler_type &&handler)
{
	resolver.async_resolve(asio::ip::tcp::resolver::query(host_port.first, host_port.second), std::forward<handler_type>(handler));
}
inline io_context::work make_work_guard(io_context &context)
{
	return io_context::work(context);
}
#endif

} // namespace http
} // namespace zpds

#endif // _ZPDS_HTTP_ASIO_COMPAT_HPP_

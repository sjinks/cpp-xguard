/**
 * @file xguard.h
 * @date Apr 26, 2010
 * @author Vladimir Kolesnikov <vladimir@free-sevastopol.com>
 * @see http://blog.sjinks.pro/c-cpp/796-scope-guard-by-means-of-cpp-0x-part-1/
 * @see http://blog.sjinks.pro/c-cpp/800-scope-guard-cpp-0x-part-2/
 *
 * Changelog:
 * Sep 15, 2012:
 * * got rid of try ... catch block in the destructor
 * * all methods are now marked with noexcept
 * Jun 10, 2011:
 * * added move assignment operator
 * * A&&... p argument to @c makeXGuard() is no longer @c const
 * * @c other argument to the move constructor is no longer @c const
 */

#ifndef XGUARD_H_
#define XGUARD_H_

#include <functional>

template<typename Function>
class XGuard {
public:
	XGuard(const Function& aFunction) noexcept : m_fSucceeded(false), m_Function(aFunction)
	{
	}

	~XGuard(void) noexcept
	{
		if (!this->m_fSucceeded) {
			this->m_Function();
		}
	}

	XGuard(XGuard&& other) noexcept : m_fSucceeded(std::move(other.m_fSucceeded)), m_Function(std::move(other.m_Function))
	{
		other.commit();
	}

	XGuard& operator=(XGuard&& rhs) noexcept
	{
		if (this != &rhs) {
			this->m_fSucceeded = std::move(rhs.m_fSucceeded);
			this->m_Function   = std::move(rhs.m_Function);
			rhs.commit();
		}

		return *this;
	}

	void commit(void) const noexcept
	{
		this->m_fSucceeded = true;
	}

private:
	mutable bool m_fSucceeded;
	Function m_Function;

	XGuard(const XGuard&) = delete;
	XGuard& operator=(const XGuard&) = delete;
};

template<typename F, typename... A>
inline auto makeXGuard(F&& f, A&&... p) -> XGuard<decltype(std::bind(f, p...))>
{
	auto func = std::bind(f, p...);
	return XGuard<decltype(func)>(func);
}

template<typename C, typename M, typename... A>
inline auto makeXGuard(C&& c, M&& m, A&&... p) -> XGuard<decltype(std::bind(m, c, p...))>
{
	auto func = std::bind(m, c, p...);
	return XGuard<decltype(func)>(func);
}

#endif /* XGUARD_H_ */

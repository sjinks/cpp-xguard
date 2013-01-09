#ifndef XGUARD_TESTSUITE_H
#define XGUARD_TESTSUITE_H

#include <iostream>
#include <cxxtest/TestSuite.h>
#include "../src/xguard.h"

int g_rollback_commit_v = 0;

class XGuardTestSuite : public CxxTest::TestSuite {
public:

	void testBasicRollbackCommit1(void)
	{
		{
			auto guard = makeXGuard(&XGuardTestSuite::static_reset_rollback_commit_v);
			g_rollback_commit_v = 5;
			TS_ASSERT_EQUALS(g_rollback_commit_v, 5);
		}

		TS_ASSERT_EQUALS(g_rollback_commit_v, 0);

		{
			auto guard = makeXGuard(&XGuardTestSuite::static_reset_rollback_commit_v);
			g_rollback_commit_v = 3;
			TS_ASSERT_EQUALS(g_rollback_commit_v, 3);
			guard.commit();
			TS_ASSERT_EQUALS(g_rollback_commit_v, 3);
		}

		TS_ASSERT_EQUALS(g_rollback_commit_v, 3);
	}

	void testBasicRollbackCommit2(void)
	{
		{
			auto guard = makeXGuard(this, &XGuardTestSuite::reset_rollback_commit_v);
			g_rollback_commit_v = 5;
			TS_ASSERT_EQUALS(g_rollback_commit_v, 5);
		}

		TS_ASSERT_EQUALS(g_rollback_commit_v, 0);

		{
			auto guard = makeXGuard(this, &XGuardTestSuite::reset_rollback_commit_v);
			g_rollback_commit_v = 3;
			TS_ASSERT_EQUALS(g_rollback_commit_v, 3);
			guard.commit();
			TS_ASSERT_EQUALS(g_rollback_commit_v, 3);
		}

		TS_ASSERT_EQUALS(g_rollback_commit_v, 3);
	}

	void testMethodWithArgs(void)
	{
		{
			auto guard  = makeXGuard(this, &XGuardTestSuite::setVar, 10);
			this->m_var = 5;
			TS_ASSERT_EQUALS(this->m_var, 5);
		}

		TS_ASSERT_EQUALS(this->m_var, 10);

		{
			auto guard  = makeXGuard(this, &XGuardTestSuite::setSum, 1, 2, 3);
			this->m_var = 5;
			TS_ASSERT_EQUALS(this->m_var, 5);
		}

		TS_ASSERT_EQUALS(this->m_var, 6);

		{
			auto guard  = makeXGuard(this, &XGuardTestSuite::setSum, 1, 2, 3);
			this->m_var = 50;
			TS_ASSERT_EQUALS(this->m_var, 50);
			guard.commit();
		}

		TS_ASSERT_EQUALS(this->m_var, 50);
	}

	void testMethodByRef(void)
	{
		{
			auto guard  = makeXGuard(this, &XGuardTestSuite::decrement, std::ref(this->m_var));
			this->m_var = 5;
			TS_ASSERT_EQUALS(this->m_var, 5);
		}

		TS_ASSERT_EQUALS(this->m_var, 4);

		{
			auto guard  = makeXGuard(this, &XGuardTestSuite::decrement, std::ref(this->m_var));
			this->m_var = 1;
			TS_ASSERT_EQUALS(this->m_var, 1);
			guard.commit();
		}

		TS_ASSERT_EQUALS(this->m_var, 1);
	}

	struct Test {
		static int value;
		int x;
		Test(void) : x(4) {}
		Test(const Test& other) : x(other.x) { ++Test::value; }
	};

	void testByReference(void)
	{
		Test x;
		int n;

		{
			TS_ASSERT_EQUALS(Test::value, 0);
			auto guard = makeXGuard(this, &XGuardTestSuite::testval, x);
			TS_ASSERT(Test::value > 0); // == 2
			TS_ASSERT_EQUALS(Test::value, 2);
			n = Test::value;
//			std::cout << n << std::endl;
		}

		TS_ASSERT(Test::value >= n); // == 4
		TS_ASSERT_EQUALS(Test::value, 4);
		TS_ASSERT_EQUALS(x.x, 4);

		x.x         = 4;
		Test::value = 0;

		{
			TS_ASSERT_EQUALS(Test::value, 0);
			auto guard = makeXGuard(this, &XGuardTestSuite::testval, std::ref(x));
			TS_ASSERT_EQUALS(Test::value, 0);
		}

		TS_ASSERT(Test::value >= 1); // == 2
		TS_ASSERT_EQUALS(Test::value, 2); // == 2
		TS_ASSERT_EQUALS(x.x, 4);

		x.x         = 4;
		Test::value = 0;

		{
			TS_ASSERT_EQUALS(Test::value, 0);
			auto guard = makeXGuard(this, &XGuardTestSuite::testval, std::cref(x));
			TS_ASSERT_EQUALS(Test::value, 0);
		}

		TS_ASSERT(Test::value >= 1); // == 2
		TS_ASSERT_EQUALS(Test::value, 2); // == 2
		TS_ASSERT_EQUALS(x.x, 4);

		x.x         = 4;
		Test::value = 0;

		{
			TS_ASSERT_EQUALS(Test::value, 0);
			auto guard = makeXGuard(this, &XGuardTestSuite::testref, std::ref(x));
			TS_ASSERT_EQUALS(Test::value, 0);
		}

		TS_ASSERT_EQUALS(x.x, 6);

		x.x         = 4;
		Test::value = 0;

		{
			TS_ASSERT_EQUALS(Test::value, 0);
			auto guard = makeXGuard(this, &XGuardTestSuite::testcref, std::cref(x));
			TS_ASSERT_EQUALS(Test::value, 0);
		}
	}

private:
	int m_var = 0;

	static void static_reset_rollback_commit_v(void)
	{
		g_rollback_commit_v = 0;
	}

	void reset_rollback_commit_v(void)
	{
		g_rollback_commit_v = 0;
	}

	void setVar(int val)
	{
		this->m_var = val;
	}

	void setSum(int val1, int val2, int val3)
	{
		this->m_var = val1 + val2 + val3;
	}

	void decrement(int& var)
	{
		--var;
	}

	void testref(Test& x)
	{
		x.x = 6;
	}

	void testcref(const Test& x) const
	{
	}

	void testval(Test x)
	{
		x.x = 5;
	}
};

int XGuardTestSuite::Test::value = 0;

#endif // XGUARD_TESTSUITE_H

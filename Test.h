#include </media/win_c2/PROGGA/GIT/porer_linux/cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class Test : public CppUnit::TestFixture
{
   CPPUNIT_TEST_SUITE(Test);
   CPPUNIT_TEST(Test1);
   CPPUNIT_TEST(Test2);
   CPPUNIT_TEST_SUITE_END();
public:
   void setUp() {
       // инициализация
   }
   void tearDown()    {
       // деинициализация
   }
   void Test1()    {
       CPPUNIT_ASSERT(true);
   }
   void Test2()    {
       CPPUNIT_ASSERT(true);
   }

};
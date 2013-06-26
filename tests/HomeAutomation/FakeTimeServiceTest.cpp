extern "C"
{
#include "FakeTimeService.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(FakeTimeService)
{
    void setup()
    {
      FakeTimeService_Create();
    }

    void teardown()
    {
       FakeTimeService_Destroy();
    }
};

TEST(FakeTimeService, Create)
{
  LONGS_EQUAL(TIME_UNKNOWN, getMinuteOfDay());
  LONGS_EQUAL(TIME_UNKNOWN, getDayOfWeek());
}

TEST(FakeTimeService, Set)
{
  FakeTimeService_SetMinute(42);
  FakeTimeService_SetDay(SATURDAY);
  LONGS_EQUAL(42, getMinuteOfDay());
  LONGS_EQUAL(SATURDAY, getDayOfWeek());
}


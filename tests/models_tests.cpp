#include <gtest/gtest.h>
#include <finam-api-manager/time.h>

TEST(Time, Iso8501) {
    std::string time = "2026-05-08T19:51:03Z";
    Time t(time);
    ASSERT_EQ(t.iso8501(), time);
}

TEST(Time, Equality) {
    std::string time = "2026-05-08T19:51:03Z";
    Time t1(time);
    Time t2(time);
    ASSERT_TRUE(t1 == t2);
}

TEST(Time, Comparations) {
    Time t1("2026-05-08T19:51:03Z");
    Time t2("2026-06-08T19:51:03Z");
    Time t3("2026-06-08T19:51:05Z");
    ASSERT_TRUE(t1 != t2);
    ASSERT_TRUE(t1 <= t2);
    ASSERT_TRUE(t1 < t2);

    ASSERT_TRUE(!(t2 == t3));
    ASSERT_TRUE(t3 >= t2);
    ASSERT_TRUE(t3 > t2);
}
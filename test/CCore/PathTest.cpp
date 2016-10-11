#include <gtest/gtest.h>
#include <CCore/Path.h>

class PathTest : public ::testing::Test
{
protected:

    Path path;
    PrimalityTester primalityTester;

    virtual void SetUp()
    {
        primalityTester = PrimalityTester();
        path = Path();
        path.setPrimalityTester(primalityTester);
    }
};

TEST_F(PathTest, PathTestLoop)
{
    path.setStartingPoint(Point(4, 5));
    path.calculatePath(std::make_tuple(
            Point(0, 0),
            Point(30, 30)
    ));

    EXPECT_TRUE(path.isLoop());
    EXPECT_EQ(44, path.getLength());
    EXPECT_FALSE(path.isSquare());
}

TEST_F(PathTest, PathTestBoundaries)
{
    path.setStartingPoint(Point(5, 8));
    path.calculatePath(std::make_tuple(
            Point(0, 0),
            Point(15, 15)
    ));

    EXPECT_FALSE(path.isLoop());

    path.calculatePath(std::make_tuple(
            Point(0, 0),
            Point(30, 30)
    ));

    EXPECT_TRUE(path.isLoop());
}

TEST_F(PathTest, PathTestInvalidLoop)
{
    path.setStartingPoint(Point(5, 8));
    path.calculatePath(std::make_tuple(
            Point(0, 0),
            Point(15, 15)
    ));

    EXPECT_FALSE(path.isLoop());
    EXPECT_FALSE(path.isSquare());
}

TEST_F(PathTest, PathTestSquare)
{
    path.setStartingPoint(Point(2, 7));
    path.calculatePath(std::make_tuple(
            Point(0, 0),
            Point(30, 30)
    ), true);

    EXPECT_TRUE(path.isLoop());
    EXPECT_TRUE(path.isSquare());
    EXPECT_EQ(24, path.getLength());
}
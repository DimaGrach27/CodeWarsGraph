#define NDEBUG
#include <assert.h>
#include <unordered_map>
using namespace  std;

struct Dot
{
    Dot() = default;

    Dot(char letter)
    {
        Letter = letter;
        IsPicked = false;
    }
    
    char Letter;
    bool IsPicked;
};

struct Point
{
    Point(int x, int y)
    {
        x_pos = x;
        y_pos = y;
    }
    
    int x_pos;
    int y_pos;

    bool operator==(Point const& p) const
    {
        return x_pos == p.x_pos && y_pos == p.y_pos;
    }

    struct HashFunction
    {
        size_t operator()(const Point& p) const
        {
            size_t rowHash = std::hash<int>()(p.x_pos);
            size_t colHash = std::hash<int>()(p.y_pos) << 1;
            return rowHash ^ colHash;
        } 
    };
};

unordered_map<Point, Dot, Point::HashFunction> grid;

//Allow move
//horizontal x +/- 1; if (x+1)/(x-1) == IsPicked allow x +/- 2;
//vertical y +/- 1; if (y+1)/(y-1) == IsPicked allow y +/- 2;
//diagonal x +/- 1 & y +/- 1; if (x +/- 1 & y +/- 1) == IsPicked allow x +/- 2 & y +/- 2;
// x +/- 1, y +/- 2; y +/- 1, x +/- 2

bool IsMoveAllowed(const Point &startMove, const Point &move)
{
    if(startMove.x_pos + move.x_pos > 1 || startMove.x_pos + move.x_pos < -1 ||
        startMove.y_pos + move.y_pos > 1 || startMove.y_pos + move.y_pos < -1)
    {
        return false;
    }

    const Point nextPoint = Point(startMove.x_pos + move.x_pos, startMove.y_pos + move.y_pos);

    if(grid[nextPoint].IsPicked)
    {
        return IsMoveAllowed(nextPoint, move);
    }

    return true;
}

unsigned int countPatternsFrom(char firstDot, unsigned short length)
{
    if(length == 0 || length == 10)
    {
        return 0;
    }

    if(length == 1)
    {
        return 1;
    }
    
    Point moves [] =
    {
        {1, 0}, {-1, 0},
        {0, 1}, {-0, -1},
        {1, 1}, {-1, 1}, {1, -1}, {-1, -1},
        {1, -2}, {-1, -2}, {1, 2}, {-1 , 2},
        {2, 1}, {2, -1}, {-2, 1}, {-2 , -1}
    };
    
    return 0;
}

int main(int argc, char* argv[])
{
    grid = unordered_map<Point, Dot, Point::HashFunction>();
    grid.emplace(Point(-1, 1), Dot('A'));
    grid.emplace(Point(0, 1), Dot('B'));
    grid.emplace(Point(1, 1), Dot('C'));
    grid.emplace(Point(-1, 0), Dot('D'));
    grid.emplace(Point(0, 0), Dot('E'));
    grid.emplace(Point(1, 0), Dot('F'));
    grid.emplace(Point(-1, -1), Dot('G'));
    grid.emplace(Point(0, -1), Dot('H'));
    grid.emplace(Point(1, -1), Dot('I'));
    
    assert(countPatternsFrom('A', 0) == 0);
    assert(countPatternsFrom('A', 10) == 0);
    assert(countPatternsFrom('B', 1) == 1);
    assert(countPatternsFrom('C', 2) == 5);
    assert(countPatternsFrom('D', 3) == 37);
    assert(countPatternsFrom('E', 4) == 256);
    assert(countPatternsFrom('E', 8) == 23280);
    
    return 0;
}

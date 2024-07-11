// #define NDEBUG
#include <assert.h>
#include <iostream>
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
    Point() = default;
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

    Point operator+(Point const& p) const
    {
        return { x_pos + p.x_pos, y_pos + p.y_pos };
    }

    struct HashFunction
    {
        size_t operator()(const Point& p) const
        {
            const size_t rowHash = std::hash<int>()(p.x_pos);
            const size_t colHash = std::hash<int>()(p.y_pos) << 1;
            return rowHash ^ colHash;
        } 
    };
};

unordered_map<Point, Dot, Point::HashFunction> grid;
unsigned int Count = 0;
string line;
Point* nextPoint;
//Allow move
//horizontal x +/- 1; if (x+1)/(x-1) == IsPicked allow x +/- 2;
//vertical y +/- 1; if (y+1)/(y-1) == IsPicked allow y +/- 2;
//diagonal x +/- 1 & y +/- 1; if (x +/- 1 & y +/- 1) == IsPicked allow x +/- 2 & y +/- 2;
// x +/- 1, y +/- 2; y +/- 1, x +/- 2

bool IsMoveAllowed(const Point &startMove, const Point &move, Point* returnPoint)
{
    if(startMove.x_pos + move.x_pos > 1 || startMove.x_pos + move.x_pos < -1 ||
        startMove.y_pos + move.y_pos > 1 || startMove.y_pos + move.y_pos < -1)
    {
        return false;
    }

    const Point nextPoint = Point(startMove + move);
    returnPoint->x_pos = nextPoint.x_pos;
    returnPoint->y_pos = nextPoint.y_pos;

    if(grid[nextPoint].IsPicked)
    {
        return IsMoveAllowed(nextPoint, move, returnPoint);
    }

    return true;
}

void SetDotPicked(const Point point)
{
    grid[point].IsPicked = true;
}

void ResetDots()
{
    for (auto keyValue : grid)
    {
        Dot dot = Dot(keyValue.second.Letter);
        dot.IsPicked= false;
        grid[keyValue.first] = dot;
    }
}

void SetDotPick(const Point &point, bool isPicked)
{
    grid[point].IsPicked = isPicked;
}

void CycleMove(const Point startMove, const vector<Point>& moves, unsigned short length)
{
    SetDotPick(startMove, true);
    line.push_back(grid[startMove].Letter);

    for (const Point& move : moves)
    {
        if(!IsMoveAllowed(startMove, move, nextPoint))
        {
            continue;
        }
        
        if(length == 1)
        {
            Count++;
            const Point point = *nextPoint;
            // const Point point = startMove + move;
            SetDotPick(point, false);
            line.append("->");
            line.push_back(grid[point].Letter);
            cout << line << '\n';

            line.pop_back();
            line.pop_back();
            line.pop_back();
        }
        else
        {
            // const Point point = startMove + move;
            const Point point = *nextPoint;
            line.append("->");
            CycleMove(point, moves, length - 1);
        }
    }

    if(!line.empty())
        line.pop_back();
    if(!line.empty())
        line.pop_back();
    if(!line.empty())
        line.pop_back();
    
    SetDotPick(startMove, false);
}

unsigned int countPatternsFrom(char firstDot, unsigned short length)
{
    ResetDots();
    Count = 0;
    line.clear();
    nextPoint = new Point;

    cout << "Start: " << firstDot << " Length: " << length << '\n';
    cout << "Dots: " << '\n';

    if(length < 1 || length > 9)
    {
        return 0;
    }

    if(length == 1)
    {
        cout << firstDot << '\n';

        return 1;
    }

    vector<Point> moves = 
    // const Point moves [] =
    {
        {1, 0}, {-1, 0},
        {0, 1}, {-0, -1},
        {1, 1}, {-1, 1}, {1, -1}, {-1, -1},
        {1, -2}, {-1, -2}, {1, 2}, {-1 , 2},
        {2, 1}, {2, -1}, {-2, 1}, {-2 , -1}
    };

    Point startPoint = Point();

    for (const auto keyValue : grid)
    {
        if(keyValue.second.Letter == firstDot)
        {
            startPoint = keyValue.first;
            break;
        }
    }
    
    CycleMove(startPoint, moves, length - 1);

    cout << "Return count = " << Count << '\n';
    delete nextPoint;
    return Count;
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

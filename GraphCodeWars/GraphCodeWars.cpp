#define NDEBUG
#include <assert.h>

struct Dot
{
    char Letter;
    bool IsPicked;
    int x_pos;
    int y_pos;
};

unsigned int countPatternsFrom(char firstDot, unsigned short length)
{
    Dot map [9] =
        {
        {'A'}, {'B'}, {'C'},
        {'D'}, {'E'}, {'F'},
        {'G'}, {'H'}, {'I'},
        };
    
    return 0;
}



int main(int argc, char* argv[])
{
    assert(countPatternsFrom('A', 0) == 0);
    assert(countPatternsFrom('A', 10) == 0);
    assert(countPatternsFrom('B', 1) == 1);
    assert(countPatternsFrom('C', 2) == 5);
    assert(countPatternsFrom('D', 3) == 37);
    assert(countPatternsFrom('E', 4) == 256);
    assert(countPatternsFrom('E', 8) == 23280);
    
    return 0;
}

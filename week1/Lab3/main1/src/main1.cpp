#include <iostream>
#include <string.h>

using namespace std;

char g_buf[0x20] = "NotFLAG{QQ}";

class RunFunc1 {
public:
    RunFunc1();
};

RunFunc1::RunFunc1()
{
    char __buf[] = {70, 77, 67, 68, 127, 65, 77, 88, 91, 97, 101, 124, 65, 108, 101, 106, 98, 78, 69, 68, 64, 104, 0};
    int i;

    cin >> i;

    if (i == 0x54878745) {
        for (int j = 0; j < 22; ++j) {
            __buf[j] ^= j;
        }
        
        strcpy(g_buf, __buf);
    }
}

RunFunc1 rf1;

int main(void)
{
    printf("g_buf: %s\n", g_buf);
}

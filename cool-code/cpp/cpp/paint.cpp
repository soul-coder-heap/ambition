#include<iostream>
#include<cmath>
using namespace std;
int main()
{
    float x, y;
    for (y = 1.5f; y >-1.0f; y -= 0.1f)
    {
        for (x = -1.5f; x <1.5f; x += 0.05f)
        {
            float a = x*x + y*y - 1;
            if ((a*a*a- x*x*y*y*y)<=0)//心形方程
                cout << '*';
            else cout << " ";
        }
        cout << endl;
    }
    return 0;
}
#include "iostream"

using namespace std;

class A
{
    public:
        A()
        {
        }
        int get() const
        {
           cout<<10<<endl;
        }
        int get()
        {
            cout<<"hello"<<endl;
        }
};

int main()
{
    int const a = 10;
    const int b = 20;
    int c = 30;
    int d = 40;
    int const *p = &d;
    int* const q = &c;
    cout<<*p<<endl;
    d = 20;
    p = &c;
    cout<<*p<<endl;

    cout<<*q<<endl;
    //cout<<*q<<endl;

    A aa;
    aa.get();
    const A bb;
    bb.get();
    return 0;
}

#include <iostream>
using namespace std;

class Singleton
{
    private:
        Singleton(){}
        static Singleton* pinstance;
        int num;

    public:
        static Singleton* getInstance()
        {
            // This is the lazy instantiation, but not thread-safe
            if (pinstance == 0) // here may not be thread-safe, since two threads may enter simultaniously
                pinstance = new Singleton;
            return pinstance;
        }
        // other methods
        void test()
        {
            cout<<"NUM:"<<getNum()<<endl;
        }
        void setNum(int n)
        {
            num = n;
        }
        int getNum()
        {
            return num;
        }
};
Singleton* Singleton::pinstance = 0;

int main()
{
    Singleton *s = Singleton::getInstance();
    s->setNum(10);
    s->test();
    Singleton *t = Singleton::getInstance();
    t->test();  // get the same number 10, which means Single pattern offer a way to keep the global state
    cout<<s<<endl;
    cout<<t<<endl;  // and from here, you can find they point to the same address, which from pinstance
     
    return 0;
}

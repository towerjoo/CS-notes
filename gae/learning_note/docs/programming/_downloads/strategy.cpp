#include <iostream>
using namespace std;

class FlyBehavior
{
    public:
        virtual void fly(){}
};

class QuackBehavior
{
    public:
        virtual void quack(){}
};

class FlyWithWind:public FlyBehavior
{
    public:
        void fly()
        {
            cout<<"I'm really flying"<<endl;
        }
};

class FlyFake:public FlyBehavior
{
    public:
        void fly()
        {
            cout<<"I can't fly."<<endl;
        }
};

class Quack:public QuackBehavior
{
    public:
        void quack()
        {
            cout<<"GuaGua, I'm quacking"<<endl;
        }
};

class QuackSilence:public QuackBehavior
{
    public:
        void quack()
        {
            cout<<"I can't quack at all"<<endl;
        }
};
        

class Duck
{
    public:
        QuackBehavior* quackBehavior;
        FlyBehavior* flyBehavior;

        void performFly()
        {
            flyBehavior->fly();
        }

        void performQuack()
        {
            quackBehavior->quack();
        }
        void setFlyBehavior(FlyBehavior *f)
        {
            flyBehavior = f;
        }
        void setQuackBehavior(QuackBehavior *q)
        {
            quackBehavior = q;
        }
        virtual ~Duck()
        {
            // 由于变量中有new生成的成员变量,所以需要释放空间
            // 此处为虚函数,则会在运行时动态绑定
            delete quackBehavior;
            delete flyBehavior;
            cout<<"I am destroyed."<<endl;
        }
};

class RealDuck:public Duck
{
    public:
        RealDuck()
        {
            quackBehavior = new Quack();
            flyBehavior = new FlyWithWind();
        }
};

class FakeDuck:public Duck
{
    public:
        FakeDuck()
        {
            // new 生成的实例为指针型
            quackBehavior = new QuackSilence();
            flyBehavior = new FlyFake();
        }
};
        
int main()
{
    Duck *duck;
    RealDuck real; //真的会叫会飞的鸭子
    FakeDuck fake; //假的不会飞不会叫的鸭子

    duck = &real;   //动态绑定到真鸭子
    duck->performFly();
    duck->performQuack();

    duck = &fake;   //动态绑定到假鸭子
    duck->performFly();
    duck->performQuack();

    duck->setFlyBehavior(new FlyWithWind());    //运行时更改飞的属性
    duck->performFly();
    return 0;
}

#include <iostream>
#include <string>
using namespace std;

class Duck
{
    public:
       virtual void quack(){}
       virtual void fly(){}
};

class Turkey
{
    public:
        virtual void gobble(){}
        virtual void fly(){}
};

class MallardDuck:public Duck
{
    public:
        void quack(){cout<<"Quack"<<endl;}  // the concrete class
        void fly(){cout<<"I'm flying"<<endl;}
};

class WildTurkey:public Turkey
{
    public:
        void gobble(){cout<<"Gobble gobble"<<endl;}
        void fly(){cout<<"I'm flying a short distance."<<endl;}
};

class DuckAdapter:public Duck
{
    public:
        Turkey *turkey;
        DuckAdapter(Turkey *turkey)
        {
            this->turkey = turkey;
        }
        void quack(){turkey->gobble();}
        void fly()
        {
            for(int i=0; i<5; i++)  // turkey cannot fly very long, so fly 5 times to get the duck's distance
                turkey->fly();
        }
};

class DuckAdapter_MI:public Duck, public WildTurkey     // using Multi-Inheritance
{
    public:
        void quack(){gobble();}
        void fly()
        {
            for(int i=0; i<5; i++)
                WildTurkey::fly();
        }
};

int main()
{
    cout<<"############# The real duck start #####################"<<endl;
    MallardDuck duck;
    duck.quack();
    duck.fly();

    cout<<"############# The real turkey start #####################"<<endl;
    WildTurkey turkey;
    turkey.gobble();
    turkey.fly();

    cout<<"############# The fake duck(turkey) start based on composition #####################"<<endl;
    DuckAdapter fakeDuck(&turkey);  // make the turkey have the same interface with duck
    fakeDuck.quack();
    fakeDuck.fly();

    cout<<"############# The fake duck(turkey) start based on inheritance #####################"<<endl;
    DuckAdapter_MI fakeDuck2;   // multi-inheritance
    fakeDuck2.quack();
    fakeDuck2.fly();
    return 0;
}


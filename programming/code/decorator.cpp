#include <iostream>
#include <string>
using namespace std;

class Beverage
{
    public:
        string description;
        double costs;
        int size;   //1,2,3 => small, medium, big
        virtual string getDescription()
        {
            string size;
            size = (this->size==1)?"small":((this->size==2)?"medium":"big");
            return size + "  " + description;
        }
        virtual double cost(){return costs*size;}
        virtual void setSize(int size){this->size=size;}
        virtual int getSize(){return size;}
        virtual void printout()
        {
            cout<<this->getDescription()<<"  costs:"<<this->cost()<<endl;
        }
};

class CondimentDecorator:public Beverage
{
    public:
        Beverage *beverage;
        CondimentDecorator(Beverage *beverage)
        {
            size = beverage->getSize();
        }
        virtual double cost()
        {
            return beverage->cost() + costs*beverage->getSize();
        }
        virtual string getDescription()
        {
            return beverage->getDescription() + ", " + description;
        }
        /*
        virtual ~CondimentDecorator()
        {
            cout<<beverage->getDescription()<<"  was called."<<endl;
            delete beverage;
        }
        */
};

class HouseBlend:public Beverage
{
    public:
        HouseBlend()
        {
            description = "HouseBlend" ;
            costs = .89;
        }
};
class Espresso:public Beverage
{
    public:
        Espresso()
        {
            description = "Espresso";
            costs = 1.99;
        }
};

class DarkRoast:public Beverage
{
    public:
        DarkRoast()
        {
            description = "DarkRoast";
            costs = .99;
        }
};
class Decaf:public Beverage
{
    public:
        Decaf()
        {
            costs = 1.05;
            description = "Decaf";
        }
};
class Mocha:public CondimentDecorator
{
    public:
        Mocha(Beverage *beverage):CondimentDecorator(beverage)
        {
            this->beverage = beverage;
            costs = 0.2;
            description = "Mocha";
        }
};
class Soy:public CondimentDecorator
{
    public:
        Soy(Beverage *beverage):CondimentDecorator(beverage)
        {
            this->beverage = beverage;
            costs = 0.15;
            description = "Soy";
        }
};
class Whip:public CondimentDecorator
{
    public:
        Whip(Beverage *beverage):CondimentDecorator(beverage)
        {
            this->beverage = beverage;
            costs = 0.10;
            description = "Whip";
        }
};


int main()
{
    DarkRoast d;
    d.setSize(2);
    Whip w(new Soy(new Whip(new Mocha(&d))));  // add the decorator as many as you need
    w.printout();

    return 0;
}
        

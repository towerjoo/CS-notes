#include<iostream>
#include<string>
#include<exception>
#include<vector>
using namespace std;

class UnsupportedOperationException:public exception
{
    public:
        virtual const char* what() const throw()
        {
            return "Not Supported Operations!";
        }
};

class MenuComponent
{
    public:
        virtual void add(MenuComponent *menuComponent)
        {
            UnsupportedOperationException ex;
            throw ex;
        }
        virtual MenuComponent* getChild(int i)
        {
            UnsupportedOperationException ex;
            throw ex;
        }

        virtual void print()
        {
            UnsupportedOperationException ex;
            throw ex;
        }

        virtual string getName()
        {
            UnsupportedOperationException ex;
            throw ex;
        }

        virtual double getPrice()
        {
            UnsupportedOperationException ex;
            throw ex;
        }
};

class MenuItem:public MenuComponent
{
    public:
        string name;
        double price;
        MenuItem(string name, double price)
        {
            this->name = name;
            this->price = price;
        }

        double getPrice(){return price;}
        string getName(){return name;}
        void print()
        {
            cout<<"Name:  "<<getName()<<"  Price:"<<getPrice()<<endl;
        }
};

class Menu:public MenuComponent
{
    public:
        string name;
        vector<MenuComponent*> menuComponents;

        Menu(string name)
        {
            this->name = name;
        }

        void add(MenuComponent *menuComponent)
        {
            menuComponents.push_back(menuComponent);
        }
        string getName(){return name;}

        MenuComponent* getChild(int i)
        {
            return menuComponents[i];
        }

        void print()
        {
            cout<<"Name:  "<<getName()<<endl;
            cout<<"--------------------------"<<endl;
            for(int i=0; i<menuComponents.size(); i++)
                menuComponents[i]->print();
        }
};

class Test
{
    public:
        MenuComponent* menuComponent;
        Test(MenuComponent* menuComponent)
        {
            this->menuComponent = menuComponent;
        }

        void printout() // handle the composite or leaf uniformly
        {
             cout<<"Name: "<<menuComponent->getName();
             try
             {
                 cout<<"  Price:"<<menuComponent->getPrice();
             }
             catch(UnsupportedOperationException error)
             {
             }
             cout<<endl;
        }
};


int main()
{

    MenuComponent *menu;
    Menu a("Menu1");
    Menu b("Menu2");
    MenuItem item1("leaf1", 23.2);
    MenuItem item2("leaf2", 2.2);

    menu = &b;
    menu->add(&item1);
    menu->add(&item2);

    menu = &a;
    menu->add(&item1);
    menu->add(&item2);

    menu->add(&b);
    menu->print();

    cout<<"######### Handle composite and leaf uniformly ########"<<endl;
    Test t(&a);
    t.printout();

    Test s(&item1);
    s.printout();
    return 0;
}



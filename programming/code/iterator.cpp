#include<iostream>
#include<vector>
#include<string>
using namespace std;

class Iterator;
class DinnaMenuIterator;
class PancakeMenuIterator;

class MenuItem
{
    public:
        string name;
        double price;

        MenuItem(string name, double price)
        {
            this->name = name;
            this->price = price;
        }
        string getName(){return name;}
        double getPrice(){return price;}
};

// PancakeMenu and DinnerMenu use the different internal representation of collection
// so we can implement a unify Iterator class to offer the same interfaces

class PancakeMenu
{
    public:
        vector<MenuItem*> items;
        PancakeMenu()
        {
            items.push_back(new MenuItem("Potato", 13.5));
            items.push_back(new MenuItem("tomato", 33.5));
            items.push_back(new MenuItem("pancake", 3.5));
        }

};

class DinnerMenu
{
    public:
        MenuItem* menuitem[6];
        DinnerMenu()
        {
            for(int i=0; i<6; i++)
                menuitem[i] = NULL;
            menuitem[0] = new MenuItem("Noodle", 45.5);
            menuitem[1] = new MenuItem("Rice", 32.4);
        }
};

class Iterator
{
    public:
        int position;
        Iterator():position(0){}
        virtual bool hasNext(){}
        virtual MenuItem* next(){}
};

class PancakeMenuIterator:public Iterator
{
    public:
        PancakeMenu *pm;
        PancakeMenuIterator(PancakeMenu *pm)
        {
            position = 0;
            this->pm = pm;
        }
        bool hasNext()
        {
            if (position<pm->items.size() && position>=0)
                return true;
            else
                return false;
        }
        MenuItem* next()
        {
            return pm->items[position++];
        }
};

class DinnaMenuIterator:public Iterator
{
    public:
        DinnerMenu *dm;
        DinnaMenuIterator(DinnerMenu *dm)
        {
            position = 0;
            this->dm = dm;
        }
        bool hasNext()
        {
            if (position<6 && dm->menuitem[position] != NULL)
                return true;
            else
                return false;
        }
        MenuItem* next()
        {
            return dm->menuitem[position++];
        }
};

class Waitress
{
    public:
        PancakeMenuIterator *pmi;
        DinnaMenuIterator *dmi;

        Waitress(PancakeMenuIterator *pmi, DinnaMenuIterator *dmi)
        {
            this->pmi = pmi;
            this->dmi = dmi;
        }
        void printAllMenu()
        {
            printMenu(pmi);
            printMenu(dmi);
        }
    private:
        void printMenu(Iterator *iter)
        {
            while(iter->hasNext())
            {
                MenuItem *mi = iter->next();
                cout<<"Name: "<<mi->getName()<<"   Price:"<<mi->getPrice()<<endl;
            }
        }
};




int main()
{
    PancakeMenu pm;
    cout<<pm.items[0]->getName()<<endl;

    DinnerMenu dm;
    cout<<dm.menuitem[0]->getName()<<endl;

    PancakeMenuIterator pmi(&pm);
    DinnaMenuIterator dmi(&dm);

    // the following comments show the same interfaces of different Iterator
    /*
    cout<<"###### Pancake using Iterator pattern #########"<<endl;
    while(pmi.hasNext())
    {
        MenuItem *mi = pmi.next();
        cout<<"Name:"<<mi->getName()<<"   Price:"<<mi->getPrice()<<endl;
    }
    cout<<"###### Dinner using Iterator pattern #########"<<endl;
    while(dmi.hasNext())
    {
        MenuItem *mi = dmi.next();
        cout<<"Name:"<<mi->getName()<<"   Price:"<<mi->getPrice()<<endl;
    }
    */

    cout<<"####### Waitress start ###############"<<endl;
    Waitress waitress(&pmi, &dmi);
    waitress.printAllMenu();
    return 0;
}




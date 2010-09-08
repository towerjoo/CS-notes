#include<iostream>
#include<string>
using namespace std;

class CaffeineBeverage
{
    public:
        void prepareRecipe()
        {
            boildWater();
            brew();
            pourInCup();
            if (customerWantsCondiments())
            {
                addCondiments();
            }
        }
        void boildWater(){cout<<"Boiling water."<<endl;}
        void pourInCup(){cout<<"Pouring into cup."<<endl;}

        virtual void brew(){}
        virtual void addCondiments(){}

        virtual bool customerWantsCondiments(){return true;}    // the hook to offer a way to change the algorithm
};

class Coffee:public CaffeineBeverage
{
    public:
        void brew(){cout<<"Dripping Coffee through filter."<<endl;}
        void addCondiments(){cout<<"Adding sugar and Milk"<<endl;}

        bool customerWantsCondiments()
        {
            char choice;
            while(true)
            {
                cout<<"Whether you wanna add sugar and milk?(y/n)"<<endl;
                cin>>choice;
                if (choice == 'y' || choice == 'n')
                    break;
            }
            return choice=='y'?true:false;
        }
};
class Tea:public CaffeineBeverage
{
    public:
        void brew(){cout<<"Dripping Tea through filter."<<endl;}
        void addCondiments(){cout<<"Adding lemon"<<endl;}

        bool customerWantsCondiments()
        {
            char choice;
            while(true)
            {
                cout<<"Whether you wanna add lemon?(y/n)"<<endl;
                cin>>choice;
                if (choice == 'y' || choice == 'n')
                    break;
            }
            return choice=='y'?true:false;
        }
};

int main()
{
    Coffee coffee;
    Tea tea;
    cout<<"##### Preparing the Coffee ######"<<endl;
    coffee.prepareRecipe();
    cout<<"##### Preparing the Tea ######"<<endl;
    tea.prepareRecipe();
    return 0;
}



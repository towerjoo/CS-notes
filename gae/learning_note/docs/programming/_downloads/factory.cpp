#include<iostream>
#include<string>
#include<vector>
using namespace std;

class Pizza;
class NYStyleCheesPizza;
class NYStyleVeggiePizza;
class NYStyleClamPizza;
class NYStylePepperoniPizza;
class ChicagoStyleCheesPizza;
class ChicagoStyleVeggiePizza;
class ChicagoStyleClamPizza;
class ChicagoStylePepperoniPizza;

class PizzaStore;
class NYPizzaStore;
class ChicagoPizzaStore;

class Pizza
{
    public:
        string name;
        string dough;
        string sauce;
        vector<string> toppings;

        void prepare()
        {
            cout<<"Preparing "<<name<<endl;
            cout<<"Tossing dough..."<<endl;
            cout<<"Adding sauce..."<<endl;
            cout<<"Adding toppings:"<<endl;
            for(int i=0; i<toppings.size(); i++)
                cout<<"    "<<toppings[i]<<endl;
        }
        void bake()
        {
            cout<<"Bake for 25 minutes at 350"<<endl;
        }
        void cut()
        {
            cout<<"Cutting the pizza into diagonal slices"<<endl;
        }
        void box()
        {
            cout<<"Place the pizza in official PizzaStore box"<<endl;
        }
        string getName()
        {
            return name;
        }
};

class PizzaStore
{
    public:
        Pizza* orderPizza(string type)
        {
            Pizza *pizza;
            pizza = createPizza(type);
            pizza->prepare();
            pizza->bake();
            pizza->cut();
            pizza->box();
            return pizza;
        }
        virtual Pizza* createPizza(string type){}
};

class NYStyleCheesPizza:public Pizza
{
    public:
        NYStyleCheesPizza()
        {
            name = "NY Style Sauce and Cheese Pizza";
            dough = "Thin Crust Dough";
            sauce = "Marinara Sauce";

            toppings.push_back("Grated Reggiano Cheese");
        }
};
class NYStylePepperoniPizza:public Pizza
{
    public:
        NYStylePepperoniPizza()
        {
            name = "NY Style Sauce and Pepperoni Pizza";
            dough = "Thin Crust Dough";
            sauce = "Marinara Sauce";

            toppings.push_back("Grated Reggiano Pepperoni");
        }
};
class NYStyleClamPizza:public Pizza
{
    public:
        NYStyleClamPizza()
        {
            name = "NY Style Sauce and Clam Pizza";
            dough = "Thin Crust Dough";
            sauce = "Marinara Sauce";

            toppings.push_back("Grated Reggiano Clam");
        }
};
class NYStyleVeggiePizza:public Pizza
{
    public:
        NYStyleVeggiePizza()
        {
            name = "NY Style Sauce and Veggie Pizza";
            dough = "Thin Crust Dough";
            sauce = "Marinara Sauce";

            toppings.push_back("Grated Reggiano Veggie");
        }
};
class ChicagoStyleCheesPizza:public Pizza
{
    public:
        ChicagoStyleCheesPizza()
        {
            name = "Chicago Style Sauce and Cheese Pizza";
            dough = "Thin Crust Dough";
            sauce = "Marinara Sauce";

            toppings.push_back("Grated Reggiano Cheese");
        }
};
class ChicagoStylePepperoniPizza:public Pizza
{
    public:
        ChicagoStylePepperoniPizza()
        {
            name = "Chicago Style Sauce and Pepperoni Pizza";
            dough = "Thin Crust Dough";
            sauce = "Marinara Sauce";

            toppings.push_back("Grated Reggiano Pepperoni");
        }
};
class ChicagoStyleClamPizza:public Pizza
{
    public:
        ChicagoStyleClamPizza()
        {
            name = "Chicago Style Sauce and Clam Pizza";
            dough = "Thin Crust Dough";
            sauce = "Marinara Sauce";

            toppings.push_back("Grated Reggiano Clam");
        }
};
class ChicagoStyleVeggiePizza:public Pizza
{
    public:
        ChicagoStyleVeggiePizza()
        {
            name = "Chicago Style Sauce and Veggie Pizza";
            dough = "Thin Crust Dough";
            sauce = "Marinara Sauce";

            toppings.push_back("Grated Reggiano Veggie");
        }
};



class NYPizzaStore:public PizzaStore
{
    public:
        Pizza* createPizza(string type)
        {
            if (type == "cheese")
            {
                return new NYStyleCheesPizza();
            }
            else if (type=="veggie")
            {
                return new NYStyleVeggiePizza();
            }
            else if (type == "clam")
            {
                return new NYStyleClamPizza();
            }
            else if (type == "pepperoni")
            {
                return new NYStylePepperoniPizza();
            }
        }
};
class ChicagoPizzaStore:public PizzaStore
{
    public:
        Pizza* createPizza(string type)
        {
            if (type == "cheese")
            {
                return new ChicagoStyleCheesPizza();
            }
            else if (type=="veggie")
            {
                return new ChicagoStyleVeggiePizza();
            }
            else if (type == "clam")
            {
                return new ChicagoStyleClamPizza();
            }
            else if (type == "pepperoni")
            {
                return new ChicagoStylePepperoniPizza();
            }
        }
};




int main()
{
    PizzaStore *nyStore = new NYPizzaStore();
    PizzaStore *chicagoStore = new ChicagoPizzaStore();

    Pizza *pizza = nyStore->orderPizza("cheese");
    cout<<"Ethan ordered a "<<pizza->getName()<<endl<<endl;

    pizza = chicagoStore->orderPizza("clam");
    cout<<"Joel ordered a "<<pizza->getName()<<endl<<endl;
    return 0;
}

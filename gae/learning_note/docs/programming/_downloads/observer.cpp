#include<iostream>
#include<vector>
#include<string>
using namespace std;

class Observer
{
    public:
        virtual void update(float temp, float humidity, float pressure){}
};

class Subject
{
    public:
        virtual void registerObserver(Observer o){};
        virtual void removeObserver(Observer o){};
        virtual void notifyObserver(){};
};

class DisplayElement
{
    public:
        virtual void display(){};
};

class WeatherData:public Subject
{
    public:
        vector<Observer*> observers;
        float temperature;
        float humidity;
        float pressure;

        void registerObserver(Observer *o)
        {
            observers.push_back(o);
        }
        void removeObserver(Observer *o)
        {
            for(int i=0; i<observers.size(); i++)
                if (observers.at(i) == o)
                {
                    observers.erase(observers.begin()+i);
                    break;
                }
        }
        void notifyObserver()
        {
            for(int i=0; i<observers.size(); i++)
            {
                observers[i]->update(temperature, humidity, pressure);  // 这是一种 push的方式
            }
        }
        void measurementsChanged()
        {
            notifyObserver();
        }
        void setMeasurements(float temp, float hum, float pres)
        {
            temperature = temp;
            humidity = hum;
            pressure = pres;
            measurementsChanged();
        }
        float getTemperature(){return temperature;}
        float getHumidity(){return humidity;}
        float getPressure(){return pressure;}
};

class CurrentConditionDisplay:public Observer, public DisplayElement
{
    private:
        float temperature;
        float humidity;

    public:
        void update(float temp, float humidity, float pressure)
        {
            this->temperature = temp;
            this->humidity = humidity;
            display();
        }
        void display()
        {
            cout<<"Current Conditions"<<endl;
            cout<<"temperature:"<<temperature<<endl;
            cout<<"humidity:"<<humidity<<"%"<<endl;
            cout<<endl<<endl;
        }
};

class ForcastConditionDisplay:public Observer, public DisplayElement
{
    private:
        float temperature;
        float humidity;
        float pressure;
        
    public:
        void update(float temp, float humidity, float pressure)
        {
            this->temperature = temp;
            this->humidity = humidity;
            this->pressure = pressure;
            display();
        }
        void display()
        {
            cout<<"Forcast"<<endl;
            cout<<"temperature:"<<temperature<<endl;
            cout<<"humidity:"<<humidity<<"%"<<endl;
            cout<<"pressure:"<<pressure<<endl;
            cout<<endl;
        }
};

int main()
{
    Subject *s;
    WeatherData weather;
    s = &weather;
    CurrentConditionDisplay currentDisplay;
    CurrentConditionDisplay currentDisplay2;
    ForcastConditionDisplay forcastDisplay;

    weather.registerObserver(&currentDisplay);
    weather.registerObserver(&currentDisplay2);
    weather.registerObserver(&forcastDisplay);

    weather.setMeasurements(80,62,30.4);
    weather.removeObserver(&currentDisplay2);
    weather.setMeasurements(80,62,30.4);
    return 0;
}




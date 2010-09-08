#include<iostream>
#include<string>
using namespace std;

class Device
{
    public:
        string name;
        virtual void on(){cout<<name<<" is on."<<endl;}
        virtual void play(){cout<<name<<" is playing."<<endl;}
        virtual void off(){cout<<name<<" is off."<<endl;}
};

class DVD:public Device
{
    public:
        DVD(){name="DVD";}
};
class Amplifier:public Device
{
    public:
        Amplifier(){name="Amplifier";}
};
class Projector:public Device
{
    public:
        Projector(){name="Projector";}
};

class FacadeThreater
{
    private:
        DVD* dvd;
        Amplifier* amplifier;
        Projector* projector;
    public:
        FacadeThreater(DVD *dvd, Amplifier *amplifier, Projector *projector)
        {
            this->dvd = dvd;
            this->amplifier = amplifier;
            this->projector = projector;
        }
        void playMovie()
        {
            dvd->on();
            projector->on();
            amplifier->on();
            dvd->play();
        }
        void stopMovie()
        {
            amplifier->off();
            projector->off();
            dvd->off();
        }
};

int main()
{
    DVD dvd;
    Amplifier amplifier;
    Projector projector;
    // non-facade method
    // play movie
    cout<<"################# Non-facade Pattern ####################"<<endl;
    dvd.on();
    projector.on();
    amplifier.on();
    dvd.play();

    // using facade pattern
    cout<<"################# Facade Pattern ####################"<<endl;
    FacadeThreater ft(&dvd, &amplifier, &projector);
    ft.playMovie();
    return 0;
}

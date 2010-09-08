#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Command
{
    public:
        virtual void execute(){}
        virtual void undo(){}
};
class Light
{
    public:
        void on(){cout<<"The light is on"<<endl;}
        void off(){cout<<"The light is off"<<endl;}
};
class Fan
{
    public:
        static const int HIGH=3;
        static const int MEDIUM = 2;
        static const int LOW = 1;
        static const int OFF = 0;
        int speed;
        void show_current_speed()
        {
            cout<<"Current Speed of fan:"<<getSpeed()<<endl;
        }

        void high(){speed=HIGH;show_current_speed();}
        void medium(){speed=MEDIUM;show_current_speed();}
        void low(){speed=LOW;show_current_speed();}
        void off(){speed=OFF;show_current_speed();}
        int getSpeed(){return speed;}
};
class FanHighCommand:public Command
{
    private:
        Fan* fan;
        int prevSpeed;
    public:
        FanHighCommand(Fan* fan)
        {
            this->fan = fan;
        }
        void execute()
        {
            prevSpeed = fan->getSpeed();
            fan->high();
        }
        void undo()
        {
            switch(prevSpeed)
            {
                case Fan::HIGH:
                    fan->high();
                    break;
                case Fan::MEDIUM:
                    fan->medium();
                    break;
                case Fan::LOW:
                    fan->low();
                    break;
                case Fan::OFF:
                    fan->off();
                    break;
                default:
                    break;
            }
        }
};
class LightOffCommand:public Command
{
    private:
        Light* light;
    public:
        LightOffCommand(Light* light)
        {
            this->light = light;
        }
        void execute()
        {
            light->off();
        }
        void undo()
        {
            light->on();
        }
};


class LightOnCommand:public Command
{
    private:
        Light* light;
    public:
        LightOnCommand(Light* light)
        {
            this->light = light;
        }
        void execute()
        {
            light->on();
        }
        void undo()
        {
            light->off();
        }
};
class NoCommand:public Command  //as the default command, which no other commands suit
{
};


class SimpleRemoteControl
{
    private:
        vector<Command *> onCommands;
        vector<Command *> offCommands;
        Command *undoCommand;

    public:
        SimpleRemoteControl(){}

        void setCommand(Command* onCommand, Command* offCommand)
        {
            onCommands.push_back(onCommand);
            offCommands.push_back(offCommand);
        }
        void onButtonWasPressed(int which)
        {
            onCommands[which]->execute();
            undoCommand = onCommands[which];
        }
        void offButtonWasPressed(int which)
        {
            offCommands[which]->execute();
            undoCommand = offCommands[which];
        }
        void undoButtonPressed()    //invoke the undo action
        {
            undoCommand->execute();
        }
};

int main()
{
    SimpleRemoteControl remote;
    LightOnCommand lightOn(new Light());
    LightOffCommand lightOff(new Light());
    remote.setCommand(&lightOn, &lightOff);
    FanHighCommand fanHigh(new Fan());
    remote.setCommand(&fanHigh, &fanHigh);
    remote.onButtonWasPressed(0);
    remote.offButtonWasPressed(0);
    remote.offButtonWasPressed(1);
    remote.undoButtonPressed();
    return 0;
}
        

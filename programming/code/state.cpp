/*
 * Author: Tower Joo<zhutao.iscas@gmail.com>
 * Time: 2009-06-11 14:32
 * File: state.cpp
 * Description: This source file is to implement the state design pattern.
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class TCPconnection;

class State
{
    public:
        virtual void Open(){}
        virtual void Close(){}
        virtual void Acknowledge(){}
};



class TCPopen:public State
{
    public:
        TCPconnection *tcp;
        TCPopen(TCPconnection* tcp)
        {
            this->tcp = tcp;
        }
        void Open()
        {
            cout<<"The Tcp is already opened."<<endl;
        }
        void Acknowledge();
        void Close();
        
};
class TCPclose:public State
{
    public:
        TCPconnection *tcp;
        TCPclose(TCPconnection* tcp)
        {
            this->tcp = tcp;
        }
        
        void Acknowledge()
        {
            cout<<"The Tcp is not opened yet."<<endl;
        }
        void Close()
        {
            cout<<"The Tcp is already close."<<endl;
        }
        void Open();
};

class TCPacknowledge:public State
{
    public:
        TCPconnection *tcp;
        TCPacknowledge(TCPconnection* tcp)
        {
            this->tcp = tcp;
        }
        void Open()
        {
            cout<<"The Tcp is already open"<<endl;
        }
        void Acknowledge()
        {
            cout<<"The Tcp is already acknowleged."<<endl;
        }
        void Close();
};

class TCPconnection
{
    public:
        State *state;
        TCPconnection()
        {
            state = new TCPclose(this);
        }
        void Open()
        {
            state->Open();
        }
        void Close()
        {
            state->Close();
        }
        void Acknowledge()
        {
            state->Acknowledge();
        }
        void setState(State *state)
        {
            this->state = state;
        }
        State* getTCPclose()
        {
            return new TCPclose(this);
        }
        State* getTCPopen()
        {
            return new TCPopen(this);
        }
        State* getTCPacknowledge()
        {
            return new TCPacknowledge(this);
        }
};
// because the classes have cross-reference
// so the following methods MUST be defined after TCPconnection
void TCPopen::Acknowledge()
{
    cout<<"The Tcp is acknowleged."<<endl;
    tcp->setState(tcp->getTCPacknowledge());
}
void TCPopen::Close()
{
    cout<<"Yeah. The Tcp is close."<<endl;
    tcp->setState(tcp->getTCPclose());
}
void TCPclose::Open()
{
    cout<<"The Tcp is open"<<endl;
    tcp->setState(tcp->getTCPopen());
}
void TCPacknowledge::Close()
{
    cout<<"The Tcp is closed."<<endl;
    tcp->setState(tcp->getTCPclose());
}

int main()
{
    TCPconnection tcp;
    tcp.state->Open();
    tcp.state->Acknowledge();
    tcp.state->Close();

    tcp.state->Acknowledge();// will not acknowleged, since the tcp is not open
	return 0;
}

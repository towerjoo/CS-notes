/*
 * Author: Tower Joo<zhutao.iscas@gmail.com>
 * Time: 2009-06-11 20:18
 * File: proxy.cpp
 * Description: This source file is to implement the proxy design pattern.
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Image
{
    public:
        virtual void displayImage(){}
};

class RealImage:public Image
{
    private:
        string filename;
    public:
        RealImage(string name):filename(name)
        {
            loadImageFromDisk();    // an expensive operation, may from network
        }
        void displayImage()
        {
            cout<<"Displaying Image "<<filename<<endl;
        }
        void loadImageFromDisk()
        {
            cout<<"Loading "<<filename<<endl;
        }
};

// the proxy which provide the access control to the expensive operation(load file from disk)
class ImageProxy:public Image
{
    private:
        string filename;
        Image *image;
    public:
        ImageProxy(string name):filename(name){image = NULL;}
        void displayImage()
        {
            if (image == NULL)
            {
                image = new RealImage(filename);
            }
            image->displayImage();
        }
};

int main()
{
    ImageProxy image1("image1");
    ImageProxy image2("image2");
    ImageProxy image3("image3");

    image1.displayImage();
    image2.displayImage();
    image1.displayImage();  // this will not load the file for the second time

	return 0;
}

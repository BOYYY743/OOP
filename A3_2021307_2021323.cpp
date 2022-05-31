#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <windows.h>
#define TWO_PI 6.28
using namespace std;

class Donut
{
    //private by default//
    //variables 
    int res, width, height, r, center, x, y, z, K2, val;
    float A, B, xcordi, ycordi, z_, ooz, costheta, sintheta, cosPhi, sinPhi, cosA, sinA, theta, Phi, sinB, cosB, kum, * z_buff;
    char* arr, print;

public:
    /*
    * @brief sets default values for donut to run as initial default donut
    */
    Donut() //creates donut class
    {
        //initializing values to donut so when class is called it assigns the values//
        res = 3000;
        width = 60;
        height = 60;
        A = 0;
        B = 0;
        ooz = 0;
        Phi = 0;
        theta = 0;
        K2 = 5;
        center = 6;
        r = 3;
        z = 50;
    }
    /*
    * @brief clears memory when the program is over so there is no memory leakage
    */
    ~Donut()
    {
        delete[] arr;
        delete[] z_buff;
    }


    void createDonut()
    {
        arr = new char[res];//Declaring a dynamic array as picture res//
        z_buff = new float[res];//z buffer stores the z coordinates//

        while (1)//major loop which keeps the donut printing unless stopped//
        {
            for (int i = 0; i < res; i++)
            {
                arr[i] = ' ';//setting the screen blank at the start
                z_buff[i] = 0;//setting z coordinate to zero at start
            }

            for (theta = 0; theta < TWO_PI; theta += 0.02)//donut rotates on the axis which are varied with thetha and phi
            {                                             //it can increase speed of rotation and determines how smoothly it rotates
                for (Phi = 0; Phi < TWO_PI; Phi += 0.05)
                {
                    //declaring mathematical values to calculate to do the math for the donut
                    costheta = cos(theta);
                    sintheta = sin(theta);
                    cosPhi = cos(Phi);
                    sinPhi = sin(Phi);
                    cosA = cos(A);
                    sinA = sin(A);
                    cosB = cos(B);
                    sinB = sin(B);
                    //calculatuing coordinates with help of formulae given in assignment
                    xcordi = ((center + (r * costheta)) * (cosB * cosPhi + sinA * sinB * sinPhi)) - (r * cosA * sinB * sintheta);

                    ycordi = ((center + r * costheta) * (cosPhi * sinB - cosB * sinA * sinPhi)) + (r * cosA * cosB * sintheta);

                    z_ = (z + K2) / 2 + (cosA * (center + r * costheta) * sinPhi) + (r * sinA * sintheta);

                    int lum = 8 * ((cosPhi * costheta * sinB) - (cosA * costheta * sinPhi) - (sinA * sintheta) + (cosB * (cosA * sintheta - costheta * sinA * sinPhi)));


                    x = (width / 2) + (z * xcordi) / (K2 + z_);
                    y = (height / 2) + (z * ycordi) * 0.75 / (K2 + z_);
                    val = x + (width * y);
                    ooz = (1 / z_);

                    if (x < width && y < height && x>0 && y>0 && ooz > z_buff[val])//ask about the arr[val] thing
                    {
                        z_buff[val] = ooz;
                        arr[val] = ".,-~:;=!*#$@"[lum / 8 > 0 ? lum : 0/* if (lum/8 > 0) { lum = 0; }*/];//question //
                    }
                }
            }
            for (int i = 0; i < res; i++)//loop used to print out the values on the screen and display the donut
            {
                if (i % width)
                {
                    print = arr[i];
                }
                else
                {
                    print = '\n';
                }

                cout << print;

            }

            A += 0.25;//controls speed of rotation of donut
            B += 0.25;
            system("cls");//clears screen after a single iteration of printing the loop so//works with the frames per second ideology//
            Sleep(100);//sleep to make it print fast or slow
        }
    }


};

int main()
{
    Donut d;//instance of class declared
    d.createDonut();//function of class called//

    return 0;
}

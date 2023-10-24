#include "mouse.h"
double Mouse::x = 0;
double Mouse::y = 0;
double Mouse::last_x = 0;
double Mouse::last_y = 0;
float Mouse::dx = 0; 
float Mouse::dy = 0;
bool   Mouse::first_time= true;

void Mouse::curser_keycallback(GLFWwindow* window, double xpos, double ypos)
{
	
    x = xpos;
    y = ypos;
    if (first_time)
    {
        last_x = x;
        last_y = y;
        first_time = false;
    }
    dx = last_x - x;
    dy = last_y - y;
    last_x = x;
    last_y = y;
	
}

float Mouse::Get_dx()
{
    float temp = dx;
    dx = 0;
    return temp;
}

float Mouse::Get_dy()
{
    float temp = dy;
    dy = 0;
    return temp;
}

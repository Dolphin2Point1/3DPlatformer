#include <irrlicht.h>
#include <iostream>
using namespace irr;

int main() {
    // ask user for driver

    video::E_DRIVER_TYPE driverType;

    printf("Please select the driver you want for this example:\n"\
        " (a) OpenGL 1.5\n (b) Direct3D 9.0c\n (c) Direct3D 8.1\n"\
        " (d) Burning's Software Renderer\n (e) Software Renderer\n"\
        " (f) NullDevice\n (otherKey) exit\n\n");

    char i;
    std::cin >> i;

    switch(i)
    {
        case 'a': driverType = video::EDT_OPENGL;   break;
        case 'b': driverType = video::EDT_DIRECT3D9;break;
        case 'c': driverType = video::EDT_DIRECT3D8;break;
        case 'd': driverType = video::EDT_BURNINGSVIDEO;break;
        case 'e': driverType = video::EDT_SOFTWARE; break;
        case 'f': driverType = video::EDT_NULL;     break;
        default: return 1;
    }

    // create device and exit if creation failed

    IrrlichtDevice *device =
            createDevice(driverType, core::dimension2d<u32>(640, 480));

    if (device == 0)
        return 1; // could not create selected driver.
	return 0;
}
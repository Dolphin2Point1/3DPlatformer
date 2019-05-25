#include <irrlicht.h>
#include <iostream>
using namespace irr;

int main() {
    int Rotatex,Rotatey,Rotatez;
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
            createDevice(driverType, core::dimension2d<u32>(640, 480), 16, false, false, true, 0);

    if (device == 0)
        return 1; // could not create selected driver.
    device->setWindowCaption(L"Hello World! - Irrlicht Engine Demo");
    video::IVideoDriver* driver = device->getVideoDriver();
    scene::ISceneManager* smgr = device->getSceneManager();
    gui::IGUIEnvironment* guienv = device->getGUIEnvironment();
    guienv->addStaticText(L"Hello World! This is the Irrlicht Software renderer!",
                          core::rect<s32>(10,10,260,22), true);
    scene::IAnimatedMesh* mesh = smgr->getMesh("../assets/box.dae");
    if(!mesh) {
        device->drop();
        return 1;
    }
    scene::IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode(mesh);
    if(node) {
        node->setMaterialFlag(video::EMF_LIGHTING, false);
        node->setMD2Animation(scene::EMAT_STAND);
        node->setMaterialTexture(0, driver->getTexture("../assets/box.png"));
    }
    smgr->addCameraSceneNode(0, core::vector3df(0,10,0), core::vector3df(0,5,0));
    while(device->run()) {
        driver->beginScene(true, true, video::SColor(255,100,101,140));
        node->setRotation(core::vector3df(node->getRotation().X + 10, node->getRotation().Y + 10,node->getRotation().Z + 10));
        smgr->drawAll();
        guienv->drawAll();

        driver->endScene();
    }
    device->drop();
    return 0;
}
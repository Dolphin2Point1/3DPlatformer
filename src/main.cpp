#include <irrlicht.h>

#include "main.h"

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif


class Main {
    public: static int createDevice() {
        irr::IrrlichtDevice *device = irr::createDevice(irr::video::EDT_SOFTWARE,
                                                        irr::core::dimension2d<irr::u32>(640, 480), 16,
                                                        false, false, false, 0);
        if (!device)
            return 1;
        device->setWindowCaption(L"Hello World! - Irrlicht Engine Demo");
        irr::video::IVideoDriver* driver = device->getVideoDriver();
        irr::scene::ISceneManager* smgr = device->getSceneManager();
        irr::gui::IGUIEnvironment* guienv = device->getGUIEnvironment();
        guienv->addStaticText(L"Hello World! This is the Irrlicht Software renderer!",
                              irr::core::rect<irr::s32>(10,10,260,22), true);

    }


};
int main() {
    Main::createDevice();
    return 0;
}
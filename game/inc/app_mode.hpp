#pragma once
#ifndef APP_MODE
#define APP_MODE

#include "scene.hpp"
#include "ui_constants.hpp"
#include <memory>

#include <raylib.h>


namespace app {

class AppModeBase {
public:
    AppModeBase(std::shared_ptr<render::Scene> scene) :
        m_scene{scene}
    {

    }
    virtual void update() = 0;
    virtual void draw() = 0;

protected:
    std::shared_ptr<render::Scene> m_scene;


private:



};

}



#endif // APP_MODE
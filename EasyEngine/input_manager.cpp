// ì¬Ò : ”Âê
/******************************************************************************

    include

******************************************************************************/
#include "input_manager.hpp"


/******************************************************************************

    definition & declaration

******************************************************************************/
namespace imanager_ns = easy_engine::i_lib;


/******************************************************************************

    InputManager::

******************************************************************************/
std::unique_ptr<imanager_ns::InputManager> imanager_ns::InputManager::create() {
    return std::unique_ptr<InputManager>{new InputManager{}};
}

void imanager_ns::InputManager::update() {
    for(auto& device : devices_)
        device.second->update();
}
// EOF

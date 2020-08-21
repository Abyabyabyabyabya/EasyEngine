// çÏê¨é“ : î¬èÍ
/******************************************************************************

    include

******************************************************************************/
#include "input_manager.hpp"
#include "keyboard.hpp"


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

void imanager_ns::InputManager::keyEvent(const UINT Msg, const WPARAM wPrm, const LPARAM lPrm) const noexcept {
    auto device_itr = devices_.find(t_lib::TypeIDGenerator<Keyboard>{});
    if(device_itr != devices_.end()) {
        static_cast<Keyboard*>(device_itr->second.get())->eventProcessing(Msg, wPrm, lPrm);
    }
}
// EOF

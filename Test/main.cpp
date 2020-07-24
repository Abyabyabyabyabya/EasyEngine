#include <iostream>
#include "egeg.hpp"
#include "id.hpp"
#include "event_container.hpp"
#include <array>
static char moji[] = "hogehoge";
static constexpr auto name = egeg::t_lib::StringGenerator<moji>{};
static constexpr int gen = egeg::t_lib::ConstantGenerator<0>{};
static constexpr char* a = nullptr;

class Base {
public :
    virtual void out() = 0;
};
class Der : public Base {
public :
    static std::unique_ptr<Der> create() { return std::make_unique<Der>(); }
    Der() { out(); }
    void out() override { std::cout << "Der" << std::endl; }
};
class Apple : public Base {
public :
    static std::unique_ptr<Apple> create() { return std::make_unique<Apple>(); }
    Apple() { out(); }
    void out() override { std::cout << "Apple" << std::endl; }
};


int main() {
    //egeg::t_lib::EventStack<void()> stack;
    std::deque<std::function<void()>> stack;
    stack.push_back([]()noexcept{std::cout << "call 0" << '\n';});
    stack.push_front([]()noexcept{std::cout << "call 1" << '\n';});

    egeg::t_lib::EventQueue<void()> events(std::move(stack));
    noexcept(events.pop_with_call());
    noexcept(events.call());
    noexcept(events.top());
    events.pop_with_call();
    try {
    events.pop_with_call();
    } catch(std::exception& e) {
        std::cout << e.what() << std::endl;
    }   
    egeg::t_lib::EventStack<int(), std::list> a;
    using event_type = std::function<void()>;
    egeg::t_lib::EventStack<void()> c;
    egeg::t_lib::EventStack<void(), std::list> e;
    using STDMap = std::map<int, std::function<void()>>;
    using EGEGMap = egeg::t_lib::EventMap<int, void()>;
}

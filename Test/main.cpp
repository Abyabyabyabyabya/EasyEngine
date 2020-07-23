#include <iostream>
#include "egeg.hpp"
#include "id.hpp"
#include "event_container.hpp"

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
    stack.push_back([](){std::cout << "call 0" << '\n';});
    stack.push_front([](){std::cout << "call 1" << '\n';});

    egeg::t_lib::EventStack<void()> events(std::move(stack));
    events.pop_with_call();
    events.pop_with_call();
    try {
    events.pop_with_call();
    } catch(egeg::t_lib::BadEventCall&) {
        std::cout << "handle exception" << std::endl;
    }
}

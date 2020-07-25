#include <iostream>
#include "egeg.hpp"
#include "id.hpp"
#include "event_container.hpp"
#include "task_manager.hpp"

using namespace easy_engine::t_lib;

using Task = impl::EventType<void()>;

int main() {
    TaskManager<Task> tsys;
    TaskManager<void()> t;

    auto task = tsys.registerTask([](){std::cout << "a" << std::endl;});
    auto buf = tsys.registerTask([](){std::cout << "buf" << std::endl;});
    auto t1 = t.registerTask([](){std::cout << "fun" << std::endl;});

    tsys.run();
    
    tsys.unregisterTask(task);
    tsys.unregisterTask(buf);
    task = tsys.registerTask([](){std::cout << "again" << std::endl;});
    buf = tsys.registerTask([](){std::cout << "buf again" << std::endl;});

    TaskManager<Task>::TaskInfo ta;
    ta = tsys.registerTask([](){std::cout << "ta" << std::endl;});

    tsys.run();

}


#include <iostream>
#include <MOL/Application/core.hpp>

int main(int argc, char *argv[]) {
    std::cout << "\n Hello again, old friend \n" << std::endl;
    Core::Engine main_application;
    main_application.get_instance();
    if (main_application.init() == 1) {
	return 1;
    }
    return 0;
}


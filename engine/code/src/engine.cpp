
#include <iostream>
#include <MOL/Application/core.hpp>

int main(int argc, char *argv[])
{
    Core::Engine engine;
    engine.get_instance();
    if (engine.init() == 1) return 1;
    return 0;
}


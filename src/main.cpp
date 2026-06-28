#include "core/Application.h"
#include <iostream>

int main(int argc, char** argv) {
    try {
        Application app;
        app.parseArgs(argc, argv);
        app.init();
        app.run();
        app.cleanup();
    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

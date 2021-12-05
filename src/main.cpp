#include <iostream>
#include <format>

import <GLFW/glfw3.h>;
import openhomm.math;
import openhomm.application;


#if defined(WIN32) && defined(_MSC_VER)
#   ifdef __clang__
#       pragma clang diagnostic push
#       pragma clang diagnostic ignored "-Wlanguage-extension-token"
#       pragma clang diagnostic ignored "-Wmissing-variable-declarations"
#   endif
extern "C" {
    // https://gpuopen.com/amdpowerxpressrequesthighperformance/
    _declspec(dllexport) unsigned long AmdPowerXpressRequestHighPerformance = 0x00000001;
    // https://docs.nvidia.com/gameworks/content/technologies/desktop/optimus.htm
    _declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
}
#   ifdef __clang__
#       pragma clang diagnostic pop
#   endif
#endif

auto main([[maybe_unused]] int  argc, [[maybe_unused]] char** argv) -> int {
    Application app(argc, argv);
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Hello modules", nullptr, nullptr);

    if (!window) {
        std::cout << "Error" << std::endl;
        glfwTerminate();
        exit(1);
    }

    glfwSetMouseButtonCallback(window, []([[maybe_unused]] GLFWwindow* window, int button, int action, int mods) {
        std::cout << std::format("glfwSetMouseButtonCallback({},{},{})\n", button, action, mods);
    });

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();

    return 0;
}
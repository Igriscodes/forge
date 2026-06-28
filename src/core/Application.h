#pragma once

#include <string>
#include <vector>

enum class RunMode {
    Benchmark,
    Stress,
    Quick,
    Scenario
};

class Engine;

class Application {
public:
    Application();
    ~Application();

    void parseArgs(int argc, char** argv);
    void init();
    void run();
    void cleanup();

private:
    RunMode m_mode;
    std::string m_scenario;
    std::string m_targetGpu;
    bool m_verbose;
    Engine* m_engine;
};

#include "Application.h"
#include "Engine.h"
#include <iostream>
#include <cstring>

Application::Application() : m_mode(RunMode::Benchmark), m_targetGpu("all"), m_verbose(false), m_engine(nullptr) {}

Application::~Application() {
    delete m_engine;
}

void Application::parseArgs(int argc, char** argv) {
    bool modeSet = false;
    for (int i = 1; i < argc; ++i) {
        if (std::strcmp(argv[i], "--benchmark") == 0) {
            m_mode = RunMode::Benchmark;
            modeSet = true;
        } else if (std::strcmp(argv[i], "--stress") == 0) {
            m_mode = RunMode::Stress;
            modeSet = true;
            if (i + 1 < argc && argv[i+1][0] != '-') {
                m_scenario = argv[++i];
            }
        } else if (std::strcmp(argv[i], "--scenario") == 0) {
            if (i + 1 < argc) {
                m_scenario = argv[++i];
                if (!modeSet) {
                    m_mode = RunMode::Scenario;
                    modeSet = true;
                }
            }
        } else if (std::strcmp(argv[i], "--mode") == 0) {
            if (i + 1 < argc) {
                m_scenario = argv[++i];
            }
        } else if (std::strcmp(argv[i], "--gpu") == 0) {
            if (i + 1 < argc) {
                m_targetGpu = argv[++i];
            }
        } else if (std::strcmp(argv[i], "--verbose") == 0 || std::strcmp(argv[i], "-v") == 0) {
            m_verbose = true;
        }
    }

    if (m_mode == RunMode::Stress && m_scenario.empty()) {
        std::cerr << "Warning: --stress mode requires a scenario. Defaulting to Thermal Collapse." << std::endl;
        m_scenario = "Thermal Collapse";
    }
}

void Application::init() {
    if (m_verbose) std::cout << "Initializing Forge..." << std::endl;
    m_engine = new Engine();
    m_engine->setVerbose(m_verbose);
    m_engine->setTargetGpu(m_targetGpu);
    m_engine->init();
    
    if (m_mode == RunMode::Scenario || m_mode == RunMode::Stress) {
        m_engine->setPhase(m_scenario);
        m_engine->setBenchmarkAll(false);
    } else {
        m_engine->setBenchmarkAll(true);
    }
}

void Application::run() {
    if (m_verbose) std::cout << "Starting Forge engine loop..." << std::endl;
    m_engine->run();
}

void Application::cleanup() {
    if (m_verbose) std::cout << "Cleaning up Forge..." << std::endl;
    if (m_engine) {
        m_engine->cleanup();
    }
}

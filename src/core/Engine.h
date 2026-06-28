#pragma once

#include <string>
#include <vector>
#include <map>
#include <memory>

struct GLFWwindow;

class Engine {
public:
    Engine();
    ~Engine();

    void init();
    void run();
    void cleanup();
    
    void setPhase(const std::string& phase);
    void setTargetGpu(const std::string& gpu);
    void setVerbose(bool verbose);
    void setBenchmarkAll(bool benchmarkAll);

private:
    void initGLFW();
    void initOpenGL();
    void initImGui();
    void renderUI();
    
    void loadShaders();
    void setupFullscreenQuad();
    
    void advancePhase();
    void logVerbose(const std::string& msg);
    std::string getFallbackShaderSource(const std::string& phase);

    GLFWwindow* m_window;
    
    std::string m_currentPhase;
    std::string m_targetGpu;
    bool m_verbose;
    bool m_benchmarkAll;
    
    std::vector<std::string> m_phases;
    int m_currentPhaseIndex;
    float m_phaseTimer;
    
    std::map<std::string, unsigned int> m_shaderPrograms;
    unsigned int m_activeShaderProgram;
    
    unsigned int m_vao, m_vbo;
    
    float m_gpuTemp;
    float m_gpuUtil;
    float m_vramUtil;
    float m_totalScore;
    
    double m_time;
};

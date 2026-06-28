# Forge - GPU Benchmark & Stress Test

Forge is a deterministic cinematic engineering simulation benchmark engine designed to aggressively stress all GPU subsystems while visually constructing large-scale sci-fi industrial systems in real-time.

It features a robust modular architecture, adaptive GPU optimization scheduling, and extensive benchmark-grade telemetry.

## Technical Details

- **Language:** C++17
- **Build System:** CMake
- **Graphics API:** OpenGL (Fallback mode active), architecture stubbed for Vulkan support.
- **Dependencies (Auto-fetched via CMake):**
  - `GLFW 3.3.8` (Window and Context management)
  - `GLM 0.9.9.8` (Mathematics)
  - `Dear ImGui v1.89.9` (Telemetry Dashboard / UI)
  - `GLAD` (OpenGL extensions loader)
- **Shader Pipeline:** Procedural GLSL vertex/fragment simulation.

## Usage

Clone the repository:
```bash
git clone https://github.com/Igriscodes/forge.git
cd forge
```

Build the application from the source directory using CMake:
```bash
mkdir -p build && cd build
cmake ..
make -j$(nproc)
```

### Execution Commands

Forge provides a clean CLI interface to trigger different scenarios and diagnostic modes.

**1. Standard Benchmark (All Phases Sequentially)**
```bash
./forge --benchmark
```

**2. Verbose Standard Benchmark**
```bash
./forge --benchmark --verbose
# OR
./forge --benchmark -v
```

**3. Target a Specific GPU**
```bash
./forge --gpu 0 --benchmark
```

**4. Infinite Stress Test a Specific Scenario**
```bash
./forge --stress --scenario "Alloy Forge"
```

**5. Quick Single-Scenario Showcase**
```bash
./forge --scenario "Turbine Lattice Generation"
```

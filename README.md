# Physica - a computational physics library

This repository contains a computational physics library inspired by the concepts explored in the [WolframPhysicsProject](https://wolframphysics.org/).

## Overview

Physica aims to explore the dynamics and behavior of hypergraphs, drawing inspiration from the foundational ideas put forth by the Wolfram Physics project. Hypergraphs are generalizations of graphs where edges can connect more than two vertices, offering a powerful framework for modeling complex physical systems and interactions.

Physica provides a framework to evolve hypergraphs based on a set of rules inspired by computational irreducibility and emergent behavior observed in natural systems. These rules govern how hyperedges can form, dissolve, or modify their connections over successive simulation steps. By applying these rules iteratively, the engine generates dynamic configurations of hypergraphs, allowing exploration and analysis of emergent properties and structures.

![HypergraphVisualization](https://wolframphysics.org/visual-gallery/visualsummary/WolframPhysicsProject-visualsummary-large.png)

## Features

- **Hypergraph Representation:** Implements a data structure to represent and manipulate hypergraphs.
- **Configuration Options:** (planned) Configurable initial conditions and transformation rules.
- **Simulation Engine:** (planned) Provides mechanisms to simulate the evolution of hypergraphs over time according to the initial conditions and the configured rule of evolution.
- **Visualization Tools:** (planned) Includes tools for visualizing the generated hypergraphs and their dynamics.

## Getting Started

To begin working with this project, follow these instructions to set up your development environment on Windows:

### Prerequisites

1. **CMake**: Install CMake from the [official CMake website](https://cmake.org/download/).

2. **Visual Studio 2017 or later**: Install Visual Studio from the [official Visual Studio website](https://visualstudio.microsoft.com/downloads/), ensuring you include the C++ development tools.

3. **vcpkg**: This package manager will handle project dependencies. Follow these steps to install vcpkg:

   - **Clone vcpkg Repository**

     Open Command Prompt and clone the vcpkg repository:

     ```sh
     git clone https://github.com/microsoft/vcpkg.git
     ```

   - **Bootstrap vcpkg**

     Navigate to the vcpkg directory and run the bootstrap script:

     ```sh
     cd vcpkg
     .\bootstrap-vcpkg.bat
     ```

   - **Set Environment Variables**

     Configure your environment variables to include vcpkg. Run the following commands in Command Prompt:

     ```sh
     set "VCPKG_ROOT=C:\path\to\vcpkg"
     set PATH=%VCPKG_ROOT%;%PATH%
     ```

     Replace `C:\path\to\vcpkg` with the actual path where you cloned vcpkg.

### Building the Project

1. **Debug**

   Navigate to your project root:

   ```sh
   cd scripts/
   build-debug.bat
   ```

2. **Debug (no unit tests)**

   Navigate to your project root:

   ```sh
   cd scripts/
   build-debug-no-tests.bat
   ```
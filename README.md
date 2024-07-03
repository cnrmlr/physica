# Computational Physics Engine

This repository contains a computational physics engine inspired by the concepts explored in the [WolframPhysicsProject](https://wolframphysics.org/).

## Overview

The computational physics engine aims to explore the dynamics and behavior of hypergraphs, drawing inspiration from the foundational ideas put forth by the Wolfram Physics project. Hypergraphs are generalizations of graphs where edges can connect more than two vertices, offering a powerful framework for modeling complex systems and interactions.

In this engine, hypergraphs evolve based on a set of rules inspired by computational irreducibility and emergent behavior observed in natural systems. These rules govern how hyperedges can form, dissolve, or modify their connections over successive simulation steps. By applying these rules iteratively, the engine generates dynamic configurations of hypergraphs, allowing exploration of emergent properties and structures.

![HypergraphVisualization](https://wolframphysics.org/visual-gallery/visualsummary/WolframPhysicsProject-visualsummary-large.png)

## Features

- **Hypergraph Representation:** Implements a data structure to represent and manipulate hypergraphs.
- **Configuration Options:** (planned) Configurable initial conditions and transformation rules.
- **Simulation Engine:** (planned) Provides mechanisms to simulate the evolution of hypergraphs over time according to the initial conditions and the configured rule of evolution.
- **Visualization Tools:** (planned) Includes tools for visualizing the generated hypergraphs and their dynamics.

## Getting Started

### Prerequisites

- **Rust**: Installed on your system to build the engine.
  - **Windows**:
    - Download and run the installer from [rust-lang.org](https://www.rust-lang.org/).
    - Follow the prompts in the installer.
    - Optionally, ensure Rust is added to your PATH environment variable during installation.
    - Verify installation by opening Command Prompt (`cmd`) and typing:
      ```sh
      rustc --version
      ```
  - **Unix-based Systems** (Linux, macOS):
    - Open a terminal and run the following command:
      ```sh
      curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
      ```
    - Follow the prompts to customize the installation as needed, such as adding Rust to your PATH.
    - Verify installation by reopening your terminal and typing:
      ```sh
      rustc --version
      ```

- **Python**: Required for build and visualization scripts.
  - **Windows**:
    - Download the installer from [python.org](https://www.python.org/).
    - Run the installer and follow the prompts.
    - Optionally, add Python to your PATH environment variable during installation.
    - Verify installation by opening a new command prompt and typing:
      ```sh
      python --version
      ```
  - **Unix-based Systems** (Linux, macOS):
    - Python usually comes pre-installed on most Unix-based systems. However, to install Python using a package manager:
      - On Debian/Ubuntu:
        ```sh
        sudo apt-get update
        sudo apt-get install python3
        ```
      - On macOS (using Homebrew):
        ```sh
        brew install python
        ```
    - Verify installation by opening a new terminal and typing:
      ```sh
      python --version
      ```


### Setup/Run

- **Clone the repository**:
   ```bash
   git clone https://github.com/cnrmlr/computational_physics_engine.git

- **Configure and run**:
   - From the scripts directory, run the following commands to generate the engine's configuration file and run the engine:
      - **Windows**: 
      ```sh
      python configure.py
      python build_and_run.py --build_type release
      ```
      - **Unix-based Systems** (Linux, macOS):
      ```sh
      python3 configure.py
      python3 build_and_run.py --build_type release
      ```
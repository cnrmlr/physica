# Hypergraph Simulator

This repository contains a hypergraph simulator inspired by the concepts explored in the [WolframPhysicsProject](https://wolframphysics.org/)

## Overview

The hypergraph simulator aims to explore the dynamics and behavior of hypergraphs, drawing inspiration from the foundational ideas put forth by the Wolfram Physics project. Hypergraphs are generalizations of graphs where edges can connect more than two nodes, offering a powerful framework for modeling complex systems and interactions.

In this simulator, hypergraphs evolve based on a set of rules inspired by computational irreducibility and emergent behavior observed in natural systems. These rules govern how hyperedges can form, dissolve, or modify their connections over successive simulation steps. By applying these rules iteratively, the simulator generates dynamic configurations of hypergraphs, allowing exploration of emergent properties and structures.

![HypergraphVisualization](https://wolframphysics.org/visual-gallery/visualsummary/WolframPhysicsProject-visualsummary-large.png)

## Features

- **Hypergraph Representation:** Implements a data structure to represent and manipulate hypergraphs.
- **Configuration Options:** (coming soon) Configurable initial conditions and transformation rules to demonstrate the simulator's capabilities to transform hypergraphs over time.
- **Simulation Engine:** (coming soon) Provides mechanisms to simulate the evolution of hypergraphs over time according to a configured rule of evolution.
- **Visualization Tools:** (coming soon) Includes tools for visualizing the generated hypergraphs and their dynamics.

## Getting Started

### Prerequisites

- [Rust](https://www.rust-lang.org/) installed on your system to build the simulator.
- [Python](https://www.python.org/) for build and visualization scripts.

### Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/cnrmlr/hypergraph_simulator.git

2. From the root of the repository, run the following command:
    ```bash
    python build_and_run.py --build_type <build_type>
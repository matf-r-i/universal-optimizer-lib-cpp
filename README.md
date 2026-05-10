# Universal Optimizer Library (C++)

C++ implementation of the Universal Optimizer Library, ported from the Python version.

## Project Structure

```
├── include/          # Public headers (*.hpp)
│   ├── algorithm/    # Algorithm classes
│   │   ├── exact/    # Exact algorithms (e.g., Total Enumeration)
│   │   └── metaheuristic/  # Metaheuristic algorithms
│   ├── problem/      # Problem definitions
│   ├── solution/     # Solution representations
│   └── utils/        # Utility classes
├── src/              # Implementation files (*.cpp)
│   └── ...           # Mirrors include/ structure
├── tests/            # Unit tests
├── scripts/          # Build and utility scripts
├── docs/             # Documentation
├── Makefile          # Build configuration
└── README.md         # This file
```

## Building

### Prerequisites
- C++20 compatible compiler (g++ >= 11, clang >= 14, MSVC 2022)
- GNU Make

### Build Library
```bash
make
```

### Build and Run Tests
```bash
make test
```

### Clean Build Artifacts
```bash
make clean
make distclean    # Also removes documentation
```

## Class Hierarchy

```
Optimizer
└── Algorithm
    ├── Metaheuristic
    │   ├── SingleSolutionMetaheuristic
    │   │   ├── SaOptimizer (Simulated Annealing)
    │   │   └── VnsOptimizer (Variable Neighborhood Search)
    │   └── PopulationBasedMetaheuristic
    │       ├── GaOptimizer (Genetic Algorithm)
    │       ├── EmOptimizer (Electro-Magnetism-like)
    │       ├── MoeadOptimizer (MOEA/D)
    │       └── MonteCarloOptimizer
    └── TeOptimizer (Total Enumeration)
```

## License

Apache License 2.0

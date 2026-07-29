# Hydra

Hydra is the development repository for the **Bella knowledge compiler** and the **Cara #SAT solver**.

## Bella

A knowledge compiler for:

- (s)d-DNNF circuits,
- wDNNF, pwDNNF, and nwDNNF circuits.

> [!IMPORTANT]
> This repository contains the source code. For precompiled binaries (statically linked on Linux) and the full description, please visit the [BellaCompiler repository](https://github.com/Illner/BellaCompiler).

## Cara

An isomorphism-aware #SAT solver.

> [!IMPORTANT]
> This repository contains the source code. For precompiled binaries (statically linked on Linux) and the full description, please visit the [CaraSolver repository](https://github.com/Illner/CaraSolver).

## Build Instructions

**Supported OS**: Linux, macOS (Apple Silicon), and Windows

Building requires:
[CMake ≥ 3.14](https://cmake.org/),
[Boost](https://www.boost.org/), and
[GMP](https://gmplib.org/).

> [!NOTE]
> On Windows, [Cygwin](https://cygwin.com/) is needed.

Both Bella and Cara are built using their respective scripts (`bella.sh` or `cara.sh`) located in the `scripts/` directory. 
Compilation takes place in either the `build_bella` or `build_cara` directory, depending on the tool you are building.

Replace `<tool>` with either `bella` or `cara` (and `<Tool>` with either `Bella` or `Cara`) in the commands below.

### Release

```console
./scripts/<tool>.sh --release
```

The release binary is located in `build_<tool>/Release/<Tool>/`.

### Debug

```console
./scripts/<tool>.sh --debug
```

The debug binary is located in `build_<tool>/Debug/<Tool>/`.

### Test

```console
./scripts/<tool>.sh --test
```

The test binaries are located in `build_<tool>/Test/HydraTest/` and `build_<tool>/Test/<Tool>Test/`.

### All (Release, Debug, and Test)

```console
./scripts/<tool>.sh
./scripts/<tool>.sh --all
./scripts/<tool>.sh --release --debug --test
```

The corresponding binaries are in the locations mentioned above.

## Third-Party Software

### SAT Solvers

* [MiniSat 2.2.0 (d4v2 version)](https://github.com/crillab/d4v2)  
  `Hydra/external/satSolvers/MiniSat_d4`

* [Glucose 3.0 (d4v2 version)](https://github.com/crillab/d4v2)  
  `Hydra/external/satSolvers/Glucose_d4`

* [MiniSat 2.2.0](https://github.com/niklasso/minisat)  
  _implemented, not used_  
  `Hydra/external/satSolvers/MiniSat`

* [CaDiCaL 3.0.0](https://github.com/arminbiere/cadical)  
  _work in progress_  
  `Hydra/external/satSolvers/CaDiCaL`

### Hash Maps

* [unordered_dense v4.5.0](https://github.com/martinus/unordered_dense)  
  `Hydra/external/hashMaps/unordered_dense`

* [robin-hood-hashing 3.11.5](https://github.com/martinus/robin-hood-hashing)  
  `Hydra/external/hashMaps/robin-hood-hashing`

* [flat_hash_map](https://github.com/skarupke/flat_hash_map)  
  _implemented, not used_  
  `Hydra/external/hashMaps/flat_hash_map`

### Hypergraph Partitioning

* [PaToH v3.3](https://faculty.cc.gatech.edu/~umit/software.html)  
  _used on Linux and macOS_  
  `Hydra/external/partitioningHypergraphs/PaToH`

* [hMETIS 1.5.3](https://papers.karypis.org/glaros/software/metis/overview.html)  
  _used only on Windows_  
  `Hydra/external/partitioningHypergraphs/hMETIS`

* [KaHyPar v.1.3.3](https://kahypar.org/)  
  _used on Linux, macOS, and Windows_  
  `Hydra/external/partitioningHypergraphs/KaHyPar`  
  `Hydra/external/boost` (_precompiled libraries required by KaHyPar_)

## Papers

If you use **Bella for (s)d-DNNF/wDNNF circuits** in an academic setting, please cite the following paper describing the knowledge compiler:

```bibtex
@article{Illner_Kucera_2024, 
    author  = {Illner, Petr and Ku\v{c}era, Petr}, 
    title   = {A Compiler for Weak Decomposable Negation Normal Form}, 
    volume  = {38}, 
    url     = {https://ojs.aaai.org/index.php/AAAI/article/view/28926}, 
    DOI     = {10.1609/aaai.v38i9.28926}, 
    number  = {9}, 
    journal = {Proceedings of the AAAI Conference on Artificial Intelligence},
    year    = {2024}, 
    month   = {Mar.}, 
    pages   = {10562-10570} 
}
```

If you use **Bella for pwDNNF/nwDNNF circuits** or **Cara** in an academic setting, please cite the following paper describing the knowledge compiler and caching scheme:

```bibtex
@article{Illner_2025, 
    author  = {Illner, Petr}, 
    title   = {New Compilation Languages Based on Restricted Weak Decomposability}, 
    volume  = {39}, 
    url     = {https://ojs.aaai.org/index.php/AAAI/article/view/33643}, 
    DOI     = {10.1609/aaai.v39i14.33643}, 
    number  = {14}, 
    journal = {Proceedings of the AAAI Conference on Artificial Intelligence}, 
    year    = {2025}, 
    month   = {Apr.}, 
    pages   = {14987-14996} 
}
```

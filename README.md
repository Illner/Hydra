# Hydra

Hydra is the development repository for the **Bella knowledge compiler** and the **Cara #SAT solver**.

**Supported OS**: Linux, macOS (Intel & Apple Silicon), Windows

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

The following tools are required:
[CMake](https://cmake.org/),
[Boost](https://www.boost.org/), and
[GMP](https://gmplib.org/).

> [!NOTE]
> On Windows, [Cygwin](https://cygwin.com/) is needed.

### Building Bella

```console
./bella.sh
```

The compilation takes place in the **`build_bella`** directory. The release binary can be found at: **`build_bella/Release/Bella/`**

### Building Cara

```console
./cara.sh
```

The compilation takes place in the **`build_cara`** directory. The release binary can be found at: **`build_cara/Release/Cara/`**

## Used software

### SAT solver

* [MiniSat 2.2.0 (d4v2 version)](https://github.com/crillab/d4v2)  
  Hydra/external/satSolvers/MiniSat_d4

* [Glucose 3.0 (d4v2 version)](https://github.com/crillab/d4v2)  
  Hydra/external/satSolvers/Glucose_d4

* [MiniSat 2.2.0](https://github.com/niklasso/minisat)  
  _implemented, not used_  
  Hydra/external/satSolvers/MiniSat

* [CaDiCaL 3.0.0](https://github.com/arminbiere/cadical) (TBD)  
  Hydra/external/satSolvers/CaDiCaL

### Hash map

* [unordered_dense v4.5.0](https://github.com/martinus/unordered_dense)  
  Hydra/external/hashMaps/unordered_dense

* [robin-hood-hashing 3.11.5](https://github.com/martinus/robin-hood-hashing)  
  Hydra/external/hashMaps/robin-hood-hashing

* [flat_hash_map](https://github.com/skarupke/flat_hash_map)  
  _implemented, not used_  
  Hydra/external/hashMaps/flat_hash_map

### Hypergraph partitioning

* [PaToH v3.3](https://faculty.cc.gatech.edu/~umit/software.html)  
  _used for Linux, and macOS_  
  Hydra/external/partitioningHypergraphs/PaToH

* [hMETIS 1.5.3](https://papers.karypis.org/glaros/software/metis/overview.html)  
  _used only for Windows_  
  Hydra/external/partitioningHypergraphs/hMETIS

* [KaHyPar v.1.3.3](https://kahypar.org/)  
  Hydra/external/partitioningHypergraphs/KaHyPar

### Other

* [Boost](https://www.boost.org/)  
  Hydra/external/boost

## Papers

If you use **Bella for (s)d-DNNF/wDNNF circuits** in an academic setting, please cite the following paper describing the knowledge compiler:

    @article{Illner_Kucera_2024, 
        author  = {Illner, Petr and Kučera, Petr}, 
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

If you use **Bella for pwDNNF/nwDNNF circuits** or **Cara** in an academic setting, please cite the following paper describing the knowledge compiler and caching scheme:

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

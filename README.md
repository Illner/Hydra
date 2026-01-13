# Hydra

Hydra is the development repository for the **Bella knowledge compiler** and the **Cara #SAT solver**.

**Supported OS**: Linux, macOS (Intel & Apple Silicon), Windows

## Bella

A knowledge compiler for:

- (s)d-DNNF circuits,
- wDNNF, pwDNNF, and nwDNNF circuits.

> [!IMPORTANT]
> This repository contains the source code. For compiled binaries and the full description, please visit the <a href="https://github.com/Illner/BellaCompiler" target="_blank">BellaCompiler repository</a>.

## Cara

An isomorphism-aware #SAT solver.

> [!IMPORTANT]
> This repository contains the source code. For compiled binaries and the full description, please visit the <a href="https://github.com/Illner/CaraSolver" target="_blank">CaraSolver repository</a>.

## Build Instructions

The following tools are required:
<a href="https://cmake.org/" target="_blank">CMake</a>,
<a href="https://www.boost.org/" target="_blank">Boost</a>, and
<a href="https://gmplib.org/" target="_blank">GMP</a>.

> [!NOTE]
> On Windows, <a href="https://cygwin.com/" target="_blank">Cygwin</a> is needed.

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

* <a href="https://github.com/crillab/d4v2" target="_blank"> MiniSat 2.2.0 (d4 version) </a> <br> Hydra/external/satSolvers/MiniSat_d4
* <a href="https://github.com/niklasso/minisat" target="_blank"> MiniSat 2.2.0 </a> <br> <i> implemented, not used </i> <br> Hydra/external/satSolvers/MiniSat
* <a href="https://github.com/arminbiere/cadical" target="_blank"> CaDiCaL 3.0.0 </a> (TBD) <br> Hydra/external/satSolvers/CaDiCaL

### Hash map

* <a href="https://github.com/martinus/unordered_dense" target="_blank"> unordered_dense v4.5.0 </a> <br> Hydra/external/hashMaps/unordered_dense
* <a href="https://github.com/martinus/robin-hood-hashing" target="_blank"> robin-hood-hashing 3.11.5 </a> <br> Hydra/external/hashMaps/robin-hood-hashing
* <a href="https://github.com/skarupke/flat_hash_map" target="_blank"> flat_hash_map </a> <br> <i> implemented, not used </i> <br> Hydra/external/hashMaps/flat_hash_map

### Hypergraph partitioning

* <a href="https://faculty.cc.gatech.edu/~umit/software.html" target="_blank"> PaToH v3.3 </a> <br> <i> used for Linux, and macOS </i> <br> Hydra/external/partitioningHypergraphs/PaToH
* <a href="http://glaros.dtc.umn.edu/gkhome/metis/hmetis/overview" target="_blank"> hMETIS 1.5 </a> <br> <i> used only for Windows </i> <br> Hydra/external/partitioningHypergraphs/hMETIS
* <a href="https://kahypar.org/" target="_blank"> KaHyPar v.1.3.3 </a> <br> Hydra/external/partitioningHypergraphs/KaHyPar

### Other

* <a href="https://www.boost.org/" target="_blank"> Boost </a> <br> Hydra/external/boost

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

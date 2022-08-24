### Algorithms

Based on the RELIC toolkit we implement:
 hashing to $\mathbb{G}_2$ on the BW13-P310 curve with two methods presented in https://eprint.iacr.org/2022/996. The first method is seen as a generlized  Fuentes et al method and the second one is a further optimiation based on the first one.
The preset file is in the preset folder in the name of gmp-ecc-bw310.sh.<br/>

### Requirements

The build process requires the [CMake](https://cmake.org/) cross-platform build system. The [GMP](https://gmplib.org/) library is also needed in our benchmarks.

### Build instructions

Instructions for building the library can be found in the [Wiki](https://github.com/relic-toolkit/relic/wiki/Building).


### Source code
  
The main source code of our algorithms are distributed in different folders.  The main functions are:

* ep13_map(ep13_t p, const uint8_t *msg, int len) :Maps a byte array to a point of BW13-P310.
* ep13_cof_fuentes(q, p):Given a random point q , hashing q to G2 with method II.
* ep13_cof_fuentes(ep13_t r, ep13_t p) : Given a random point q of E, hashing q to G2 using generlized fuentes et's method.


 Note the the previous fastest memberhship testings algotithms on the BN-P446 curve are presented in functions g2_is_valid(const g2_t a) and gt_is_valid(const gt_t a), respectively.

 ### Benckmarks
 The function for benckmarking are presented in [bench_pc.c](https://github.com/eccdaiy39/smt/blob/master/smt-relic/bench/bench_pc.c) for the BN-P446 curve and 
 [bench_pc_bw13.c](https://github.com/eccdaiy39/smt/blob/master/smt-relic/bench/bench_pc_bw13.c) for the BW13-P310 curve.
 Here we give a direct way to obtain concrete datas.
  



  1. mkdir build && cd build 
  2. ../preset/gmp-ecc-bw310.sh ../
  3. make
  4. cd bin && ./bench_hash
  

 



### Algorithms

Based on the RELIC toolkit we implement:

we implemented hashing to $\mathbb{G}_2$ on the BW13-P310 curve with two methods presented in <URL https://eprint.iacr.org/2022/996>. The first one is seen as a generlized  Fuentes et al method and
the second one is 
The preset file is in the preset folder in the name of gmp-ecc-bw310.sh.<br/>

### Requirements

The build process requires the [CMake](https://cmake.org/) cross-platform build system. The [GMP](https://gmplib.org/) library is also needed in our benchmarks.

### Build instructions

Instructions for building the library can be found in the [Wiki](https://github.com/relic-toolkit/relic/wiki/Building).


### Source code
  
The main source code of our algorithms are distributed in different folders.  The main functions are:
* 
*

 Note the the previous fastest memberhship testings algotithms on the BN-P446 curve are presented in functions g2_is_valid(const g2_t a) and gt_is_valid(const gt_t a), respectively.

 ### Benckmarks
 The function for benckmarking are presented in [bench_pc.c](https://github.com/eccdaiy39/smt/blob/master/smt-relic/bench/bench_pc.c) for the BN-P446 curve and 
 [bench_pc_bw13.c](https://github.com/eccdaiy39/smt/blob/master/smt-relic/bench/bench_pc_bw13.c) for the BW13-P310 curve.
 Here we give a direct way to obtain concrete datas.
  

![image](https://github.com/eccdaiy39/smt/blob/master/image/G2-BN.png)
![image](https://github.com/eccdaiy39/smt/blob/master/image/GT-BN.png)


  1. mkdir build && cd build 
  2. ../preset/gmp-ecc-bw310.sh ../
  3. make
  4. cd bin && ./bench_pc_bw13
  
![image](https://github.com/eccdaiy39/smt/blob/master/image/BW13.png)


 



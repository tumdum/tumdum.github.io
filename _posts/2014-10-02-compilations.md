---
layout: post
date: 2014-10-02
title: "Cost of includes"
---

For each src/*.cc file there is detailed log in logs/*.cc.txt with:
    - strace summary of syscalls times and number of executions
    - wall clock time it took to compile
    - number of header locations which whare tried
    - number of opened (not unique) headers
    - number of headers according to gcc -M

Compilation was done with -Os using "g++ (Ubuntu 4.8.2-19ubuntu1) 4.8.2"

```bash
    Summary:

    src/all.cc
    % time     seconds  usecs/call     calls    errors syscall
    ------ ----------- ----------- --------- --------- ----------------
     69.13    0.280109           7     39941      6178 lstat
     17.69    0.071678           9      7798      6200 open
      4.00    0.016206          10      1650           read
      2.81    0.011378           7      1598           close
    real 4.93
    tried to open 7700 headers
           opened 1555 headers
       depends on 968 headers

    src/bind.cc
    % time     seconds  usecs/call     calls    errors syscall
    ------ ----------- ----------- --------- --------- ----------------
     61.35    0.024457           7      3545       517 lstat
     16.09    0.006413           9       696       539 open
      4.96    0.001977          13       156           read
      2.91    0.001160           7       157           close
    real 0.31
    tried to open 617 headers
           opened 118 headers
       depends on 108 headers

    src/empty.cc
    % time     seconds  usecs/call     calls    errors syscall
    ------ ----------- ----------- --------- --------- ----------------
     14.51    0.000942          10        90           mmap
     12.88    0.000836          13        66        29 open
     12.14    0.000788          22        36           read
     10.09    0.000655          11        60        29 stat
    real 0.05
    tried to open 8 headers
           opened 1 headers
       depends on 1 headers

    src/map.cc
    % time     seconds  usecs/call     calls    errors syscall
    ------ ----------- ----------- --------- --------- ----------------
     32.02    0.004875          11       460        42 lstat
     13.78    0.002098          15       136        64 open
     10.20    0.001553          22        71           read
      8.43    0.001283          13        96           mmap
    real 0.13
    tried to open 78 headers
           opened 36 headers
       depends on 36 headers

    src/mpl_apply_and_vector.cc
    % time     seconds  usecs/call     calls    errors syscall
    ------ ----------- ----------- --------- --------- ----------------
     70.61    0.079509           7     11277      1736 lstat
     17.13    0.019287           9      2093      1758 open
      2.93    0.003298          10       334           read
      2.04    0.002296           7       335           close
    real 0.69
    tried to open 2014 headers
           opened 296 headers
       depends on 256 headers

    src/optional.cc
    % time     seconds  usecs/call     calls    errors syscall
    ------ ----------- ----------- --------- --------- ----------------
     64.42    0.071699           7     10565      1576 lstat
     16.86    0.018767           9      2060      1598 open
      4.76    0.005293           5       997           mmap
      4.72    0.005257          11       462           read
    real 1.06
    tried to open 1974 headers
           opened 422 headers
       depends on 299 headers

    src/shared_ptr.cc
    % time     seconds  usecs/call     calls    errors syscall
    ------ ----------- ----------- --------- --------- ----------------
     59.20    0.029393           7      4198       576 lstat
     16.67    0.008275          10       833       598 open
      6.72    0.003337          14       235           read
      3.62    0.001797           8       235           close
    real 0.48
    tried to open 747 headers
           opened 195 headers
       depends on 162 headers

    src/sstream.cc
    % time     seconds  usecs/call     calls    errors syscall
    ------ ----------- ----------- --------- --------- ----------------
     47.04    0.011771           7      1710       202 lstat
     15.54    0.003888          11       368       224 open
      9.16    0.002293          16       143           read
      5.39    0.001349          13       103           mmap
    real 0.29
    tried to open 303 headers
           opened 107 headers
       depends on 94 headers

    src/string.cc
    % time     seconds  usecs/call     calls    errors syscall
    ------ ----------- ----------- --------- --------- ----------------
     44.86    0.009815           6      1540       193 lstat
     15.52    0.003396          10       336       215 open
      9.18    0.002008          17       120           read
      5.79    0.001266          13       100           mmap
    real 0.20
    tried to open 271 headers
           opened 84 headers
       depends on 73 headers

    src/thread.cc
    % time     seconds  usecs/call     calls    errors syscall
    ------ ----------- ----------- --------- --------- ----------------
     67.58    0.208776           7     30597      4689 lstat
     17.40    0.053756           9      6037      4711 open
      4.39    0.013553          10      1378           read
      2.93    0.009059           7      1326           close
    real 4.23
    tried to open 5939 headers
           opened 1283 headers
       depends on 782 headers

    src/variant.cc
    % time     seconds  usecs/call     calls    errors syscall
    ------ ----------- ----------- --------- --------- ----------------
     69.27    0.148890           7     21371      3300 lstat
     17.52    0.037660           9      4111      3322 open
      3.49    0.007495           9       789           read
      2.93    0.006300           6      1007           mmap
    real 1.80
    tried to open 4025 headers
           opened 749 headers
       depends on 514 headers

    src/vector.cc
    % time     seconds  usecs/call     calls    errors syscall
    ------ ----------- ----------- --------- --------- ----------------
     24.69    0.003097           7       466        42 lstat
     14.58    0.001829          13       137        64 open
     11.10    0.001392          19        72           read
      9.65    0.001210          12        97           mmap
    real 0.13
    tried to open 79 headers
           opened 37 headers
       depends on 37 headers
```

[Details]({{ site.baseurl }}/files/compilations.tar.xz)

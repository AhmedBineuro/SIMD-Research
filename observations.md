# Eigen

- How it achieves its speed?
  - Uses better data compacting for better data alignment.
  - Uses largest scale SIMD the processor is capable of.
  - Uses a better multiplication algorithm to divide the problem into cache sized chunks for even faster computation
  - Lazy evaluation: rather than compute something immediately, wait until it is needed and then compute it.

# Vector class

- How it achieves its speed?
  - Uses SIMD instructions to shrink the amount of expensive multiplication by a factor of 16.
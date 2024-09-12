# Instructions

- Instruction to build
  - `make build`
- Instruction to run all the tests
  - `make custom_tests arg1=row1xcol1 arg2=row2xcol2`
  - Change the values to the two matrix sizes for the test
  - The dimensions should be divisible by 16
- Instruction to run a specific test
  - `make run -m1 row1xcol1 -m2 row2xcol2 -tm testModeName`
  - `-tm` is an optional argument and it is for the test mode
  - There are 3 test modes:
    - `def` : Element wise test mode _(default)_
    - `vc` : Vector class test mode
- Instruction to make quick tests
  - `make quick_tests`

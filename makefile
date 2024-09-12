.PHONY: customs_tests
.PHONY: quick_tests

build:
	g++ -Wpedantic -Wall -std=c++17 -march=haswell *.cpp -I ./vectorclass -I ./Eigen -O3 -o tests
build_debug:
	g++ -g -Wpedantic -Wall -std=c++17 -march=haswell *.cpp -I ./vectorclass -I ./Eigen -O3 -o tests
run:
	@./tests $(ARGS)
custom_tests:
	@echo "Running Matrix Multiplication tests"
	@echo "Matrix 1 size: $(arg1)"
	@echo "Matrix 2 size: $(arg2)"
	@./tests -m1 $(arg1) -m2 $(arg2)
	@./tests -m1 $(arg1) -m2 $(arg2) -tm vc
	@./tests -m1 $(arg1) -m2 $(arg2) -tm ed
quick_tests:
	@echo "Running Matrix Multiplication tests"
	@echo "Matrix 1 size: 2048x2048"
	@echo "Matrix 2 size: 2048x2048"
	@./tests -m1 2048x2048 -m2 2048x2048
	@./tests -m1 2048x2048 -m2 2048x2048 -tm vc
	@./tests -m1 2048x2048 -m2 2048x2048 -tm ed

# Array of arguments (pairs of matrix dimensions)
ARGS = "-m1 1024x512 -m2 512x1536" "-m1 2048x1024 -m2 1024x3072" "-m1 4096x2048 -m2 2048x2048"

perf_stat_tests:
	@for arg in $(ARGS); do \
	    m1="-m1 "`echo $$arg | cut -d' ' -f2`; \
	    m2="-m2 "`echo $$arg | cut -d' ' -f4`; \
	    echo "Running Matrix Multiplication tests" >> def.txt; \
	    echo "Matrix 1 size: $$m1" >> def.txt; \
	    echo "Matrix 2 size: $$m2" >> def.txt; \
	    perf stat -e L1-dcache-load-misses,L1-dcache-loads,LLC-load-misses,LLC-loads ./tests  $$m1 $$m2 2>> def.txt; \
	    echo "Running Matrix Multiplication tests" >> vc.txt; \
	    echo "Matrix 1 size: $$m1" >> vc.txt; \
	    echo "Matrix 2 size: $$m2" >> vc.txt; \
	    perf stat -e L1-dcache-load-misses,L1-dcache-loads,LLC-load-misses,LLC-loads ./tests  $$m1 $$m2 -tm vc 2>> vc.txt; \
	    echo "Running Matrix Multiplication tests" >> ed.txt; \
	    echo "Matrix 1 size: $$m1" >> ed.txt; \
	    echo "Matrix 2 size: $$m2" >> ed.txt; \
	    perf stat -e L1-dcache-load-misses,L1-dcache-loads,LLC-load-misses,LLC-loads ./tests  $$m1 $$m2 -tm ed 2>> ed.txt; \
	done

perf_record_tests:
	@echo "Running Matrix Multiplication tests"
	@echo "Matrix 1 size: 4096x4096"
	@echo "Matrix 2 size: 4096x4096"
	@perf record -o perf.data -e L1-dcache-load-misses,L1-dcache-loads,LLC-load-misses,LLC-loads ./tests  -m1 2048x2048 -m2 2048x2048
	@perf annotate -i perf.data > ./annotated/def_report.txt
	@perf record -o perf.data -e L1-dcache-load-misses,L1-dcache-loads,LLC-load-misses,LLC-loads ./tests  -m1 2048x2048 -m2 2048x2048 -tm vc
	@perf annotate -i perf.data > ./annotated/vc_report.txt
	@perf record -o perf.data -e L1-dcache-load-misses,L1-dcache-loads,LLC-load-misses,LLC-loads ./tests  -m1 2048x2048 -m2 2048x2048 -tm ed
	@perf annotate -i perf.data > ./annotated/ed_report.txt
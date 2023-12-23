CXX = g++
CXXFLAGS = -std=c++11 -O3 -Wall

all: test

gen: gen_tuganet.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

p1: p2.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

test: gen p2
	for size in $$(seq 50000 50000 1000000); do \
		echo "Generating input file p2.in with size $$size"; \
		./gen $$size $$size 10000 1 1001 > p2.in; \
		echo "Running p2 10 times for size $$size"; \
		for i in $$(seq 1 10); do \
			echo -n "Test $$i: "; \
			start=$$(date +%s%N); \
			./p2 < p2.in; \
			end=$$(date +%s%N); \
			echo "$$(( (end - start) / 1000000 )) ms"; \
		done | awk '{sum+=$$1} END {print sum/10}'; \
	done

clean:
	rm -f gen p2 p2.in

CXX = g++
CXXFLAGS = -std=c++11 -O3 -Wall

all: test

gen: gen_supermarble.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

p1: p1.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

test: gen p1
	for size in $$(seq 100 100 1600); do \
		echo "Generating input file p1.in with size $$size"; \
		./gen $$size $$size 50 > p1.in; \
		echo "Running p1 10 times for size $$size"; \
		for i in $$(seq 1 10); do \
			echo -n "Test $$i: "; \
			start=$$(date +%s%N); \
			./p1 < p1.in; \
			end=$$(date +%s%N); \
			echo "$$(( (end - start) / 1000000 )) ms"; \
		done | awk '{sum+=$$1} END {print sum/10}'; \
	done

clean:
	rm -f gen p1 p1.in

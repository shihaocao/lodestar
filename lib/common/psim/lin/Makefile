CLANGXX       ?= clang++
CLANGCXXFLAGS += -Iinclude -I/opt/local/include -std=c++14 -Werror -Wall -Wextra
LLD           ?= clang++
LLDFLAGS      += -L/opt/local/lib -lgtest

TEST_FILES := $(wildcard test/*.cpp)
TEST_BINS  := $(patsubst test/%.cpp,bin/test/%.o,$(TEST_FILES))

EG_FILES := $(wildcard examples/*.cpp)
EG_BINS  := $(patsubst examples/%.cpp,bin/examples/%.out,$(EG_FILES))

test.out : $(TEST_BINS)
	$(LLD) $(LLDFLAGS) -o bin/$@ $^

examples : $(EG_BINS)
	echo "Examples built and are in bin/examples/*.out"

bin/examples/%.out : examples/%.cpp
	mkdir -p bin/examples
	$(CLANGXX) $(CLANGCXXFLAGS) -o $@ $<

bin/test/%.o : test/%.cpp
	mkdir -p bin/test
	$(CLANGXX) $(CLANGCXXFLAGS) -c -o $@ $<

test : test.out
	./bin/test.out

clean:
	rm bin/test/* || echo "bin/test/* already clean"
	rm bin/examples/* || echo "bin/examples/* already clean"

.PHONY : clean test

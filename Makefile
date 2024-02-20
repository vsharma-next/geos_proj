CXX = g++
CXXFLAGS = -std=c++11 -Wall $(shell geos-config --cflags) $(shell pkg-config --cflags proj)
LDFLAGS = $(shell geos-config --libs) $(shell pkg-config --libs proj)

SRC_DIR = examples
BUILD_DIR = build

SOURCES = $(wildcard $(SRC_DIR)/example_*.cpp)
TARGETS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.exe,$(SOURCES))

all: $(BUILD_DIR) $(TARGETS)

$(BUILD_DIR)/%.exe: $(SRC_DIR)/%.cpp
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS)

$(BUILD_DIR):
	mkdir -p $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean

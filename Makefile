CXX = g++
CXXFLAGS = -std=c++11 -Wall $(shell geos-config --cflags) $(shell pkg-config --cflags proj)
LDFLAGS = $(shell geos-config --libs) $(shell pkg-config --libs proj)

SRC_DIR = examples
BUILD_DIR = build

TARGET = $(BUILD_DIR)/test_1

SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $^ -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean

CXX = g++
LIBS_DIR = libs/build
CXXFLAGS = -std=c++17 -Wall $(shell $(LIBS_DIR)/bin/geos-config --cflags) $(shell $(LIBS_DIR)/bin/gdal-config --cflags) 
LDFLAGS = -static $(shell $(LIBS_DIR)/bin/geos-config --static-cclibs) $(shell $(LIBS_DIR)/bin/gdal-config --libs) -lsqlite3 -ldl

SRC_DIR = examples
BUILD_DIR = build

SOURCES = $(wildcard $(SRC_DIR)/example_*.cpp)
TARGETS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.exe,$(SOURCES))

all: $(TARGETS)

$(BUILD_DIR)/%.exe: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS)

$(BUILD_DIR):
	mkdir -p $@

clean:
	rm -rf $(BUILD_DIR)/*.exe

.PHONY: all clean

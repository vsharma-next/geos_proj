CXX = g++
LIBS_DIR = libs/build
PKG_CONFIG_PATH := $(LIBS_DIR)/lib/pkgconfig
CXXFLAGS = -std=c++17 -Wall -I$(LIBS_DIR)/include $(shell PKG_CONFIG_PATH=$(PKG_CONFIG_PATH) pkg-config --cflags proj) $(shell $(LIBS_DIR)/bin/gdal-config --cflags)
LDFLAGS = -L$(LIBS_DIR)/lib -static $(shell $(LIBS_DIR)/bin/geos-config --static-cclibs) $(shell PKG_CONFIG_PATH=$(PKG_CONFIG_PATH) pkg-config --static --libs proj) $(shell $(LIBS_DIR)/bin/gdal-config --libs) 

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

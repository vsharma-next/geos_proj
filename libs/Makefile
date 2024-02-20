GDAL_VERSION = 3.8.3
SQLITE_VERSION = 3450100
GEOS_VERSION = 3.12.1
PROJ_VERSION = 9.3.1
ZLIB_VERSION = 1.3.1
TIFF_VERSION = 4.6.0

SQLITE_URL = "https://www.sqlite.org/2024/sqlite-autoconf-$(SQLITE_VERSION).tar.gz"
PROJ_URL = "http://download.osgeo.org/proj/proj-$(PROJ_VERSION).tar.gz"
GEOS_URL = "http://download.osgeo.org/geos/geos-$(GEOS_VERSION).tar.bz2"
ZLIB_URL = "http://zlib.net/zlib-$(ZLIB_VERSION).tar.gz"
TIFF_URL = "http://download.osgeo.org/libtiff/tiff-$(TIFF_VERSION).tar.gz"
GDAL_URL = "https://github.com/OSGeo/gdal/releases/download/v$(GDAL_VERSION)/gdal-$(GDAL_VERSION).tar.gz"

PWD = $(shell pwd)
SRC_DIR = build/src
SRC_DIR_FULL = $(PWD)/$(SRC_DIR)
ROOT_DIR = $(PWD)/build/
DIST_DIR = $(PWD)/build/
PREFIX = --prefix=$(ROOT_DIR)
PREFIX_CMAKE = "-DCMAKE_INSTALL_PREFIX=$(ROOT_DIR)"

# # EMCC_CFLAGS = -g4 -O0 -fexceptions -DRENAME_INTERNAL_LIBTIFF_SYMBOLS
# EMCC_CFLAGS = -DRENAME_INTERNAL_LIBTIFF_SYMBOLS
# EMCONFIGURE ?= CXXFLAGS="$(EMCC_CFLAGS)" CFLAGS="$(EMCC_CFLAGS)"

########
# GDAL #
########
GDAL_SRC = $(SRC_DIR)/gdal-$(GDAL_VERSION)

gdal: $(ROOT_DIR)/lib/libgdal.a

$(ROOT_DIR)/lib/libgdal.a: $(GDAL_SRC)/build/Makefile
	cd $(GDAL_SRC)/build; \
	$(EMMAKE) make -j9 VERBOSE=1 install;

$(GDAL_SRC)/build/Makefile: $(ROOT_DIR)/lib/libproj.a $(GDAL_SRC)/CMakeLists.txt
	cd $(GDAL_SRC); \
	rm -rf $(ROOT_DIR)/lib/cmake; \
	mkdir build; \
	cd build; \
	$(EMCMAKE) cmake .. $(PREFIX_CMAKE) -DBUILD_SHARED_LIBS=OFF -DCMAKE_BUILD_TYPE=Release \
	-DCMAKE_VERBOSE_MAKEFILE:BOOL=ON -DCMAKE_RULE_MESSAGES:BOOL=OFF \
	-DACCEPT_MISSING_SQLITE3_MUTEX_ALLOC:BOOL=ON \
	-DGDAL_USE_EXTERNAL_LIBS:BOOL=OFF -DGDAL_USE_INTERNAL_LIBS:BOOL=ON \
	-DBUILD_APPS=OFF \
    -DCMAKE_PREFIX_PATH=$(ROOT_DIR) -DCMAKE_FIND_ROOT_PATH=$(ROOT_DIR) \
    -DGDAL_BUILD_OPTIONAL_DRIVERS=OFF -DOGR_BUILD_OPTIONAL_DRIVERS=OFF -DGDAL_ENABLE_PLUGINS:BOOL=OFF \
    -DPROJ_INCLUDE_DIR=$(ROOT_DIR)/include -DPROJ_LIBRARY_RELEASE=$(ROOT_DIR)/lib/libproj.a

$(GDAL_SRC)/CMakeLists.txt:
	mkdir -p $(SRC_DIR); \
	cd $(SRC_DIR); \
	wget -nc $(GDAL_URL); \
	tar -xf gdal-$(GDAL_VERSION).tar.gz;



########
# GEOS #
########

GEOS_SRC = $(SRC_DIR)/geos-$(GEOS_VERSION)

geos: $(ROOT_DIR)/lib/libgeos.a

$(ROOT_DIR)/lib/libgeos.a: $(GEOS_SRC)/build/Makefile
	cd $(GEOS_SRC)/build; \
	$(EMMAKE) make -j4 install;

$(GEOS_SRC)/build/Makefile: $(GEOS_SRC)/CMakeLists.txt
	cd $(GEOS_SRC); \
    mkdir build; \
	cd build; \
	$(EMCMAKE) cmake .. $(PREFIX_CMAKE) -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=OFF -DBUILD_TESTING=OFF;

$(GEOS_SRC)/CMakeLists.txt:
	mkdir -p $(SRC_DIR); \
	cd $(SRC_DIR); \
	wget -nc $(GEOS_URL); \
	tar -xf geos-$(GEOS_VERSION).tar.bz2;

########
# PROJ #
########
PROJ_SRC = $(SRC_DIR)/proj-$(PROJ_VERSION)

proj: $(ROOT_DIR)/lib/libproj.a

$(ROOT_DIR)/lib/libproj.a: $(PROJ_SRC)/Makefile
	cd $(PROJ_SRC); \
	$(EMMAKE) make install;

$(PROJ_SRC)/Makefile: $(ROOT_DIR)/lib/libtiff.a $(ROOT_DIR)/lib/libsqlite3.a $(PROJ_SRC)/CMakeLists.txt
	cd $(PROJ_SRC); \
	$(EMCMAKE) cmake . $(PREFIX_CMAKE)  \
    -DSQLITE3_INCLUDE_DIR=${ROOT_DIR}/include \
    -DSQLITE3_LIBRARY=${ROOT_DIR}/lib/libsqlite3.a \
    -DTIFF_INCLUDE_DIR=${ROOT_DIR}/include \
    -DTIFF_LIBRARY_RELEASE=${ROOT_DIR}/lib/libtiff.a \
    -DENABLE_CURL=OFF \
    -DBUILD_TESTING=OFF \
    -DBUILD_SHARED_LIBS=OFF \
    -DBUILD_APPS=OFF;


$(PROJ_SRC)/CMakeLists.txt:
	mkdir -p $(SRC_DIR); \
	cd $(SRC_DIR); \
	wget -nc $(PROJ_URL); \
	tar -xf proj-$(PROJ_VERSION).tar.gz;

###########
# SQLITE3 #
###########
SQLITE3_SRC = $(SRC_DIR)/sqlite-autoconf-$(SQLITE_VERSION)

sqlite3: $(ROOT_DIR)/lib/libsqlite3.a

$(ROOT_DIR)/lib/libsqlite3.a: $(SQLITE3_SRC)/Makefile
	cd $(SQLITE3_SRC); \
	$(EMMAKE) make install;

$(SQLITE3_SRC)/Makefile: $(ROOT_DIR)/lib/libz.a $(SQLITE3_SRC)/configure
	cd $(SQLITE3_SRC); \
	$(EMCONFIGURE) ./configure $(PREFIX) --enable-shared=no \
	CFLAGS="-I$(ROOT_DIR)/include -DSQLITE_DISABLE_LFS -DSQLITE_ENABLE_FTS3 -DSQLITE_ENABLE_FTS3_PARENTHESIS -DSQLITE_ENABLE_JSON1 -DSQLITE_THREADSAFE=0 -DSQLITE_ENABLE_NORMALIZE" \
	CPPFLAGS="-I$(ROOT_DIR)/include" \
	LDFLAGS="-L$(ROOT_DIR)/lib";

$(SQLITE3_SRC)/configure:
	mkdir -p $(SRC_DIR); \
	cd $(SRC_DIR); \
	wget -nc $(SQLITE_URL); \
	tar -xf sqlite-autoconf-$(SQLITE_VERSION).tar.gz;

###########
# TIFF #
###########
TIFF_SRC = $(SRC_DIR)/tiff-$(TIFF_VERSION)

tiff: $(ROOT_DIR)/lib/libtiff.a

$(ROOT_DIR)/lib/libtiff.a: $(TIFF_SRC)/Makefile
	cd $(TIFF_SRC); \
	$(EMMAKE) make install;

$(TIFF_SRC)/Makefile: $(ROOT_DIR)/lib/libz.a $(TIFF_SRC)/configure
	cd $(TIFF_SRC); \
	$(EMCONFIGURE) ./configure $(PREFIX) --enable-shared=no --disable-docs \
	--with-zlib-include-dir=${ROOT_DIR}/include \
	--with-zlib-lib-dir=${ROOT_DIR}/lib;

$(TIFF_SRC)/configure:
	mkdir -p $(SRC_DIR); \
	cd $(SRC_DIR); \
	wget -nc $(TIFF_URL); \
	tar -xf tiff-$(TIFF_VERSION).tar.gz;

########
# ZLIB #
########
ZLIB_SRC = $(SRC_DIR)/zlib-$(ZLIB_VERSION)

zlib: $(ROOT_DIR)/lib/libz.a

$(ROOT_DIR)/lib/libz.a: $(ZLIB_SRC)/Makefile
	export PATH=$(ROOT_DIR)/bin:$(PATH); \
	cd $(ZLIB_SRC); \
	$(EMMAKE) make install;

$(ZLIB_SRC)/Makefile: $(ZLIB_SRC)/configure
	export PATH=$(ROOT_DIR)/bin:$(PATH); \
	cd $(ZLIB_SRC); \
	$(EMCONFIGURE) ./configure $(PREFIX) --static;

$(ZLIB_SRC)/configure:
	mkdir -p $(SRC_DIR); \
	cd $(SRC_DIR); \
	wget -nc $(ZLIB_URL); \
	tar -xf zlib-$(ZLIB_VERSION).tar.gz;

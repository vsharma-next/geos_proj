SQLITE_VERSION = 3450100
GEOS_VERSION = 3.12.1
PROJ_VERSION = 9.3.1
ZLIB_VERSION = 1.3.1
TIFF_VERSION = 4.6.0
GEOTIFF_VERSION = 1.7.1

SQLITE_URL = "https://www.sqlite.org/2024/sqlite-autoconf-$(SQLITE_VERSION).tar.gz"
PROJ_URL = "http://download.osgeo.org/proj/proj-$(PROJ_VERSION).tar.gz"
GEOS_URL = "http://download.osgeo.org/geos/geos-$(GEOS_VERSION).tar.bz2"
ZLIB_URL = "http://zlib.net/zlib-$(ZLIB_VERSION).tar.gz"
TIFF_URL = "http://download.osgeo.org/libtiff/tiff-$(TIFF_VERSION).tar.gz"
GEOTIFF_URL = "http://download.osgeo.org/geotiff/libgeotiff/libgeotiff-$(GEOTIFF_VERSION).tar.gz"


PWD = $(shell pwd)
SRC_DIR = build
SRC_DIR_FULL = $(PWD)/$(SRC_DIR)
ROOT_DIR = $(PWD)/build/
DIST_DIR = $(PWD)/build/package/
PREFIX = --prefix=$(ROOT_DIR)
PREFIX_CMAKE = "-DCMAKE_INSTALL_PREFIX=$(ROOT_DIR)"

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

###########
# GEOTIFF #
###########
GEOTIFF_SRC = $(SRC_DIR)/libgeotiff-$(GEOTIFF_VERSION)

geotiff: $(ROOT_DIR)/lib/libgeotiff.a

$(ROOT_DIR)/lib/libgeotiff.a: $(GEOTIFF_SRC)/Makefile
	cd $(GEOTIFF_SRC); \
	$(EMMAKE) make install;

$(GEOTIFF_SRC)/Makefile: $(ROOT_DIR)/lib/libz.a $(ROOT_DIR)/lib/libproj.a $(GEOTIFF_SRC)/configure
	cd $(GEOTIFF_SRC); \
	$(EMCONFIGURE) ./configure $(PREFIX) --enable-shared=no \
	--with-proj=$(ROOT_DIR) --with-libtiff=$(ROOT_DIR) --with-zlib=$(ROOT_DIR) \
	CFLAGS="-I$(ROOT_DIR)/include" \
	CPPFLAGS="-I$(ROOT_DIR)/include" \
	LDFLAGS="-L$(ROOT_DIR)/lib";

$(GEOTIFF_SRC)/configure:
	mkdir -p $(SRC_DIR); \
	cd $(SRC_DIR); \
	wget -nc $(GEOTIFF_URL); \
	tar -xf libgeotiff-$(GEOTIFF_VERSION).tar.gz;

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

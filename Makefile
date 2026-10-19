TARGET	= ev1_test
LIB_DIR	= ./lib
LIB_BUILD = $(LIB_DIR)/build

CFLAGS	= -Wall -Wextra $(PKG_CFLAGS)
CPPFLAGS= -I$(LIB_DIR)
LDFLAGS	= -L$(LIB_BUILD) -Wl,-rpath,$(LIB_BUILD)
LDLIBS	= -ldesfire $(PKG_LIBS)

PKG_CFLAGS	= $(shell pkg-config --cflags libnfc libcrypto)
PKG_LIBS	= $(shell pkg-config --libs libnfc libcrypto)

all: $(TARGET)

$(LIB_BUILD)/libdesfire.so:
	$(MAKE) -C $(LIB_DIR)

$(TARGET): $(TARGET).c | $(LIB_BUILD)/libdesfire.so
	gcc $(CFLAGS) $(CPPFLAGS) $< $(LDFLAGS) $(LDLIBS) -o $@.bin

clean:
	$(MAKE) -C $(LIB_DIR) clean
	rm -f $(TARGET).bin

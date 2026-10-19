TARGET = libdesfire.so
BUILD_DIR = build

CFLAGS = -g -Wall -Wextra -fPIC -I. $(PKG_CFLAGS)

PKG_CFLAGS = $(shell pkg-config --cflags libnfc libcrypto)
PKG_LIBS = $(shell pkg-config --libs libnfc libcrypto)

SRCS = freefare.c \
       mifare_desfire.c \
       mifare_desfire_aid.c \
       mifare_desfire_crypto.c \
       mifare_desfire_error.c \
       mifare_desfire_key.c \
       mifare_key_deriver.c \
       felica.c \
       mad.c \
       mifare_application.c \
       mifare_classic.c \
       mifare_ultralight.c \
       ntag21x_error.c \
       ntag21x.c

OBJS = $(SRCS:%.c=$(BUILD_DIR)/%.o)

all: $(BUILD_DIR)/$(TARGET)

$(BUILD_DIR)/$(TARGET): $(OBJS)
	gcc -shared -o $@ $^ $(PKG_LIBS)

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	gcc $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)
	rm -f ../$(TARGET)
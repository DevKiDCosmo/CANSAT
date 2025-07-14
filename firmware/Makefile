TARGET = kernel8
BUILD = build
SRC = src
PRODUCT = product_1.0v+b

CC = ./gcc-arm-11.2-2022.02-x86_64-aarch64-none-elf/bin/aarch64-none-elf-gcc
LD = ./gcc-arm-11.2-2022.02-x86_64-aarch64-none-elf/bin/aarch64-none-elf-ld
OBJCOPY = ./gcc-arm-11.2-2022.02-x86_64-aarch64-none-elf/bin/aarch64-none-elf-objcopy

CFLAGS = -Wall -nostdlib -nostartfiles -ffreestanding -O2
LDFLAGS = -T linker.ld

SRCS = $(shell find $(SRC) -name '*.c')
OBJS = $(patsubst $(SRC)/%.c,$(BUILD)/%.o,$(SRCS))

all: $(BUILD)/$(PRODUCT)

$(BUILD):
	mkdir -p $(BUILD)

$(BUILD)/%.o: $(SRC)/%.c | $(BUILD)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/$(TARGET).elf: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD)/$(TARGET).img: $(BUILD)/$(TARGET).elf
	$(OBJCOPY) $< -O binary $@
	dd if=/dev/zero bs=1 count=$$((512 - $$(stat -c%s $@) % 512)) >> $@ || true
	printf '\x55\xAA' | dd of=build/kernel8.img bs=1 seek=510 count=2 conv=notrunc
	stat -c%s build/kernel8.img

$(BUILD)/$(PRODUCT): $(BUILD)/$(TARGET).img
	mkdir -p $(BUILD)/$(PRODUCT)
	cp $(BUILD)/$(TARGET).img $(BUILD)/$(PRODUCT)/kernel8.img
	cp $(SRC)/config.txt $(BUILD)/$(PRODUCT)/config.txt

clean:
	rm -rf $(BUILD)

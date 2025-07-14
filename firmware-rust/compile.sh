cargo rustc -- -C link-arg=--script=./linker.ld
mkdir -p build
arm-none-eabi-objcopy -O binary target/armv7a-none-eabi/debug/firmware-rust ./build/kernel8.img

cp ./config/*.* build/


#dd if=/dev/zero bs=1 count=$$((512 - $$(stat -c%s $@) % 512)) >> $@ || true
#printf '\x55\xAA' | dd of=build/kernel8.img bs=1 seek=510 count=2 conv=notrunc
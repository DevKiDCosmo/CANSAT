rm -rf build
rm -rf target

cargo build #--target=armv7a-none-eabi --release

cargo rustc -- -C link-arg=--script=./linker.ld
mkdir -p build
arm-none-eabi-objcopy -O binary target/armv7a-none-eabi/debug/firmware ./build/kernel8.img

cp ./config/*.* build/


if [ -f ./build/kernel8.img ]; then
    pad=$((512 - $(stat -c%s build/kernel8.img) % 512))
    if [ $pad -ne 512 ]; then
        dd if=/dev/zero bs=1 count=$pad >> build/kernel8.img
    fi
    #printf '\x55\xAA' | dd of=build/kernel8.img bs=1 seek=510 count=2 conv=notrunc
    stat -c %s build/kernel8.img
else
    echo "build/kernel8.img nicht gefunden!"
    exit 1
fi


arm-none-eabi-objdump ./build/kernel8.img -D > build/kernel8.img.dump
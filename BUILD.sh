#!/usr/bin/env bash
set -e

echo "[*] Building kernel..."
make

echo "[*] Preparing ISO layout..."
mkdir -p iso_root/boot/limine
mkdir -p iso_root/EFI/BOOT

cp -v bin/sauceOS iso_root/boot/
cp -v limine.conf iso_root/boot/limine/

cp -v limine/limine-bios.sys iso_root/boot/limine/
cp -v limine/limine-bios-cd.bin iso_root/boot/limine/
cp -v limine/limine-uefi-cd.bin iso_root/boot/limine/

cp -v limine/BOOTX64.EFI iso_root/EFI/BOOT/ || true
cp -v limine/BOOTIA32.EFI iso_root/EFI/BOOT/ || true

echo "[*] Creating ISO..."
xorriso -as mkisofs -R -r -J \
  -b boot/limine/limine-bios-cd.bin \
  -no-emul-boot -boot-load-size 4 -boot-info-table \
  -hfsplus -apm-block-size 2048 \
  --efi-boot boot/limine/limine-uefi-cd.bin \
  -efi-boot-part --efi-boot-image --protective-msdos-label \
  iso_root -o image.iso

echo "[*] Installing Limine BIOS stage..."
./limine/limine bios-install image.iso

echo "[*] Running QEMU..."
qemu-system-x86_64 \
  -cdrom image.iso \
  -m 512M \
  -display gtk \
  -serial stdio \
  -audiodev none,id=snd0

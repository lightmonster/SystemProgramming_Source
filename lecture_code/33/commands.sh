#!/usr/bin/env bash
umask
umask 077
mkdir secret1
echo >secret2
ls -ald secret*
umask 022

curl http://www.bbc.com/
if [ ! -f dsl-4.4.10.iso ]; then
  curl -O http://distro.ibiblio.org/damnsmall/current/dsl-4.4.10.iso
fi
qemu-system-x86_64 -k en-us -cdrom dsl-4.4.10.iso

gcc print_bytes.c -o print_bytes && ./print_bytes
./print_bytes | grep 'F2 and F3'

gcc modify_file_bytes.c -o modify_bytes && ./modify_bytes 

mkdir explore
sudo mount -o loop dsl-4.4.10.iso explore
find explore

grep -r HACKED explore/boot/isolinux/

sudo umount explore 

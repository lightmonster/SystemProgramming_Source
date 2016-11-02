#!/usr/bin/env bash
OTHERUSER=$1
if [[ "$OTHERUSER" == "" ]]; then
 echo 'Specify username e.g. _sshd (mac), sshd (Linux)'
 exit 1
fi
echo Setting secret.txt and a.out to be owned by "$OTHERUSER"
sudo chown "$OTHERUSER" secret.txt
sudo chmod 400 secret.txt
sudo rm a.out
gcc hal.c
sudo chown "$OTHERUSER" a.out
ls -al

# BattleStar-OSLib
BattleStar PSP Remake using OSLib

# To Build
Docker Image futurepr0n/pspdev

Windows compile Instructions:
docker run -v ${PWD}:/build futurepr0n/pspdev make

Linux Compile Instructions:
docker run --rm -v "${PWD}:/${PWD}" -u `id -u`:`id -g` -w "${PWD}" futurepr0n/pspdev make -C .


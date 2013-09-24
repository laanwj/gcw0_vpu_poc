Proof of concept for using the Ingenic JZ4770 vpu core on GCW Zero.

This does not provide any video acceleration by itself but running code on the VPU
is the first step towards that.

See also XMBOMX (https://github.com/IngenicSemiconductor/XBOMX).

Usage (test case):

- Make sure that you have a version of buildroot
  (https://github.com/gcwnow/buildroot) later than or equal to commit e151909,
  with a gcc/binutils cross compiler that supports `-mmxu`.
  Otherwise you will get an error during build:

    cc1: error: unrecognized command line option ‘-mmxu’

- Make sure that UBIboot sets the AHB1 bus to a stable
  frequency (166MHz seems to work).

  - If needed, build and apply patch

    git clone https://github.com/gcwnow/UBIBoot.git
    cd UBIBoot
    git am /<path_to_here>/patches/UBIBoot-0001-Change-H1CLK-AHB1-VPU-clock-to-166MHz.patch
    make CONFIG=gcw0

  - Copy bootloader (which of the bin files in `output/gcw0` that you need depends on your specific model) to device and install it

- Make sure you are using a kernel with jz-vpu driver, see the
  https://github.com/gcwnow/linux/tree/jz-3.11-vpu branch

- Set up GCW cross build chain

    export PATH="$PATH:/opt/gcw0-toolchain/usr/bin"
    export GCCPREFIX="mipsel-gcw0-linux-uclibc-"
   
- Run make in `src` 
- Copy `src/firmware/test1_p1.bin` to device
- Copy executables in `src/test` to device
- Run `poc` on device


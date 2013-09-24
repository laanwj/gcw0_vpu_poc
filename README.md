Proof of concept for using the Ingenic JZ4770 vpu core on GCW Zero.

This does not provide any video acceleration by itself but running code on the VPU
is the first step towards that.

See also XMBOMX (https://github.com/IngenicSemiconductor/XBOMX).

Usage (test case):

- Make sure you are using a kernel with jz-vpu driver, see the
  https://github.com/gcwnow/linux/tree/jz-3.11-vpu branch

- Set up GCW cross build chain

    export PATH="$PATH:/opt/gcw0-toolchain/usr/bin"
    export GCCPREFIX="mipsel-gcw0-linux-uclibc-"
   
- Run make in `src` 
- Copy `src/firmware/test1_p1.bin` to device
- Copy executables in `src/test` to device
- Run `poc` on device


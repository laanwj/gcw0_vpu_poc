Proof of concept for using the Ingenic JZ4770 vpu core on GCW Zero.

This does not provide any video acceleration by itself but running code on the VPU
is the first step towards that.

Usage (test case):

- Make sure that you have a version of the toolchain
  from at least OpenDingux 2013-10-04 or
  from https://github.com/gcwnow/buildroot later than or equal to commit e151909,
  with a gcc/binutils cross compiler that supports `-mmxu`.
  Otherwise you will get an error during build:

    cc1: error: unrecognized command line option ‘-mmxu’

- Make sure that your UBIboot is the one from at least
  OpenDingux 2013-10-04 as it sets the AHB1 bus to a stable
  frequency.

- Make sure you are using a kernel with jz-vpu driver, see the
  https://github.com/gcwnow/linux/tree/jz-3.11-vpu branch

- Set up GCW cross build chain

    export PATH="$PATH:/opt/gcw0-toolchain/usr/bin"
    export GCCPREFIX="mipsel-gcw0-linux-uclibc-"
   
- Run make in `src` 
- Copy `src/firmware/test1_p1.bin` to device
- Copy executables in `src/test` to device
- Run `poc` on device

JZ4780 examples
===============

See XMBOMX (https://github.com/IngenicSemiconductor/XBOMX). This is a set of video codecs for the
JZ4780, which is not usable as-is on the JZ4770, but many of the modules (VMAU, EFE, MC, AUX...)
appear to be similar the same so likely it could be ported or at least used to learn information as
to how to use the modules.
The biggest difference between the VPU on JZ4770 and JZ4780 appears to be that the JZ4770 lacks a DMMU, so the
VPU can only address contiguous buffers in physical memory. Instead of a MMU there is a 8-entry TLB,
but with that small size it's not very useful in practice and you'll have to use consecutive
buffers.


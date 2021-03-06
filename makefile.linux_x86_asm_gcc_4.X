#
# makefile for Linux (x86, PPC, alpha ...)
#

OPTFLAGS=-O

ALLFLAGS=${OPTFLAGS} -m32 -s \
    	-D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE \
	-DNDEBUG -D_REENTRANT -DENV_UNIX \
	$(LOCAL_FLAGS)

CXX=g++ $(ALLFLAGS) -DHAVE_GCCVISIBILITYPATCH -fvisibility=hidden -fvisibility-inlines-hidden
CC=gcc $(ALLFLAGS)
CC_SHARED=-fPIC
LINK_SHARED=-fPIC -shared
ASM=nasm -f elf

LOCAL_LIBS=-lpthread -lrcc
LOCAL_LIBS_DLL=$(LOCAL_LIBS) -ldl

CPU=x86
OBJ_CRC32=$(OBJ_CRC32_x86)


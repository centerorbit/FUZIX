export CROSS_AS=cc85 -X -m8085 -c
export CROSS_LD=ld85
export CROSS_CC=cc85
export CROSS_CCOPTS= -X -m8085 -c -Os -I$(ROOT_DIR)/cpu-$(CPU) -I$(ROOT_DIR)/platform-$(TARGET) -I$(ROOT_DIR)/include
export CROSS_CC_SEG2=
export CROSS_CC_SEG3=
export CROSS_CC_SEG4=
export CROSS_CC_SEGDISC= -Tdiscard
export CROSS_CC_FONT=
export CROSS_CC_VIDEO=
export CROSS_CC_NETWORK=
export CROSS_CC_SYS1=
export CROSS_CC_SYS2=
export CROSS_CC_SYS3=
export CROSS_CC_SYS4=
export CROSS_CC_SYS5=
export ASOPTS=-c
export ASMEXT = .S
export BINEXT = .o
export BITS=16
export EXECFORMAT=16

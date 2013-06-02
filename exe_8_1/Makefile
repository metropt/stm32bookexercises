TEMPLATEROOT = ..

# compilation flags for gdb

CFLAGS  +=  -g  -Iff9/src
ASFLAGS += -g 
LDLIBS += -lm

#project files
vpath %.c ff9/src
vpath %.c ff9/src/option

# object files
OBJS=  $(STARTUP) main.o
OBJS+= ff.o spi.o uart.o xprintf.o mmcbb.o
OBJS+= stm32f10x_gpio.o stm32f10x_rcc.o stm32f10x_usart.o misc.o stm32f10x_spi.o core_cm3.o

# include common make file

include $(TEMPLATEROOT)/Makefile.common



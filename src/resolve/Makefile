COMP = resolve

XPT_OBJS = bf$(COMP).h bf$(COMP)callback.h

ALL_OBJS = $(XPT_OBJS) $(IMPL_OBJS) $(MOD_OBJS) $(LIB_OBJS)

ifeq ($(UNAME),DARWIN)
    ALL_OBJS += dolipo
endif

include ../Makefile.inc

CC = g++
CPPFLAGS = -g -D_NOT

#default compile : chk_tracing 
VAR = chk_tracing
CPPFLAGS1 = -g -D_NOT

# (variable, caller, callee) filter compile : mc_chk_no
#VAR = mc_chk_no
CPPFLAGS2 = -g -D_NOT -D_NO

#(mc ID) except compile : mc_fit
#VAR = mc_fit
CPPFLAGS3 = -g -D_NOT -D_COMP

#(variable, caller ,callee) filter and mc ID except compile : mc_fit_no
#VAR = mc_fit_no
CPPFLAGS4 = -g -D_NOT -D_COMP -D_NO

#(variable, caller, callee) filter and mc ID except and value filter compile : mc_fit_no_n
#VAR = mc_fit_no_d
CPPFLAGS5 = -g -D_NOT -D_COMP -D_NO -D_DEP

# (variable, caller, callee) filter and value filter compile : mc_chk_no_d
#VAR = mc_chk_no_d
CPPFLAGS6 = -g -D_NOT -D_NO -D_DEP

ifeq ($(VAR),chk_tracing)
	CPPFLAGS=$(CPPFLAGS1)
endif
ifeq ($(VAR),mc_chk_no)
	CPPFLAGS=$(CPPFLAGS2)
endif
ifeq ($(VAR),mc_fit)
	CPPFLAGS=$(CPPFLAGS3)
endif
ifeq ($(VAR),mc_fit_no)
	CPPFLAGS=$(CPPFLAGS4)
endif
ifeq ($(VAR),mc_fit_no_d)
	CPPFLAGS=$(CPPFLAGS5)
endif
ifeq ($(VAR),mc_chk_no_d)
	CPPFLAGS=$(CPPFLAGS6)
endif

SRCS = $(wildcard *.cpp)
OBJECTS = $(SRCS:.cpp=.o) #Call.o, CallMgr.o, Data.o, main.o, mc.o
all : $(VAR)

chk_tracing: $(OBJECTS)
	$(CC) $(CPPFLAGS1) -o $@ $^
mc_chk_no: $(OBJECTS)
	$(CC) $(CPPFLAGS2) -o $@ $^
mc_fit: $(OBJECTS)
	$(CC) $(CPPFLAGS3) -o $@ $^
mc_fit_no: $(OBJECTS)
	$(CC) $(CPPFLAGS4) -o $@ $^
mc_fit_no_d: $(OBJECTS)
	$(CC) $(CPPFLAGS5) -o $@ $^
mc_chk_no_d: $(OBJECTS)
	$(CC) $(CPPFLAGS6) -o $@ $^
clean:
	rm -f *.o
	rm -f chk_tracing
cleanAll :
	rm -f *.o
	rm -f mc_chk*
	rm -f mc_fit*

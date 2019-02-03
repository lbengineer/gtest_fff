UNITDIR = ../../../obj
OBJS = $(UNITDIR)/gtest-all.o

$(UNITDIR)/%.o: %.cc
	g++ -I.. -I../include -O0 -g3 -Wall -DMOCK_USE_own_TRI_TPLE=1 -c -o "$@" "$<"

all: $(OBJS)

clean:
	-$(RM) $(OBJS)

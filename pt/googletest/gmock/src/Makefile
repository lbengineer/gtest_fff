UNITDIR = ../../../obj
OBJS = $(UNITDIR)/gmock-all.o $(UNITDIR)/gmock_main.o

$(UNITDIR)/%.o: %.cc
	g++ -I.. -I../include -I../../gtest/include -O0 -g3 -Wall -DMOCK_USE_own_TRI_TPLE=1 -c -o "$@" "$<"

all: $(OBJS)

clean:
	-$(RM) $(OBJS)

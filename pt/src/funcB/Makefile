TESTDIR = ../../../product/funcB/src

CURDIR = $(shell pwd)
CURDIRNAME = $(shell basename `pwd`)
SRCS = $(shell echo $$(ls -d *.cpp))
OBJS = $(SRCS:%.cpp=$(OBJDIR)/%.o)

INC = -I./
INC += -I$(CURDIR)/../../googletest/gmock/include
INC += -I$(CURDIR)/../../googletest/gtest/include

INC += -I../include
INC += -I../../funcA/include
INC += -I../../funcB/include

all: $(OBJS)

$(OBJDIR)/%.o: $(CURDIR)/%.cpp
	echo $(CURDIR)
	cd $(TESTDIR) && g++ -fpermissive -c $(INC) -o $@ $<

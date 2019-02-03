SUBDIRS = $(shell echo $$(ls -d src/*/))
SRCFILES = $(shell echo $$(ls -d src/*/*.cpp))
OBJDIR = $(shell pwd)/obj

all:
	cd googletest/gtest/src; make all
	cd googletest/gmock/src; make all
	@for subdir in $(SUBDIRS); do \
		(cd $$subdir && make OBJDIR=$(OBJDIR)); \
	done
	@for srcfile in $(SRCFILES); do \
		BASENAME=`basename $$srcfile .cpp`; \
		g++ -g -o pt_$$BASENAME obj/gmock_main.o obj/gmock-all.o obj/gtest-all.o obj/$$BASENAME.o; \
	done

clean:
	cd googletest/gtest/src; make clean;
	cd googletest/gmock/src; make clean;
	rm -rf $(OBJDIR)/*; rm -rf pt*;


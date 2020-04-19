CXX = g++
CXXFLAGS = -Ofast -Wall -flto -funroll-loops
		   # -g -pg \
		   # -frename-registers \ 
		   # -fassociative-math -freciprocal-math -fno-signed-zeros \ 
		   # -fno-trapping-math
LDFLAGS = $(CXXFLAGS)
TARGET = sigma

SRCS = src/action.cpp src/correlator.cpp src/field.cpp src/histogram.cpp \
	   src/latticeupdate.cpp src/metropolis.cpp src/pandora.cpp src/sigma.cpp \
	   src/sum.cpp src/help.cpp src/print_field.cpp src/correlate.cpp src/main.cpp 
OBJS = $(subst .cpp,.o,$(SRCS))
HDRS = $(filter-out src/main.hpp, $(subst .cpp,.hpp,$(SRCS)))

all: $(TARGET)
	$(info)

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o $@
	$(info Building $@; linking objects)

.PHONY: tar
tar:
	@tar -cvJf $(TARGET).tar.xz makefile $(SRCS) $(HDRS)
	$(info Tarballing all header and source files into $(TARGET).tar.xz)

.PHONY: clean
clean:
	@$(RM) $(OBJS)
	$(info Cleaning up object files)

.PHONY: lint
lint:
	@clang-tidy $(HDRS) $(SRCS)

all: runner
test: runner
	./runner -v

CXXFLAGS += -std=c++11 -I.

CXX_SRC  = runner.cpp
CXX_DEPS = $(patsubst %.cpp,%.d,$(CXX_SRC))

ifneq ($(MAKECMDGOALS),clean)

ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif

endif


runner: runner.o
	$(CXX) $^ $(LDFLAGS) -o $@

runner.o: runner.cpp

runner.cpp: testsuite.h
	cxxtestgen --error-printer -o "$@" "$<"

clean:
	rm -f runner runner.cpp runner.o runner.d

%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c "$<" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@"

.PHONY: clean

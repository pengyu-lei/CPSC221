CXX = g++
LD = g++
CXXFLAGS = -c -g -Og -std=c++14 -Wall -Wextra -pedantic -MP -MMD
LDFLAGS = -std=c++14 -lpthread

DEMO = graphdemo
DEMO_OBJS = graph.o demo.o

TEST = test
TEST_OBJS = test.o graph.o graph_tools.o dsets.o

OBJS_DIR = objs

all: nonasan
nonasan: $(DEMO) $(TEST)

# Pattern rules for object files
$(OBJS_DIR)/%.o: %.cpp | $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

# Create directories
$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)


# Rules for executables... we can use a pattern for the -asan versions, but, unfortunately, we can't use a pattern for the normal executables
$(DEMO):
	$(LD) $^ $(LDFLAGS) -o $@
$(TEST):
	$(LD) $^ $(LDFLAGS) -o $@

# Executable dependencies
$(DEMO):          $(patsubst %.o, $(OBJS_DIR)/%.o,      $(DEMO_OBJS))
$(TEST):          $(patsubst %.o, $(OBJS_DIR)/%.o,      $(TEST_OBJS))

# Include automatically generated dependencies
-include $(OBJS_DIR)/*.d

clean:
	-rm -rf doc *.o $(DEMO) $(TEST) objs

tidy:
	-rm -f images/*.png
	-rm -rf doc

.PHONY: all doc clean tidy nonasan

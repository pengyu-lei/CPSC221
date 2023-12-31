EXE = lab_dict
EXE_FAC = fac
EXE_FIB = fib_generator
EXE_ANAGRAM = anagram_finder
EXE_HOMOPHONE = homophone_puzzle
EXE_COMMON_WORDS = find_common_words

OBJS_DIR = .objs
OBJS_ANAGRAM_STUDENT = anagram_dict.o
OBJS_ANAGRAM_PROVIDED = anagram_finder.o
OBJS_FIB_STUDENT = fib.o
OBJS_FIB_PROVIDED = fib_generator.o
OBJS_MAIN = main.o
OBJS_FAC_PROVIDED = fac.o
OBJS_HOMOPHONE_STUDENT = pronounce_dict.o cartalk_puzzle.o
OBJS_HOMOPHONE_PROVIDED = homophone_puzzle.o
OBJS_COMMON_WORDS_STUDENT = common_words.o
OBJS_COMMON_WORDS_PROVIDED = find_common_words.o

CXX = g++
LD = g++
WARNINGS = -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable
CXXFLAGS = -std=c++1y -g -O0 $(WARNINGS) -MMD -MP -c
LDFLAGS = -std=c++1y -lpthread

all:$(EXE_FAC) \
	$(EXE_FIB) \
	$(EXE) \
	$(EXE_ANAGRAM) \
	$(EXE_HOMOPHONE) $(EXE_HOMOPHONE) \
	$(EXE_COMMON_WORDS)

data:
	svn export https://subversion.ews.illinois.edu/svn/sp17-cs225/_shared/lab_dict_data data

# Pattern rules for object files
$(OBJS_DIR)/%.o: %.cpp | $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

# Create directories
$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

# Rules for executables... we can use a pattern for the -asan versions, but, unfortunately, we can't use a pattern for the normal executables
$(EXE):
	$(LD) $^ $(LDFLAGS) -o $@
$(EXE_FAC):
	$(LD) $^ $(LDFLAGS) -o $@
$(EXE_FIB):
	$(LD) $^ $(LDFLAGS) -o $@
$(EXE_ANAGRAM):
	$(LD) $^ $(LDFLAGS) -o $@
$(EXE_HOMOPHONE):
	$(LD) $^ $(LDFLAGS) -o $@
$(EXE_COMMON_WORDS):
	$(LD) $^ $(LDFLAGS) -o $@

# Executable dependencies
$(EXE):               $(patsubst %.o, $(OBJS_DIR)/%.o,        $(OBJS_COMMON_WORDS_STUDENT)) \
							$(patsubst %.o, $(OBJS_DIR)/%.o,      $(OBJS_ANAGRAM_STUDENT)) \
							$(patsubst %.o, $(OBJS_DIR)/%.o,      $(OBJS_HOMOPHONE_STUDENT))  \
							$(patsubst %.o, $(OBJS_DIR)/%.o,      $(OBJS_FIB_STUDENT)) \
							$(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS_MAIN))
$(EXE_FAC):               $(patsubst %.o, $(OBJS_DIR)/%.o,      $(OBJS_FAC_STUDENT)) $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS_FAC_PROVIDED))
$(EXE_FIB):               $(patsubst %.o, $(OBJS_DIR)/%.o,      $(OBJS_FIB_STUDENT)) $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS_FIB_PROVIDED))
$(EXE_ANAGRAM):           $(patsubst %.o, $(OBJS_DIR)/%.o,      $(OBJS_ANAGRAM_STUDENT)) $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS_ANAGRAM_PROVIDED))
$(EXE_HOMOPHONE):         $(patsubst %.o, $(OBJS_DIR)/%.o,      $(OBJS_HOMOPHONE_STUDENT)) $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS_HOMOPHONE_PROVIDED))
$(EXE_COMMON_WORDS):      $(patsubst %.o, $(OBJS_DIR)/%.o,      $(OBJS_COMMON_WORDS_STUDENT)) $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS_COMMON_WORDS_PROVIDED))

# Include automatically generated dependencies
-include $(OBJS_DIR)/*.d

clean:
	rm -rf $(EXE) \
		$(EXE_FIB) \
		$(EXE_FAC) \
		$(EXE_ANAGRAM) \
		$(EXE_HOMOPHONE) \
		$(EXE_COMMON_WORDS) \
		$(OBJS_DIR)

tidy: clean
	rm -rf doc

.PHONY: all tidy clean

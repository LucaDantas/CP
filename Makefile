.SUFFIXES:
.SUFFIXES: .cpp

GCC = g++

WARNING = -Wall -Wextra -pedantic -Wshadow -Wformat=2 -Wfloat-equal            \
	-Wconversion -Wlogical-op -Wno-unused-result -fno-exceptions               \
	-fsanitize=address -fsanitize=undefined

#OPTMIZE = -O3 -DNDEBUG # Most optimized, disable assertions
#OPTMIZE = -O2 -ggdb3 -DMY_DEBUG_FLAG # Optmization level of OJs + debug
OPTMIZE = -O0 -ggdb3 -DMY_DEBUG_FLAG # Optmization level 0 + debug

STD = -std=c++17

OPTIONSCXX = $(STD) $(OPTMIZE) $(WARNING)

.cpp:
	$(GCC) $< $(OPTIONSCXX) -o $@

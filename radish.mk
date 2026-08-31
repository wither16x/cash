# to improve later
# (we are actually using my relative workspace tree)
include ../radish_os/prefixes.mk

BUILD := Build
BIN := Bin
SRC := Cash
INC := Include

CXX := x86_64-radishos-clang++
CXXFLAGS := -fno-lto \
		-fno-pic \
		-fno-pie \
		-std=c++23 \
		-Wall \
		-Wextra \
		-I$(INC) \
		-MMD \
		-MP
LD := x86_64-radishos-clang++
# to improve later
# (we are actually using my relative workspace tree)
LDFLAGS := -static -nostdlib -z max-page-size=0x1000 \
	-fuse-ld=lld \
	-L$(LIBC_PREFIX) \
	-T ../radish_os/userspace/linker.lds
	
SRCS := $(shell find $(SRC) -name '*.cpp')
OBJS := $(patsubst $(SRC)/%.cpp,$(BUILD)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

TARGET := $(BIN)/cash

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS) | $(BIN)
	$(LD) $(LDFLAGS) \
		-Wl,--start-group -lc++ -lc++abi -lunwind -lc -Wl,--end-group \
		-lclang_rt.builtins-x86_64 \
		-lmelon \
		$^ -o $@

$(BUILD)/%.o: $(SRC)/%.cpp | $(BUILD)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN) $(BUILD):
	mkdir -p $@

-include $(DEPS)

clean:
	rm -rf $(BUILD) $(BIN)
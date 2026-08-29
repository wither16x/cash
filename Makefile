include prefix.mk

BUILD := Build
BIN := Bin
SRC := Cash
INC := Include

CXX := $(PREFIX)clang++
CXXFLAGS := -fno-lto \
		-fno-pic \
		-fno-pie \
		-std=c++23 \
		-Wall \
		-Wextra \
		-I$(INCLUDE) \
		-MMD \
		-MP

SRCS := $(shell find $(SRC) -name '*.cpp')
OBJS := $(patsubst $(SRC)/%.cpp,$(BUILD)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

TARGET := $(BIN)/cash

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS) | $(BIN)
	$(CXX) -fno-pie -no-pie $^ -o $@ -lmelon

$(BUILD)/%.o: $(SRC)/%.cpp | $(BUILD)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN) $(BUILD):
	mkdir -p $@

-include $(DEPS)

clean:
	rm -rf $(BUILD) $(BIN)
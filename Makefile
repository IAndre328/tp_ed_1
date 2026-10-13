CXX      := g++
CXXFLAGS := -std=c++11 -Wall -Wextra -O2

INC_DIR := include
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

TARGET := $(BIN_DIR)/tp1.out

SRCS := $(shell find $(SRC_DIR) -name "*.cpp")
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

.PHONY: all clean run sanitize

all: $(TARGET)

# Liga todos os .o no executavel final
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@

# Compila cada .cpp de src em um .o dentro de obj
# -MMD -MP gera arquivos .d para recompilar quando um .h mudar
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -MMD -MP -c $< -o $@

# Build de depuracao (so para voce): make sanitize
# Usa pasta de objetos propria para nao misturar com o build normal
sanitize:
	$(MAKE) OBJ_DIR=$(OBJ_DIR)/san TARGET=$(BIN_DIR)/tp1_san.out \
		CXXFLAGS="-std=c++11 -Wall -Wextra -g -O1 -fno-omit-frame-pointer -fsanitize=address,undefined" \
		$(BIN_DIR)/tp1_san.out


# Deixa bin e obj vazias (como exigido na entrega)
clean:
	rm -rf $(OBJ_DIR)/* $(BIN_DIR)/*

run:
	./bin/tp1.out

-include $(DEPS)
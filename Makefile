# Definição do compilador e flags
CXX = g++
CXXFLAGS = -std=c++11 -O2 -Wall -Iinclude -MMD -MP
SANITIZER_FLAGS = -fsanitize=address,undefined -g

# Diretórios do projeto
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Executável final exigido pela especificação
TARGET = $(BIN_DIR)/tp1.out

# Listagem automática de ficheiros fonte e objectos
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))
DEPS = $(OBJS:.o=.d)

# Alvo principal
all: $(TARGET)

# Regra para gerar o executável
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@

# Regra para compilar os ficheiros .cpp em .o (dentro de obj/)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Criação automática das pastas obj e bin caso não existam
$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

# Limpeza dos ficheiros compilados
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Alvo opcional para compilar com AddressSanitizer e UndefinedBehaviorSanitizer
sanitize: CXXFLAGS += $(SANITIZER_FLAGS)
sanitize: clean $(TARGET)

# Inclui as dependências geradas automaticamente pelo -MMD
-include $(DEPS)

.PHONY: all clean sanitize
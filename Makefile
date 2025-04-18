CXX       := g++
CXXFLAGS  := -std=c++11 -O2 -Wall
TARGET    := pratica_hash
SOURCES   := main.cpp tabela_hash.cpp
OBJECTS   := $(SOURCES:.cpp=.o)
TEST_FILE := teste_hash.txt

.PHONY: all run clean

# Regra padrão: compila o executável
all: $(TARGET)

# Linka objetos
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compila .cpp em .o
%.o: %.cpp tabela_hash.h
	$(CXX) $(CXXFLAGS) -c $<

# Regra para executar o programa com o arquivo de teste
run: $(TARGET)
	@echo "Executando com $(TEST_FILE)..."
	./$(TARGET) $(TEST_FILE)

# Limpa arquivos objeto e executável
clean:
	rm -f $(OBJECTS) $(TARGET)

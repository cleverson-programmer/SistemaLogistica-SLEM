CXX = g++
CXXFLAGS = -std=c++11 -Wall -I../include
SRC_DIR = ../src
TEST_DIR = .

# Fontes do projeto (excluindo main.cpp)
SRCS = $(filter-out $(SRC_DIR)/main.cpp, $(wildcard $(SRC_DIR)/*.cpp))

# Fontes de teste
TEST_SRCS = $(wildcard $(TEST_DIR)/test_*.cpp)

# Nomes dos executáveis de teste
TEST_TARGETS = $(patsubst $(TEST_DIR)/%.cpp,%,$(TEST_SRCS))

all: $(TEST_TARGETS)

# Regra genérica para compilar testes
%: %.cpp $(SRCS)
	$(CXX) $(CXXFLAGS) $^ -o $@

run_tests: $(TEST_TARGETS)
	for test in $(TEST_TARGETS); do ./$$test; done

clean:
	rm -f $(TEST_TARGETS)
	rm -f *.bin

.PHONY: all run_tests clean

# PARA EXECUTAR OS TESTES
# cd test/
# make           # Compila todos os testes
# make run_tests # Executa todos os testes
# make clean     # Limpa os executáveis de teste
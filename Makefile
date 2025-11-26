# --- Detectar Sistema Operacional ---
UNAME_S := $(shell uname -s)

# --- Compilador ---
CC = gcc
CFLAGS = -Wall -std=c11 -g -Iinclude

# --- Configuração por sistema ---
ifeq ($(UNAME_S), Linux)
    # Linux / WSL
    LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
endif

ifeq ($(UNAME_S), Darwin)
    # macOS (Homebrew)
    CFLAGS += -I/opt/homebrew/include
    LDFLAGS = -L/opt/homebrew/lib -lraylib -lm -ldl -lpthread \
              -framework Cocoa -framework IOKit -framework CoreVideo
endif

# --- Estrutura ---
SRC = $(wildcard src/*.c)
BIN_DIR = bin
TARGET = $(BIN_DIR)/circo_das_facas

# --- Regras ---
all: $(TARGET)

$(TARGET): $(SRC)
	@mkdir -p $(BIN_DIR)
	$(CC) $(SRC) -o $(TARGET) $(CFLAGS) $(LDFLAGS)
	@echo "✅ Compilado com sucesso!"

run: all
	./$(TARGET)

clean:
	rm -rf $(BIN_DIR)
	@echo "🧹 Limpo!"

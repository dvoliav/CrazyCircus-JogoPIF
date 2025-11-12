# --- Compilador e Flags ---
CC = gcc
CFLAGS = -Wall -std=c11 -g \
	-Iinclude \
	-I/opt/homebrew/Cellar/raylib/5.5/include

LDFLAGS = -L/opt/homebrew/Cellar/raylib/5.5/lib \
	-lraylib -lm -ldl -lpthread \
	-framework Cocoa -framework IOKit -framework CoreVideo

# --- Estrutura ---
SRC = $(wildcard src/*.c)
BIN_DIR = bin
TARGET = $(BIN_DIR)/circo_das_facas

# --- Regras ---
all: $(TARGET)

$(TARGET): $(SRC)
	@mkdir -p $(BIN_DIR)
	$(CC) $(SRC) -o $(TARGET) $(CFLAGS) $(LDFLAGS)
	@echo "✅ Compilação concluída! Rode com ./$(TARGET)"

run: all
	./$(TARGET)

clean:
	rm -rf $(BIN_DIR)
	@echo "🧹 Projeto limpo!"

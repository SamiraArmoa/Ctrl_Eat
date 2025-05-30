# Makefile para el proyecto Ctrl_Eat - Carpeta Local

# Compiladores
CC = gcc
CXX = g++

# Flags de compilación
CFLAGS = -Wall -Wextra -std=c99 -g
CXXFLAGS = -Wall -Wextra -std=c++11 -g
LDFLAGS = -lws2_32

# Directorios
SRC_DIR = src
UTILS_DIR = utils
DATA_DIR = data/db
LIB_DIR = lib/sqlite3

# Archivos fuente C
C_SOURCES = $(SRC_DIR)/main.c \
           $(SRC_DIR)/cliente/cliente.c \
           $(SRC_DIR)/empleados/empleados.c \
           $(SRC_DIR)/ingredientes/ingredientes.c \
           $(SRC_DIR)/pedidos/pedidos.c \
           $(SRC_DIR)/productos/productos.c \
           $(SRC_DIR)/restaurantes/restaurantes.c \
           $(UTILS_DIR)/csv_utils.c \
           $(DATA_DIR)/db.c \
           $(LIB_DIR)/sqlite3.c

# Archivos fuente C++
CXX_SOURCES = $(SRC_DIR)/clientSocket.cpp

# Archivos objeto
C_OBJECTS = $(C_SOURCES:.c=.o)
CXX_OBJECTS = $(CXX_SOURCES:.cpp=.o)

# Ejecutables
MAIN_TARGET = CtrlEat.exe
SOCKET_CLIENT_TARGET = SocketClient.exe

# Regla por defecto
all: $(MAIN_TARGET) $(SOCKET_CLIENT_TARGET)

# Compilar aplicación principal (C)
$(MAIN_TARGET): $(C_OBJECTS)
	$(CC) $(C_OBJECTS) -o $@ $(LDFLAGS)

# Compilar cliente socket (C++)
$(SOCKET_CLIENT_TARGET): $(CXX_OBJECTS)
	$(CXX) $(CXX_OBJECTS) -o $@ $(LDFLAGS)

# Reglas para archivos objeto C
%.o: %.c
	$(CC) $(CFLAGS) -I. -I$(LIB_DIR) -c $< -o $@

# Reglas para archivos objeto C++
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -I. -c $< -o $@

# Ejecutar cliente socket
run-client: $(SOCKET_CLIENT_TARGET)
	./$(SOCKET_CLIENT_TARGET)

# Ejecutar aplicación principal
run-main: $(MAIN_TARGET)
	./$(MAIN_TARGET)

# Limpiar archivos generados
clean:
	del /s *.o $(MAIN_TARGET) $(SOCKET_CLIENT_TARGET) 2>nul || echo "No hay archivos que limpiar"

# Limpiar solo ejecutables
clean-exe:
	del $(MAIN_TARGET) $(SOCKET_CLIENT_TARGET) 2>nul || echo "No hay ejecutables que limpiar"

# Crear directorios necesarios
dirs:
	if not exist "data\logs" mkdir "data\logs"
	if not exist "data\db" mkdir "data\db"

# Ayuda
help:
	@echo "Makefile para Ctrl_Eat - Carpeta Local"
	@echo ""
	@echo "Objetivos disponibles:"
	@echo "  all          - Compilar todos los ejecutables"
	@echo "  $(MAIN_TARGET)    - Compilar aplicacion principal"
	@echo "  $(SOCKET_CLIENT_TARGET) - Compilar cliente socket"
	@echo "  run-client   - Ejecutar cliente socket"
	@echo "  run-main     - Ejecutar aplicacion principal"
	@echo "  clean        - Limpiar todos los archivos generados"
	@echo "  clean-exe    - Limpiar solo ejecutables"
	@echo "  dirs         - Crear directorios necesarios"
	@echo "  help         - Mostrar esta ayuda"

# Declarar objetivos que no son archivos
.PHONY: all run-client run-main clean clean-exe dirs help

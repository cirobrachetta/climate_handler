#!/bin/bash

# Opcional: detener el script si hay un error
set -e

# Colores (opcional)
GREEN='\033[0;32m'
NC='\033[0m' # No Color

echo -e "${GREEN}Compilando test...${NC}"

# Compilación
g++ -std=c++17 \
    -DCPPHTTPLIB_NO_STD_BYTE \
    -Iinclude -Itests \
    Test/test_climate.cpp \
    src/ClimateHandler.cpp \
    src/PersistenceHandler.cpp \
    -o test_app.exe

echo -e "${GREEN}Ejecución del test:${NC}"
./test_app.exe

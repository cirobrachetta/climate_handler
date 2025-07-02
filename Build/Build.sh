#!/bin/bash

#para Windows Ejecutar mediante GitBash

#comando para usar el build: 
# chmod +x build.sh (da permisos de ejecucion al archivo)
# ./build.sh (ejecuta)

# Compilador y flags
CXX=g++
CXXFLAGS="-std=c++14"
INCLUDES="-Iinclude"
SRC="main.cpp src/ServerHandler.cpp src/ClimateHandler.cpp src/PersistenceHandler.cpp"
OUT="-o app"
LIBS="-lws2_32"  # Para Windows. No se usa en Linux, pero no rompe si está vacío.

# Compilar
echo "Compilando..."
$CXX $CXXFLAGS $INCLUDES $SRC $OUT $LIBS

# Resultado
if [ $? -eq 0 ]; then
    echo "✅ Compilación exitosa. Ejecutá ./app para correr el servidor."
else
    echo "❌ Error durante la compilación."
fi
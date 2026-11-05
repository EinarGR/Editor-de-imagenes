cmake_minimum_required(VERSION 4.3)
project(PROYECTO2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)


add_executable(PROYECTO2
        main.cpp
        pgm_io.cpp
        pgm_io.h
        integrante1/Imagen.cpp
        integrante1/Imagen.h
)


# Herramienta auxiliar para convertir PGM a BMP y poder ver el resultado.

# El ejecutable arranca con un directorio de trabajo que, segun el entorno y la
# version del IDE, puede ser la carpeta del proyecto o la de compilacion. Copiar
# imagenes/ al directorio de compilacion cubre el segundo caso y evita el error
# "No se pudo abrir el archivo".
file(COPY ${CMAKE_SOURCE_DIR}/imagenes DESTINATION ${CMAKE_BINARY_DIR})

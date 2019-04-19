@echo off

REM Por Rolando A. Rosales J. 15/abril/2019

REM Para ejecutar el codigo fuente (main.cpp) necesita tener instalado MinGw y definir el PATH de g++.exe en las variables de entorno
REM Ejemplo: C:\MinGW\bin

REM  Ejecutar este fichero como administrador y se generara el main.exe con todos los enlaces de compilacion

REM Si al ejecutar el main.exe aparece un mensaje de error "XXXX.dll" y no es freeglut.dll, 
REM es posible que deba instalar en su PC el "vs redistributable" x86


echo Generando main.exe...

REM g++ -o main.exe main.cpp  -L"include\freeglut\lib\x64" -lglu32 -lfreeglut -lopengl32  -Wl,--subsystem,windows
g++  -g -Wall -Og -o main.exe main.cpp  -L"include\freeglut\lib\x64" -lglu32 -lfreeglut -lopengl32 

IF %errorlevel%==0 (
    REM start main.exe
)
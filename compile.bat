@echo off
setlocal

set COMPILER=C:\TDM-GCC-64\bin\g++.exe
set HEADERS_PATH=%cd%\headers
set SOURCES_PATH=%cd%\sources

:: Cambia esta ruta según donde tengas instalado PDCurses
set PDCURSES_INCLUDE=C:\mingw64\include
set PDCURSES_LIB=C:\mingw64\lib

set OUTPUT_NAME=Scoundrel

del %OUTPUT_NAME%.exe

%COMPILER% -g main.cpp %SOURCES_PATH%\*.cpp -I %HEADERS_PATH% -I %PDCURSES_INCLUDE% -L %PDCURSES_LIB% -l:pdcurses.a -static -o %OUTPUT_NAME%

%OUTPUT_NAME%.exe

@echo off

echo Welcome to the Compile helper!

echo.
echo - Compile Options -

set "applicationName=HelloWorld"
set "pch=pch.h"

set "currentDirectory=%~dp0"
set "sourceDirectory=%currentDirectory%source\"
set "targetDirectory=%currentDirectory%bin\"
set "tempDirectory=%currentDirectory%temp\"
set "libDirectory=%currentDirectory%lib\"
set "compilerPath=%currentDirectory%..\Compiler\mingw\mingw64\bin\"

set "compileOptions=-Wall -O -g"
set "additionalOptions=-static -static-libgcc -static-libstdc++ -lwinpthread"

echo Application Name: %applicationName%
echo Precompiled Header: %pch%
echo Current Directory: %currentDirectory%
echo Source Directory: %sourceDirectory%
echo Target Directory: %targetDirectory%
echo Temp Directory: %tempDirectory%
echo Compiler Path: %compilerPath%
echo Compile Options: %compileOptions%
echo Additional Options: %additionalOptions%

echo.
echo - Clean - 
if exist %targetDirectory%%applicationName%.exe del %targetDirectory%%applicationName%.exe && echo Executable removed
cd %tempDirectory%
echo Deleting temporary files:
for /r %%f in (*) do (echo %%f && del %%f)

setlocal enabledelayedexpansion
cd %currentDirectory%

echo.
echo - Include Directories -
set "includes="
for /f "Tokens=* Delims=" %%x in (includes.txt) do (set includes=!includes! -I%%x && echo %%x)

echo.
echo - Defines -
set "defines="
for /f "Tokens=* Delims=" %%x in (defines.txt) do (set defines=!defines! -D%%x && echo %%x)

echo.
echo - Libraries -
cd %libDirectory%
set "libraries="
for /r %%f in (*) do (set libraries=!libraries! -l%%f && echo %%f)

echo.
echo - Files -
cd %sourceDirectory%
set "paths="
for /r %%f in (*.cpp) do (set paths=!paths! %%f && echo %%f)

cd %compilerPath%

echo.
echo Generating precompiled headers...
g++ -x c++-header -o %tempDirectory%%pch%.gch -c %sourceDirectory%%pch% %defines% %includes% %libraries% %compileOptions% %additionalOptions%

echo.
echo Compiling project...
g++ -o %targetDirectory%%applicationName%.exe %paths% %defines% %includes% %libraries% %compileOptions% %additionalOptions%

echo.
echo Compile finished!

start %targetDirectory%%applicationName%.exe
exit
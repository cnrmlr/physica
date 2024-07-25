@echo off
REM Batch script to generate and build a Visual Studio solution using CMake

REM Variables
SET ROOT_DIR=%~dp0..
SET BUILD_DIR=%ROOT_DIR%\build
SET CONFIGURATION=Debug

REM Create build directory if it doesn't exist
if not exist %BUILD_DIR% mkdir %BUILD_DIR%

REM Change to build directory
cd %BUILD_DIR%

REM Generate Visual Studio solution
cmake -G "Visual Studio 17 2022" -A x64 %ROOT_DIR%

REM Build the Visual Studio solution in Debug mode
cmake --build . --config %CONFIGURATION%

REM Change back to the scripts directory
cd %ROOT_DIR%\scripts

echo Done
pause

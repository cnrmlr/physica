@echo off
REM Batch script to install Google Test, generate, and build a Visual Studio solution using CMake

REM Variables
SET ROOT_DIR=%~dp0..
SET BUILD_DIR=%ROOT_DIR%\build
SET CONFIGURATION=Debug
set BUILD_TESTS=OFF

REM Create build directory if it doesn't exist
if not exist %BUILD_DIR% mkdir %BUILD_DIR%

REM Change to build directory
cd %BUILD_DIR%

REM Generate Visual Studio solution using vcpkg toolchain
cmake -G "Visual Studio 17 2022" -A x64 -DCMAKE_TOOLCHAIN_FILE=%VCPKG_ROOT%\scripts\buildsystems\vcpkg.cmake -DBUILD_TESTS=%BUILD_TESTS% %ROOT_DIR%
if %errorlevel% neq 0 (
    echo Failed to generate Visual Studio solution.
    exit /b 1
)

REM Build the main project in Debug mode
cmake --build . --config %CONFIGURATION%
if %errorlevel% neq 0 (
    echo Failed to build the main project.
    exit /b 1
)

REM Change back to the scripts directory
cd %ROOT_DIR%\scripts

echo Done
pause

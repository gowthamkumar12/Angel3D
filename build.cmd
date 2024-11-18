@echo off
setlocal

:: Default values
set BUILD_DIR=_out
set CONFIG=DEBUG
set CLEAN_BUILD=0
set INCREMENTAL_BUILD=0

:: Parse arguments
:parse_args
if "%1"=="" goto done_parse
if "%1"=="-mclean" set CLEAN_BUILD=1
if "%1"=="-mbuild" set INCREMENTAL_BUILD=1
if /I "%1"=="DEBUG" set CONFIG=DEBUG
if /I "%1"=="RELEASE" set CONFIG=RELEASE
if /I "%1"=="DIST" set CONFIG=DIST
shift
goto parse_args

:done_parse

:: If both -mclean and -mbuild are given, prioritize -mclean
if %CLEAN_BUILD% EQU 1 (
    echo Performing a clean build in %BUILD_DIR%...
    rmdir /S /Q %BUILD_DIR%
) else if %INCREMENTAL_BUILD% EQU 1 (
    echo Performing an incremental build in %BUILD_DIR%...
) else (
    echo No build mode specified, defaulting to incremental build...
)

:: Create build directory if it doesn't exist
if not exist %BUILD_DIR% (
    mkdir %BUILD_DIR%
)

:: Move to the build directory
pushd %BUILD_DIR%

:: Run CMake configuration if necessary
if not exist CMakeCache.txt (
    echo Configuring project with CMake for %CONFIG%...
    cmake -G "Visual Studio 16 2019" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_BUILD_TYPE=%CONFIG% ..
) else (
    echo CMake configuration already exists, skipping configuration step.
)

:: Build the project
echo Building project in %CONFIG% mode...
cmake --build . --config %CONFIG%

:: Return to original directory
popd

echo Build complete.
endlocal
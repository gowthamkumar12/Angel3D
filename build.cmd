@echo off

REM Set default build type to incremental
set build_type=incremental

REM Parse command-line arguments
:parse_args
if "%~1" == "" goto execute_build
if "%~1" == "-mbuild" (
    set build_type=incremental
    shift
    goto parse_args
)
if "%~1" == "-mclean" (
    set build_type=clean
    shift
    goto parse_args
)

REM Execute the appropriate build
:execute_build
if "%build_type%" == "clean" (
    echo Performing clean build...
    cmake -E remove_directory _out
)
echo Performing %build_type% build...
cmake -B _out .
cd _out
cmake --build .

echo Build completed.
cd ..

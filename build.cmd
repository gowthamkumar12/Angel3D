@echo off
setlocal EnableDelayedExpansion

REM call 'original command'
python -I %~dp0tools\build.py %*
if !errorlevel! neq 0 goto fail

:success
exit /b 0

:fail
exit /b 1
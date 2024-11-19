@echo off

if "%1"=="" (
    pause
    exit /b
)

mkdir TXT 2>nul

move *.%1 TXT\

pause
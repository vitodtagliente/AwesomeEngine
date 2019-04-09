@echo off
cd editor
if not exist "solution" mkdir solution
cd solution
@echo on
cmake ..
pause

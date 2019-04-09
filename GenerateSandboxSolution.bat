@echo off
cd sandbox
if not exist "solution" mkdir solution
cd solution
@echo on
cmake ..
pause

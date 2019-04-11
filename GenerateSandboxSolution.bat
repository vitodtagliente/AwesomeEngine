@echo off
if not exist "solutions" mkdir solutions
cd solutions
if not exist "sandbox" mkdir sandbox
cd sandbox
@echo on
cmake ../../sandbox
pause

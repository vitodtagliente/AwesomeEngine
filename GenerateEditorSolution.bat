@echo off
if not exist "solutions" mkdir solutions
cd solutions
if not exist "editor" mkdir editor
cd editor
@echo on
cmake ../../editor 
pause

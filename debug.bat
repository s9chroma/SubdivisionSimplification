@echo off

if not exist debug mkdir debug
call remedy build/Debug/LineSimp.exe

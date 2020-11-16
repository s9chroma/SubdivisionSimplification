@echo off

if not exist build mkdir build
pushd build
call cmake ..
call cmake --build .
if not errorlevel 1 call "Debug/LineSimp.exe"
popd


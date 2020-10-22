@echo off

if not exist build mkdir build
pushd build
call cmake ..
call cmake --build .
call "Debug/LineSimp.exe"
popd


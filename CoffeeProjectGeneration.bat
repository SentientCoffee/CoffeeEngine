@echo off

echo Generating Coffee Engine and related projects...
echo.

call Externals\Premake\premake5.exe vs2019 --file="premake5.lua"

echo.
echo Complete.
echo.

pause
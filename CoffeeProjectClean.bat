@echo off

echo Cleaning Coffee Engine and related projects...
echo.

for /d /r . %%d in (.vs) do @if exist "%%d" rd /s /q "%%d"
for /d /r . %%d in (Build) do @if exist "%%d" rd /s /q "%%d"
for /d /r . %%d in (Coffee\Externals\Build) do @if exist "%%d" rd /s /q "%%d"

del /s /q *.vcxproj
del /s /q *.vcxproj.filters
del /s /q *.vcxproj.user
del /s /q *.sln

echo.
echo Complete.
echo.

pause
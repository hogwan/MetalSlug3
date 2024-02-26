@echo off 
for /f "tokens=* delims=" %%a in ('dir /b/s C:\GM\WIn\EngineBase\*.h') do copy /y "%%a" "C:\MetalSlug3\MetalSlug3\EngineBase\"
for /f "tokens=* delims=" %%a in ('dir /b/s C:\GM\WIn\EngineCore\*.h') do copy /y "%%a" "C:\MetalSlug3\MetalSlug3\EngineCore\"
for /f "tokens=* delims=" %%a in ('dir /b/s C:\GM\WIn\EnginePlatform\*.h') do copy /y "%%a" "C:\MetalSlug3\MetalSlug3\EnginePlatform\"

for /f "tokens=* delims=" %%a in ('dir /b/s C:\GM\WIn\EngineBase\*.cpp') do copy /y "%%a" "C:\MetalSlug3\MetalSlug3\EngineBase\"
for /f "tokens=* delims=" %%a in ('dir /b/s C:\GM\WIn\EngineCore\*.cpp') do copy /y "%%a" "C:\MetalSlug3\MetalSlug3\EngineCore\"
for /f "tokens=* delims=" %%a in ('dir /b/s C:\GM\WIn\EnginePlatform\*.cpp') do copy /y "%%a" "C:\MetalSlug3\MetalSlug3\EnginePlatform\"
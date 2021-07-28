
@echo off

for /l %%i in (1, 1, 5) do (
    echo %1_%%i.in
    a.exe < "%1_%%i.in" > tt
    diff "%1_%%i.out" tt
)

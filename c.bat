@echo off
color 0A
::指定 DIR 为拖拽目录
set DIR="%cd%"
echo %DIR%

for /R %DIR% %%f in (.vs *.ncb) do (
    if EXIST "%%f" (
	    echo "%%f"
	    rd /S /Q "%%f"
	    del %%f
    )
)
pause

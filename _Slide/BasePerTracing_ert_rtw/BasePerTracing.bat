
cd .

if "%1"=="" ("C:\PROGRA~1\MATLAB\R2024b\bin\win64\gmake"  DEPRULES=1 -j9  -f BasePerTracing.mk all) else ("C:\PROGRA~1\MATLAB\R2024b\bin\win64\gmake"  DEPRULES=1 -j9  -f BasePerTracing.mk %1)
@if errorlevel 1 goto error_exit

exit /B 0

:error_exit
echo The make command returned an error of %errorlevel%
exit /B 1
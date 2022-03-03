@echo off

for /f "tokens=2 delims==" %%a in ('wmic path Win32_PerfFormattedData_PerfOS_Processor get PercentProcessorTime /value^|

findstr "PercentProcessorTime"') do (set ucpu=%%a)

echo %uCPU%>>CpuUsage
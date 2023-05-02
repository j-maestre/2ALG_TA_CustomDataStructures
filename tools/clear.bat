cls
@echo off
IF EXIST ..\build\.vs rmdir /s /q ..\build\.vs
IF EXIST ..\build\PR00_MemoryNode rmdir /s /q ..\build\PR00_MemoryNode
IF EXIST ..\build\PR01_Vector rmdir /s /q ..\build\PR01_Vector
IF EXIST ..\build\PR02_CircularVector rmdir /s /q ..\build\PR02_CircularVector
IF EXIST ..\build\PR03_MovableVector rmdir /s /q ..\build\PR03_MovableVector
IF EXIST ..\build\PR04_List rmdir /s /q ..\build\PR04_List
IF EXIST ..\build\PR05_DLList rmdir /s /q ..\build\PR05_DLList
IF EXIST ..\build\PR06_CircularList rmdir /s /q ..\build\PR06_CircularList
IF EXIST ..\build\PR07_CircularDLList rmdir /s /q ..\build\PR07_CircularDLList
IF EXIST ..\build\PR08_Stack rmdir /s /q ..\build\PR08_Stack
IF EXIST ..\build\PR09_Queue rmdir /s /q ..\build\PR09_Queue
IF EXIST ..\build\PR10_Logger rmdir /s /q ..\build\PR10_Logger
IF EXIST ..\build\PR11_Comparative rmdir /s /q ..\build\PR11_Comparative
IF EXIST ..\build\PR12_Comparative_STD rmdir /s /q ..\build\PR12_Comparative_STD
IF EXIST ..\build\PR13_SortingAlgorithms rmdir /s /q ..\build\PR13_SortingAlgorithms
IF EXIST ..\build\PR14_CPP_MemoryNode rmdir /s /q ..\build\PR14_CPP_MemoryNode
IF EXIST ..\bin\debug rmdir /s /q ..\bin\debug
IF EXIST ..\bin\release rmdir /s /q ..\bin\release
IF EXIST ..\build rmdir /s /q ..\build
IF EXIST ..\bin rmdir /s /q ..\bin

IF EXIST ..\build\DS_ALG_AI1vs2017.sln del /F ..\build\DS_ALG_AI1vs2017.sln
IF EXIST ..\build\DS_ALG_AI1vs2019.sln del /F ..\build\DS_ALG_AI1vs2019.sln

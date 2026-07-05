@echo off

echo Compilando teste_tarefa...
gcc -std=c17 -Wall -Wextra -Wpedantic -g -O0 testes\teste_tarefa.c model\entidades\tarefa\tarefa.c -o testes\teste_tarefa.exe

if errorlevel 1 (
    echo Erro ao compilar teste_tarefa.
    exit /b 1
)

echo.
echo Executando teste_tarefa...
testes\teste_tarefa.exe

if errorlevel 1 (
    echo.
    echo Existem testes com erro em teste_tarefa.
    exit /b 1
)

echo.
echo Compilando teste_instancia...
gcc -std=c17 -Wall -Wextra -Wpedantic -g -O0 testes\teste_instancia.c model\entidades\tarefa\tarefa.c model\entidades\instancia\instancia.c -o testes\teste_instancia.exe

if errorlevel 1 (
    echo Erro ao compilar teste_instancia.
    exit /b 1
)

echo.
echo Executando teste_instancia...
testes\teste_instancia.exe

if errorlevel 1 (
    echo.
    echo Existem testes com erro em teste_instancia.
    exit /b 1
)

echo.
echo Todos os testes passaram.
exit /b 0
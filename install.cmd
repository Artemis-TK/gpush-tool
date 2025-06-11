@echo off
setlocal enabledelayedexpansion

echo Preparando o ambiente
ping -n 2 localhost >nul
ping -n 2 localhost >nul
ping -n 2 localhost >nul

cd /d %USERPROFILE%
if errorlevel 1 (
    echo Falha ao acessar o diretório do usuário.
    exit /b 1
)

set "BASH_ALIASES=%USERPROFILE%\.bash_aliases"
set "BASHRC=%USERPROFILE%\.bashrc"
set "BASH_PROFILE=%USERPROFILE%\.bash_profile"
set "ALIAS_LINE=    alias gpush=\"~/gpush-tool/bin/gpush\""

if not exist "%BASH_ALIASES%" (
    type nul > "%BASH_ALIASES%"
)

findstr /x /c:"%ALIAS_LINE%" "%BASH_ALIASES%" >nul
if errorlevel 1 (
    echo %ALIAS_LINE%>>"%BASH_ALIASES%"
)

if not exist "%BASHRC%" (
    (
        echo if [ -f ~/.bash_aliases ]; then
        echo     source ~/.bash_aliases
        echo fi
    ) > "%BASHRC%"
)

if not exist "%BASH_PROFILE%" (
    (
        echo if [ -f ~/.bashrc ]; then
        echo     source ~/.bashrc
        echo fi
    ) > "%BASH_PROFILE%"
)

echo Tudo pronto.
echo Se estiver usando Git Bash ou WSL, reinicie o terminal ou execute:
echo source ~/.bash_profile
endlocal
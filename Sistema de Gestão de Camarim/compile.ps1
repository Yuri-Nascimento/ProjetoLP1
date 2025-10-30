# Script de compilação para Windows
# Compile e execute o projeto

Write-Host "=== Compilando Sistema de Gestão de Camarim ===" -ForegroundColor Cyan

# Criar diretórios se não existirem
if (-not (Test-Path "bin")) {
    New-Item -ItemType Directory -Path "bin" | Out-Null
}

# Parâmetros de compilação
$CFLAGS = "-Wall -Wextra -pedantic -std=c++17 -Iheader -Ilib"

# Arquivos fonte
$SOURCES = @(
    "src/pessoa.cpp",
    "src/usuario.cpp",
    "src/artista.cpp",
    "src/item.cpp",
    "src/estoque.cpp",
    "src/camarim.cpp",
    "src/pedido.cpp",
    "src/listacompras.cpp",
    "src/main.cpp"
)

# Compilar
Write-Host "`nCompilando arquivos..." -ForegroundColor Yellow
$sourceFiles = $SOURCES -join " "
$command = "g++ $CFLAGS $sourceFiles -o bin/main.exe"

Invoke-Expression $command

if ($LASTEXITCODE -eq 0) {
    Write-Host "`n✓ Compilação concluída com sucesso!" -ForegroundColor Green
    Write-Host "`nExecutando programa..." -ForegroundColor Cyan
    Write-Host "==========================================`n" -ForegroundColor Cyan
    & ".\bin\main.exe"
} else {
    Write-Host "`n✗ Erro na compilação!" -ForegroundColor Red
    exit 1
}

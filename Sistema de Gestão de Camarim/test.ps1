# Script de compilação e execução de testes para Windows

Write-Host "=== Compilando Testes ===" -ForegroundColor Cyan

# Criar diretórios se não existirem
if (-not (Test-Path "bin")) {
    New-Item -ItemType Directory -Path "bin" | Out-Null
}

# Parâmetros de compilação
$CFLAGS = "-Wall -Wextra -pedantic -std=c++17 -Iheader -Ilib"

# Arquivos fonte (sem main.cpp)
$SOURCES = @(
    "src/pessoa.cpp",
    "src/artista.cpp",
    "src/item.cpp",
    "src/estoque.cpp",
    "src/camarim.cpp",
    "src/pedido.cpp",
    "src/listacompras.cpp",
    "test/teste.cpp"
)

# Compilar
Write-Host "`nCompilando testes..." -ForegroundColor Yellow
$sourceFiles = $SOURCES -join " "
$command = "g++ $CFLAGS $sourceFiles -o bin/teste.exe"

Invoke-Expression $command

if ($LASTEXITCODE -eq 0) {
    Write-Host "`n[OK] Compilacao dos testes concluida com sucesso!" -ForegroundColor Green
    Write-Host "`nExecutando testes..." -ForegroundColor Cyan
    Write-Host "==========================================`n" -ForegroundColor Cyan
    & ".\bin\teste.exe"
} else {
    Write-Host "`n[ERRO] Erro na compilacao dos testes!" -ForegroundColor Red
    exit 1
}

# PIM-Museu
Windows
🔹 Etapa 1: Instalar o Chocolatey (se ainda não tiver)
Abra o PowerShell como administrador
(Procura por PowerShell, clica com botão direito > "Executar como administrador")

Roda o comando abaixo:

Set-ExecutionPolicy Bypass -Scope Process -Force; `
[System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; `
iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))


Fecha e reabre o PowerShell/Terminal depois da instalação.



🔹 Etapa 2: Instalar o mingw com Chocolatey
Depois do choco instalado, rode este comando no terminal (com permissão de admin):

choco install mingw -y


Fecha e reabre o PowerShell/Terminal depois da instalação.

🔹 Etapa 3: Verificar se o GCC está funcionando
Depois da instalação, rode:

gcc --version

Se aparecer algo como:

gcc (MinGW.org GCC-6.3.0-1) 6.3.0
👉 Tá tudo certo!


gcc main.c -o main

🔹 Etapa 4: Voltar pro VS Code e rodar seu código
Agora você já pode: no terminal do vscode


gcc main.c -o main
main.exe



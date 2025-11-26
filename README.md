# Crazy Circus: The Knife Show 🎪🔪
"Crazy Circus: The Knife Show" é uma releitura do clássico jogo do **Campo Minado**. Nessa releitura, o player assume o papel de um palhaço lançador de facas, tentando evitar atingir os animais escondidos sob os quadrados (lonas do circo). A cada acerto seguro, um número revela quantos animais estão próximos, permitindo dedução e estratégia para manter o espetáculo vivo.

Use lógica, estratégia e um pouco de coragem de palhaço lançador de facas para manter o espetáculo vivo e conquistar a plateia, sem acidentes é claro!

_______________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________
Link da gameplay do jogo: https://www.youtube.com/watch?v=NXDLUEWYWSc 
_______________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

Grupo: Ranilton Araújo, Diego Gomes e Felipe Lemos 
_______________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

🎯 Objetivo do Jogo

No "Crazy Circus: The Knife Show", o objetivo é garantir que o espetáculo aconteça sem acidentes! O jogador deve revelar todas as áreas seguras do tabuleiro enquanto evita atingir os animais escondidos sob as lonas do circo.

Cada quadrado revelado com segurança aproxima você da vitória, enquanto os números exibidos indicam quantos animais estão nas proximidades, que são informações essenciais para deduzir onde é seguro lançar as facas.

Para vencer, o jogador deve:

✔️ Revelar todas os quadrados de lona seguros do tabuleiro

✔️ Marcar corretamente os quadrados de lona onde acredita que há animais escondidos

❌ Evitar acertar qualquer animal, pois isso encerra o show imediatamente!

_______________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

🎮 Controles do Jogo:

No "Crazy Circus: The Knife Show", os controles são:

🖱️ Botão Esquerdo do Mouse — Revelar Quadrado 

Use o clique esquerdo para selecionar o quadrado de lona que deseja revelar. Ele mostrará se o espaço está seguro ou se esconde um dos animais do circo que não devem ser atingidos.

🖱️ Botão Direito do Mouse — Marcar Possível Bomba Com o clique direito, você pode marcar um quadrado de lona com o logo do jogo, indicando que suspeita haver um animal escondido ali. Isso ajuda na sua estratégia para evitar erros e manter o espetáculo em segurança.

_______________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

📖 Instruções de Compilação e Execução do Projeto CrazyCircus-JogoPIF:

1. Compilação e Execução no Linux
1.1. Instalar dependências (Ubuntu/Debian)
O projeto utiliza a biblioteca gráfica raylib, além de dependências de OpenGL e X11.
Instale tudo com:
sudo apt update
sudo apt install libraylib-dev libgl1-mesa-dev libx11-dev build-essential

1.2. Baixar o projeto
git clone https://github.com/dvoliav/CrazyCircus-JogoPIF.git
cd CrazyCircus-JogoPIF

1.3. Compilar
O Makefile detecta automaticamente o Linux e usa as flags corretas: make
Isso gerará o executável na pasta: bin/circo_das_facas

1.4. Executar
./bin/circo_das_facas

Se aparecer “Permission denied”, dê permissão:
chmod +x bin/circo_das_facas
./bin/circo_das_facas

1.5. Limpar arquivos gerados
make clean

_______________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________


2. Compilação e Execução no macOS

2.1. Instalar Homebrew (se ainda não tiver)
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

2.2. Instalar dependências
Instale a biblioteca raylib pelo Homebrew: brew install raylib

Isso instalará automaticamente as bibliotecas necessárias.

2.3. Baixar o projeto
git clone https://github.com/dvoliav/CrazyCircus-JogoPIF.git
cd CrazyCircus-JogoPIF

2.4. Compilar
O Makefile detecta automaticamente o macOS (Darwin) e usa as flags adequadas do brew: make

O executável será gerado em:
bin/circo_das_facas
2.5. Executar
./bin/circo_das_facas

Se aparecer aviso de permissão, liberar com: chmod +x bin/circo_das_facas e ./bin/circo_das_facas


2.6. Limpar arquivos gerados: make clean

_______________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________


3. Comandos úteis do Makefile

Compilar tudo : make

Executar diretamente : make run

Limpar arquivos: make clean

_______________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________




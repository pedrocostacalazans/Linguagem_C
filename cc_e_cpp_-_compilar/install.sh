#!/bin/bash
clear
echo "*****************************************"
echo "*         Iniciando instalação          *"
echo "*****************************************"
echo
gcc -Wall -C -DNIX c.c -o c
gcc -Wall -C -DNIX cplus.c -o cplus

mkdir $HOME/.utils/

mv c cplus $HOME/.utils/

chmod +x $HOME/.utils/c
chmod +x $HOME/.utils/cplus

echo '# Utils' >> $HOME/.bashrc
echo 'UTILS="$HOME/.utils"' >> $HOME/.bashrc
echo 'export PATH=$UTILS:$PATH' >> $HOME/.bashrc
echo >> $HOME/.bashrc

source $HOME/.bashrc
echo
echo "*****************************************"
echo "*         Instalação concluída          *"
echo "*****************************************"


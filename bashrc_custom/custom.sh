#!/bin/bash
cp ~/.bashrc ~/.bashrc.old
cat trecho >> ~/.bashrc
clear
echo 'Pode-se ainda descomentar ou acrescentar:'
echo
echo "alias ll='ls -l'"
echo "alias la='ls -A'"
echo "alias l='ls -CF'"
echo "alias cp='cp -i' <-- Este é para perguntar se quer subscrever..."
echo


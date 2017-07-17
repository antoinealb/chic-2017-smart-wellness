#!/bin/sh

# Name of the tmux session

ENV=ilanga

set -e
set -u

cd $(dirname $0)

if tmux list-sessions | grep -q $ENV
then
    tmux attach -t $ENV
else
    tmux new-session -s $ENV -n todo -d
    tmux send-keys -t $ENV 'vim TODO.md' C-m

    tmux new-window -t $ENV -n 'editor'
    tmux send-keys -t $ENV:2 'vim' C-m
    tmux send-keys -t $ENV:2 ':NERDTree' C-m

    tmux new-window -t $ENV -n console

    tmux select-window -t $ENV:1

    tmux attach -t $ENV
fi

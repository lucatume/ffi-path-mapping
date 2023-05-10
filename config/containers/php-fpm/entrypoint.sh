#!/bin/sh

# UID/GID map to unknown user/group, $HOME=/ (the default when no home directory is defined)

eval "$( fixuid )"

php-fpm

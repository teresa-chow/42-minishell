#!/bin/bash

printf "\033[0;33mcd /   change to root \n \033[0m"
cd /
pwd
printf "\033[0;33mcd ~   change to home \n \033[0m"
cd ~
pwd


#Possible error:
# - try to access a folder with permission denied
# - try to access a file instead a folder
# - try to access a folder that doesn't exist

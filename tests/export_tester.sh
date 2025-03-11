#!/bin/bash

##this print ARG="" and not ARG=""""
export ARG=""

##this prints an error
export ARG++=12 ----> bash: export: `ARG++': not a valid identifier

export ARG,ARF --------> bash: export: `ARG,SDS': not a valid identifier

export ZZ=!2 ----------> bash: !2: event not found


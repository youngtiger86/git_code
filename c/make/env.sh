#!/bin/bash

export CODE_HOME=/home/tom/code/git_code/c
export LD_LIBRARY_PATH=${CODE_HOME}/lib:${LD_LIBRARY_PATH}
alias bindir="cd ${CODE_HOME}/bin"
alias libdir="cd ${CODE_HOME}/lib"
alias srcdir="cd ${CODE_HOME}/src"
alias commh="cd ${CODE_HOME}/src/common"
alias clth="cd ${CODE_HOME}/src/client"
alias serh="cd ${CODE_HOME}/src/server"
alias mkh="cd ${CODE_HOME}/make"
alias mk="${CODE_HOME}/make/my_compile.sh"

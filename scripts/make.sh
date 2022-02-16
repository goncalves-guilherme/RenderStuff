#!/bin/bash

command=$1

do_clean() {

    echo "#### Cleanning ####"

    rm -R ./../out/build/*

    echo "done"
}

do_compile() {
    
    echo "#### Compiling ####"
    
    cmake -S ./../ -B ./../out/build/

    make -C ./../out/build/
}

do_run() {

    echo "#### Running ####"

    ./../out/build/RH
}

do_nothing() {

    echo "#### Do Nothing ####"
}

case $command in
"clean")
    do_clean
    ;;
"compile")
    do_compile
    ;;
"run")
    do_run
    ;;
*)
    do_nothing
    ;;
esac


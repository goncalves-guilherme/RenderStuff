#!/bin/bash

command=$1

build_path="./out/build"

do_clean() {

    echo "#### Cleanning ####"

    rm -R "$build_path"/*

    echo "done"
}

do_compile() {
    
    echo "#### Compiling ####"
    
    cmake -DGLFW_BUILD_DOCS=OFF -S ./ -B $build_path

    make -C $build_path
}

do_run() {

    echo "#### Running ####"

    $build_path/RH
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


#!/usr/bin/env bash
# perf
# audio_flinger
# audio_policy
# kernel
#

function debug(){
    case $1 in
        cmd)
            echo -e "$2"
            ;;
        info) #Green
            echo -e "\033[0;32m$2\033[0m\t"
            ;;
        warn) #Yellow
            echo -e "\033[0;33m$2\033[0m\t"
            ;;
        error) #Red
            echo -e "\033[0;31mERROR: $2\033[0m\t"
            ;;
        *) WARN "debug:Don't have this choise!"
    esac
}


function audioflinger(){
    adb shell dumpsys  media.audio_flinger >audio_flinger.log
}
function audiopolicy(){
    adb shell dumpsys media.audio_policy > media.audio_policy
}

function logcat(){
    adb logcat -c;adb logcat > logcat.log
}

function kernel_log(){
    adb logcat -b kernel -c;adb logcat -b kernel >kernel.log
}

function menu() {
    clear
    echo "========================================="
    echo "1. get audioflinger log"
    echo "2. get audiopolicy log"
    echo "3. get logcat log"
    echo "4. get kernel log"
    echo "5. get qxdm log"
    echo "6. get xml"
    echo "7. get init file"
    echo "8. get init file"
    echo "9. exit"
    echo "========================================="
    echo
    echo "Please select the option number and press enter"
    read x

    case $x in

        1)
            audioflinger
            continue
            ;;
        2)
            audiopolicy
            continue
            ;;
        3)
            logcat
            continue
            ;;
        4)
            kernel_log
            continue
            ;;
        5)
            RepoSync
            continue
            ;;
        9)
            exit
            continue
            ;;
    esac

}

menu

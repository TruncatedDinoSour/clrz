#!/usr/bin/env sh

set -e

main() {
    tput civis
    printf "\033[s"

    for line in 0 $(seq "$(tput lines)"); do
        for col in 0 $(seq "$(tput cols)"); do
            tput cup "$line" "$col"
            printf ' '
        done
    done

    printf "\033[u"
    clear

    tput cnorm
}

main "$@"

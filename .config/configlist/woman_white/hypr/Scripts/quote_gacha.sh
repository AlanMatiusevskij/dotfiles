#!/bin/bash
#Motivational. and not.
CACHE="/home/alan/gacha_cache.txt";

center() {
       local text="$1"
       local cols=$(tput cols)
       printf "%*s\n" $(((${#text} + cols) / 2)) "$text"
}

NUMBOFQUOTES=11
generate_random() {
    echo "" >> $CACHE
    random_number=$((RANDOM % ($NUMBOFQUOTES))) 
    
    is_full=1
    #check if cycled through all
    for ((i=0; i < NUMBOFQUOTES; i++)); do
        if ! grep -q "$i" "$CACHE"; then
            is_full=0
            break
        fi
    done        

    if [ "$is_full" -eq "1" ]; then
        > $CACHE
        echo -e "he"
    fi
    
    while grep -q "$random_number" "$CACHE"; do
        random_number=$((RANDOM % ($NUMBOFQUOTES))) 
    done
    
    case $random_number in
        0)
            center "There is nothing beautiful in this world by itself."
            center "Only those who are wounded can see the beauty."
            center "Only those whose lives have been ruined can look at an unruined life and feel relief."
            center "To those who endure even when broken, tears are shed."
            ;;
        1)
            center "Normality is a paved road."
            center "It is comfortable to walk, but no flowers grow."
            echo -e ""
            ;;
        2)
            center "To dream of success while not having the courage to give up something in order to achieve it is arrogance."
            echo -e "\n"
            ;;
        3)
            center "The reason why some could not soar indefinitely,"
            center "even when they once rode through an upward trend," 
            center "was because they would eventually feel satisfied with themselves."
            center "Satisfaction is the enemy of progress."
            ;;
        4)
            center "Every human being is born with talent, and if they can sharpen that talent of theirs, anyone can become a genius."
            echo -e "\n"
            ;;
        5)
            center "Shoot for the moon."
            center "Even if you miss, you will land among the stars."
            echo -e ""
            ;;
        6)
            center "Whatever you choose to do, as long as you take responsibility for your decision, what others think becomes meaningless."
            echo -e "\n"
            ;;
        7)
            center "In life, two things define you:"
            center "your patience when you have nothing and your attitude when you have everything."
            echo -e ""
            ;;
        8)
            center "Time doesn't heal the wounds, it teaches how to live with them."
            echo -e "\n"
            ;;
        9)
            center "What's the most important step a man take?"
            center "It is the next one."
            center "Always the next step."
            ;;
        10)
            center "True steel is born only after tens of thousands of quenches."
            echo -e "\n"
            ;;

        11)
            center ""
            echo -e "\n"
            ;;

        12)
            center ""
            echo -e "\n"
            ;;

        13)
            center ""
            echo -e "\n"
            ;;

        14)
            center ""
            echo -e "\n"
            ;;

        15)
            center ""
            echo -e "\n"
            ;;
    esac

    echo "$random_number " >> $CACHE
}

########################
#Maximum Number of Lines: 4
_test(){
    echo -e "\e[?25l"
    center "There is nothing beautiful in this world by itself."
    center "Only those who are wounded can see the beauty."
    center "Only those whose lives have been ruined can look at an unruined life and feel relief."
    center "To those who endure even when broken, tears are shed." 
    read HOLD
}
#_test
#############

# Generate initial random number between 0 and 4
initial_random=$((RANDOM % 6))
if [ "$initial_random" -eq 3 ]; then
    echo -e "\e[?25l"
    generate_random
    read HOLD
fi

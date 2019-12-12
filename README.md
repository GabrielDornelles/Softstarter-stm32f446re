# Softstarter-stm32f446re
A softstarter system made using the stm32f446re for eletrônica de potência at Liberato

main.c is the stm32 main code, and lcd.c is a library to use a 16x2 display to show some data irl.
There's also a code in Lua that send the kart speed (from mario kart 64) to a c# code using windows forms at visual studio that will send
the kart speed through serial to Stm32f446re. And also the main interface we used to control the climbing and descent times of the motor 
on soft_interface (there's only the .cs files but its simple windows form application).

Most of the eletronic part was built by Vitor Bierhals.

interface:
![alt text](https://imgur.com/qLEbGLH)


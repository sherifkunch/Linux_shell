Да се напише shell скрипт, който приканва потребителя да въведе низ 
- потребителско име на потребител от системата - след което извежда 
на стандартния изход колко активни сесии има потребителят в момента.


read -p "Enter username: " NAME
who | awk '{print $1}' | grep -wF "${NAME}" | wc -l

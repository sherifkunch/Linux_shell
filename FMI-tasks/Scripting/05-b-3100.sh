read -p "Enter username: " NAME
who | awk '{print $1}' | grep -wF "${NAME}" | wc -l

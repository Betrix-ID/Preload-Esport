#!/system/bin/sh
# Checking ID shell
if [ "$(id -u)" -ne 0 ] && [ "$(id -u)" -ne 2000 ]; then
	printf "[ Eror |@Yeye_nat(Yeye)]\n"
   exit 1
fi
# Cheking abi 64 and 32
     if [ ! -f /sdcard/Esport/lib/enc ]; then
         architecture=$(getprop ro.product.cpu.abi)
	if [ "$architecture" = "arm64-v8a" ]; then
		cp /sdcard/Esport/lib/arm64 /sdcard/Esport/enc
	elif [ "$architecture" = "armeabi-v7a" ]; then
		cp /sdcard/Esport/lib/arm /sdcard/Esport/enc
	fi
  fi
# Smart Notification
shell() {
    sor="$1"
    cmd notification post -S bigtext -t '♨️ Perload Esport' 'Tag' "$sor" > /dev/null 2>&1
}
# Style display Terminal
	printf "\n"
	printf "     ☆================================☆\n"
	printf "\n"
	printf "\t\t       ~ Description. Perload Esport .... \n"
	printf "\n"
	printf "\t\t       - Author              :  @UnixeID\n"
	printf "\t\t       - Version             :  1.0\n"
	printf "\t\t       - Release            :  18 - April - 2025\n"
	printf "\t\t       - Shell Name      :  Perload Esport\n"
	printf "\n"
	printf "    |_______________________________________|\n"
	printf "    \\______________________________________/\n"
	printf "\n"
	printf "   Priority Perload Esport.\n"
	printf "\n"
     rm -rf /sdcard/Android/data/*/cache/*
     sleep 2
           # Ambil daftar paket
      package_list=$(pm list package | cut -f2 -d: | tr -d '\r' | xargs -n1)
     control=1
       while IFS= read -r gamelist || [ -n "$gamelist" ]; do
          line=$(echo "$gamelist" | tr -d '\r' | xargs)
              if [ -n "$line" ]; then
        if echo "$package_list" | grep -xq "$line"; then
            echo "  $control. $line"
            control=$((control + 1))
          else
            echo "Paket game '$line' tidak ditemukan."
              fi
                fi
            done < /sdcard/Esport/Gamelist.txt
   # Buat kill proses in background
  pkill -f logcat
       # Buat varibale instlling and uninstalling script
  if [ "$1" = kill ]; then
        if pgrep -f enc > /dev/null 2>&1; then
         echo "  Program is stopped in the backgurond "
         rm /data/local/tmp/enc > /dev/null 2>&1
         pkill -f enc > /dev/null 2>&1
         shell "Program is stopped in the backgurond" 
         pkill -f sh > /dev/null 2>&1       
     else
       echo "Porgam faild stop !"
   fi
  else
     if ! pgrep -f enc > /dev/null 2>&1; then
       cp /sdcard/Esport/enc /data/local/tmp
       chmod 777 /data/local/tmp/enc
       /data/local/tmp/enc > /dev/null 2>&1
    fi 
      sleep 2
        if pgrep -f enc > /dev/null 2>&1; then
        echo " Program is running in the backgurond"
     else
          echo "Porgram faild running !"
     fi
  fi 
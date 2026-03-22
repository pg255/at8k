### HOW TO COMPILE ###
# Install (and star) KalaMake (https://github.com/KalaKit/KalaMake)
# Compile with KalaMake
kalamake --compile project.kmake release-linux

### OPTIONAL: Copy the executable to /bin ###

colorprint() { printf "\033[38;5;208m$1\033[0m"; }

colorprint "DO YOU WANT TO COPY THE EXECUTABLE TO \"/bin/at8k_\"? (y/N) "
read sel

if [[ "$sel" == "y" ]]; then
	sudo cp build/debug-linux/at8k /bin/at8k_
	colorprint "DONE\n"
else
	colorprint "SKIPPING COPY\n"
fi
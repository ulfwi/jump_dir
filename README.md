# Jump dir

A command similar to cd which allows you to jump to a directory (or open in nautilus) using shortcuts.
Shortcuts are stored in jump_dir.config (environment variable JD_CONFIG).

You can also store shortcuts to files here and open them in nano.

## TODO

* Check if it's a valid path to a dir or file (what if it's on a mount path?)
* Add check so that we don't try to add keys with names that are the same as the options
* Add color to prints? https://github.com/owenthereal/ccat

## Setup

To setup jump dir you should add the following line to .bashrc (or similar):

source /path/to/jump_dir/jump_dir.sh

This adds the function jd() which runs the script in the current shell. This is needed to be able to change directory. If you run the script in a separate shell it will only change directory for that shell, not your current shell.

The script also reads the jump_dir.config file and adds all keys to bash completion.


## How to use

### Jumping to a directory with key

jd key

### Adding a shortcut

jd add new_key new_path

### Removing a shortcut

jd rm key_to_remove

### List all current shortcuts

jd list

### List files and directories at shortcut

alias jdl

jd ls key

### Open directory with key in file explorer

alias jdo

jd open
jd open key

### Open file in nano

alias jdn

jd nano key

### Show path from key

alias jdw

jd show key

### Open path in vscode

alias jdv

jd vscode key

### Show contents of file from key

alias jdc

jd cat key

### search for phrase in path from key

alias jds

jd search phrase key


## Building binaries

Run './build'

## Links

Similar functionality:
* https://github.com/wting/autojump
* https://github.com/kigster/warp-dir

## Old bash functions

_get_path_from_key()
(
   # Check if key exists in config file
   INPUT_KEY=$1

   # Iterate over all keys in config file
   return_dir=""
   while read -r line
   do
      # Split up line by spaces and store results in array
      word_array=($line)
      key=${word_array[0]}
      dir=${word_array[1]}

      if [ "$INPUT_KEY" == "$key" ]; then
         # Key found
         return_dir=$dir
      fi
   done < "$JD_CONFIG"

   # Key not found
   echo $return_dir
)

_get_key_list()
(
   # Iterate over all keys in config file
   key_list=""
   while read -r line
   do
      # Split up line by spaces and store results in array
      word_array=($line)
      key=${word_array[0]}
      dir=${word_array[1]}

      # Append key to list of keys
      key_list=$key_list" "$key
   done < "$JD_CONFIG"

   echo $key_list
)

_key_exists()
(
   # Check if key exists in config file
   INPUT_KEY=$1

   dir=$(/home/s0001191/repos/jump_dir/bin/get_path_from_key $JD_CONFIG $INPUT_KEY)
   if [ "$dir" != "" ]; then
      # Key exists
      return 0
   else
      # Key does not exist
      return 1
   fi
)

_add_key()
(
   # Add new key to config file
   new_key=$1
   new_path=$2

   # Check if key exists
   /home/s0001191/repos/jump_dir/bin/key_exists $JD_CONFIG $new_key
   if [ $? == 1 ] ; then
      line=$new_key" "$new_path
      echo $line >> $JD_CONFIG
      echo "Key \"$new_key\" with path \"$new_path\" added to config file"
   else
      echo "Key \"$new_key\" already exists with path \"$(/home/s0001191/repos/jump_dir/bin/get_path_from_key $JD_CONFIG $new_key)\""
   fi
)

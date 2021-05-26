#!/bin/bash
# This file adds the function jd and also adds all
# keys in JD_CONFIG to bash completion.

JD_DIR="/home/s0001191/repos/jump_dir"
JD_CONFIG=$JD_DIR"/jump_dir.config"

_jd()
{
   local OPTIONS="add ls rm remove list open nano show vscode cat -h --help"
   local KEYS="$($JD_DIR/bin/get_key_list $JD_CONFIG)"

   local options_array=($OPTIONS)

   local current_word="${COMP_WORDS[COMP_CWORD]}"
   local prev_word="${COMP_WORDS[COMP_CWORD-1]}"

   local autocomplete_list=""
   if [[ "${options_array[@]}" =~ "${prev_word}" ]] && [[ "$COMP_CWORD" -eq 2 ]]; then
      # Don't autocomplete with options if we've already written an option
      if [ "${prev_word}" == "add" ] || [ "${prev_word}" == "-h" ] || [ "${prev_word}" == "--help" ]; then
         autocomplete_list=""
      else
         autocomplete_list="$KEYS"
      fi
   elif [[ "$COMP_CWORD" -eq 1 ]]; then
      autocomplete_list="$OPTIONS $KEYS"
   else
      autocomplete_list=""
   fi

   # Array of words to complete
   COMPREPLY=( $(compgen -W "${autocomplete_list}" -- ${current_word}) )
}

_jd_alias()
{
   local current_word="${COMP_WORDS[COMP_CWORD]}"

   local autocomplete_list=""
   if [[ "$COMP_CWORD" -eq 1 ]]; then
      autocomplete_list="$($JD_DIR/bin/get_key_list $JD_CONFIG)"
   else
      autocomplete_list=""
   fi

   COMPREPLY=( $(compgen -W "${autocomplete_list}" -- ${current_word}) )
}

_define_jd_variables()
{
   local KEYS="$($JD_DIR/bin/get_key_list $JD_CONFIG)"

   for key in $KEYS
   do
      local key_upper_case=${key^^}
      local variable_name=JD_$key_upper_case
      local path=$($JD_DIR/bin/get_path_from_key $JD_CONFIG $key)
      declare -g "${variable_name}"="$path"
   done
}


jd()
{
   # Check if config file is valid
   if ! $JD_DIR/bin/is_config_file_valid $JD_CONFIG ; then
      printf "Warning! Invalid config file: \'$JD_CONFIG\'.\n"
      return
   fi

   local INPUT_ARG=$1
   local NBR_ARGS=$#

   case $INPUT_ARG in
   -h | --help)
      echo "jd: jd [-h or --help] [add] [list] [rm or remove] [ls] [open] key [dir]"
      echo "   Use shortcuts to jump to a new directory."
      echo "   Config file: $JD_CONFIG"
      echo ""
      echo "   jd key                     Jump to directory with key. Tries cd to folder"
      echo "                              if key is not found. Jumps to \$HOME if no key"
      echo "                              is supplied."
      echo "   jd add new_key [new_path]  Add new shortcut. If no path is supplied the"
      echo "                              current working directory is used."
      echo "   jd rm key_to_remove        Remove shortcut"
      echo ""
      echo "   jd list                    List current shortcuts"
      echo ""
      echo "   jd ls key                  List files and directories at shortcut"
      echo ""
      echo "   jd open key                Open directory with key in nautilus. If no"
      echo "                              key is supplied the current dir is opened."
      echo "   jd nano key                Open file with key in nano"
      echo ""
      echo "   jd show key                Show path corresponding to key"
      echo ""
      echo "   jd vscode key              Open path corresponding to key with vscode If no"
      echo "                              key is supplied the current dir is opened."
      echo "   jd cat key                 Display contents of file corresponding to key"
      ;;
   add)
      if [ $NBR_ARGS -ge 2 ]; then
         # Add new key to config file
         local new_key=$2

         if [ $NBR_ARGS -eq 3 ]; then
            local new_path=$3
         else
            # If no path is supplied the current directory is used
            local new_path=$PWD
         fi

         $JD_DIR/bin/add_key $JD_CONFIG $new_key $new_path
      else
         echo "Too few arguments"
      fi
      ;;
   list)
      $JD_DIR/bin/print_config_file $JD_CONFIG
      ;;
   rm | remove)
      if [ $NBR_ARGS -ge 2 ]; then
         local key_to_remove=$2
         $JD_DIR/bin/remove_key $JD_CONFIG $key_to_remove
      else
         echo "Too few arguments"
      fi
      ;;
   ls)
      if [ $NBR_ARGS -ge 2 ]; then
         # Check if key exists
         local key=$2
         if $JD_DIR/bin/key_exists $JD_CONFIG $key; then
            ll $($JD_DIR/bin/get_path_from_key $JD_CONFIG $key)
         else
            printf "Key \'$key\' does not exist\n"
         fi
      else
         printf "No key chosen\n"
      fi
      ;;
   open)
      if [ $NBR_ARGS -ge 2 ]; then
         local key=$2
         if $JD_DIR/bin/key_exists $JD_CONFIG $key; then
            xdg-open $($JD_DIR/bin/get_path_from_key $JD_CONFIG $key)
         else
            printf "Key \'$key\' does not exist\n"
         fi
      else
         xdg-open .
      fi
      ;;
   nano)
      if [ $NBR_ARGS -ge 2 ]; then
         local key=$2
         if $JD_DIR/bin/key_exists $JD_CONFIG $key; then
            local path=$($JD_DIR/bin/get_path_from_key $JD_CONFIG $key)
            if [[ -f $path ]]; then
               # Check if we need root access to edit file
               local file_owner=$(stat --format '%U' $path)
               if [ "$file_owner" == "root" ]; then
                  sudo nano $path
               else
                  nano $path
               fi
            elif [[ -d $path ]]; then
               echo "$path is a directory"
            else
               echo "$path: No such file or directory"
            fi
         else
            printf "Key \'$key\' does not exist\n"
         fi
      else
         printf "No key chosen\n"
      fi
      ;;
   vscode)
      if [ $NBR_ARGS -ge 2 ]; then
         local key=$2
         if $JD_DIR/bin/key_exists $JD_CONFIG $key; then
            local path=$($JD_DIR/bin/get_path_from_key $JD_CONFIG $key)
            if [[ -d $path ]] || [[ -f $path ]]; then
               code -n $path
            else
               echo "$path: No such file or directory"
            fi
         else
            printf "Key \'$key\' does not exist\n"
         fi
      else
         code -n .
      fi
      ;;
   show)
      if [ $NBR_ARGS -ge 2 ]; then
         local key=$2
         if $JD_DIR/bin/key_exists $JD_CONFIG $key; then
            printf $($JD_DIR/bin/get_path_from_key $JD_CONFIG $key)
         else
            printf "Key \'$key\' does not exist\n"
         fi
      else
         printf "No key chosen\n"
      fi
      ;;
   cat)
      if [ $NBR_ARGS -ge 2 ]; then
         local key=$2
         if $JD_DIR/bin/key_exists $JD_CONFIG $key; then
            cat $($JD_DIR/bin/get_path_from_key $JD_CONFIG $key)
         else
            printf "Key \'$key\' does not exist\n"
         fi
      else
         printf "No key chosen\n"
      fi
      ;;
   "")
      # Jump to default cd location ($HOME)
      cd
      ;;
   *)
      # Check if key exists
      if $JD_DIR/bin/key_exists $JD_CONFIG $INPUT_ARG; then
         cd $($JD_DIR/bin/get_path_from_key $JD_CONFIG $INPUT_ARG)
      elif [ -d "$PWD/$INPUT_ARG" ]; then
         # Use regular cd command if key cannot be found
         cd $INPUT_ARG
      else
         printf "Key or folder \'$INPUT_ARG\' does not exist\n"
      fi
      ;;
   esac
}

jdo()
(
   jd open $@
)

jdl()
(
   jd ls $@
)

jdn()
(
   jd nano $@
)

jds()
(
   jd show $@
)

jdv()
(
   jd vscode $@
)

jdc()
(
   jd cat $@
)

# Add keys to bash completion
complete -F _jd jd
complete -F _jd_alias jdo
complete -F _jd_alias jdl
complete -F _jd_alias jdn
complete -F _jd_alias jds
complete -F _jd_alias jdv
complete -F _jd_alias jdc

# Add variables containing paths
_define_jd_variables

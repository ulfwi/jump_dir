# Jump dir

A command similar to cd which allows you to jump to a directory (or open in nautilus) using shortcuts.
Shortcuts are stored in jump_dir.config (environment variable JD_CONFIG).

You can also store shortcuts to files here and open them in nano.

## Setup

To setup jump dir you should add the following line to .bashrc (or similar):

```source /path/to/jump_dir/jump_dir.sh```

This adds the function jd() which runs the script in the current shell. This is needed to be able to change directory. If you run the script in a separate shell it will only change directory for that shell, not your current shell.

The script also reads the jump_dir.config file and adds all keys to bash completion.

You might need to update some hardcoded paths in ```jump_dir.sh``` and the unit tests (e.g. JD_DIR).

## How to use

### Jumping to a directory with key

```jd key```

### Adding a shortcut

```jd add new_key new_path```

### Removing a shortcut

```jd rm key_to_remove```

### List all current shortcuts

```jd list```

### List files and directories at shortcut

alias jdl

```jd ls key```

### Open directory with key in file explorer

alias jdo

```jd open```
```jd open key```

### Open file in nano

alias jdn

```jd nano key```

### Show path from key

alias jdw

```jd show key```

### Open path in vscode

alias jdv

```jd vscode key```

### Show contents of file from key

alias jdc

```jd cat key```

### search for phrase in path from key

alias jds

```jd search phrase key```


## Building binaries

```./build```

## Run unittests

```./build test```

## Links

Similar functionality:
* https://github.com/wting/autojump
* https://github.com/kigster/warp-dir

## TODO

* Add check so that we don't try to add keys with names that are the same as the options
* Add color to prints? https://github.com/owenthereal/ccat
* Add autocompletion for paths when trying to add a key.
* The help text won't show up if the config file is invalid
* Add check to see if binary files exists

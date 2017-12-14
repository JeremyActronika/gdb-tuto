# Formation gbd

## Compilation

Pour compiler le programme, il faut simplement lancer la commande `make` dans un terminal.

Il faut s'assurer que l'option `-g` est bien ajoutée lors de la compilation pour compiler en mode *debug*.

## Program exection

### simple execution

`./gdb-tuto bug1`

### Execute gdb

```bash
# Launch gdb
gdb gdb-tuto

# ...

# Run program
(gdb) run  bug1

# ...

(gdb)
```

## Use gdb

### Launch gdb

```bash
$ gdb gdb-tuto 
GNU gdb (Ubuntu 7.11.1-0ubuntu1~16.5) 7.11.1
Copyright (C) 2016 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
<http://www.gnu.org/software/gdb/documentation/>.
For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from gdb-tuto...done.
(gdb)
```

### Add breakpoint

```bash
(gdb) break my_entry_display 
Breakpoint 1 at 0x400612: file main.c, line 20.
(gdb) break display_entries_bug1 
Breakpoint 2 at 0x40066e: file main.c, line 30.
(gdb) break main.c:33
Breakpoint 3 at 0x40067e: file main.c, line 33.
```
### Add Regex breakpoint

```bash
(gdb) help rbreak
Set a breakpoint for all functions matching REGEXP.
```

### Get information about breakpoints

```bash
(gdb) info breakpoints
Num     Type           Disp Enb Address            What
1       breakpoint     keep y   0x0000000000400612 in my_entry_display at main.c:20
2       breakpoint     keep y   0x000000000040066e in display_entries_bug1 at main.c:30
3       breakpoint     keep y   0x000000000040067e in display_entries_bug1 at main.c:33
```

### Delete breakpoint

```bash
(gdb) info breakpoints
Num     Type           Disp Enb Address            What
2       breakpoint     keep y   0x000000000040066e in display_entries_bug1 at main.c:30
3       breakpoint     keep y   0x000000000040067e in display_entries_bug1 at main.c:33
```

### Run program

```bash
(gdb) run bug1
Starting program: /home/jeremy/git/gdb-tuto/gdb-tuto bug1

Breakpoint 2, display_entries_bug1 (entry=0x601060 <entries>) at main.c:30
30	    int n_entries = sizeof(entries);
```

Program is stop at breakpoint

### Continue execution to next breakpoint

```bash
(gdb) continue
Continuing.

Breakpoint 3, display_entries_bug1 (entry=0x601060 <entries>) at main.c:33
33	        my_entry_display(&entries[i]);
```

### Print value of variable

`entry` is pointer, so print pointed address and his value.

```bash
(gdb) print entry
$1 = (const MyEntry *) 0x601060 <entries>
(gdb) p *entry
$2 = {first_name = 0x4007c4 "John", last_name = 0x4007c9 "Doe", age = 24}
```

### Execute program step by step

```bash
(gdb) s
my_entry_display (entry=0x601060 <entries>) at main.c:20
20	    printf("Entry:\n");
(gdb) step
Entry:
21	    printf("Name: %s %s\n", entry->first_name, entry->last_name);
```

## Use gdb-server

### Launch gdb server

```bash
$ gdbserver :6666 gdb-tuto 
Process gdb-tuto created; pid = 6744
Listening on port 6666
```

### Launch gdb connected to server

```bash
$ gdb
GNU gdb (Ubuntu 7.11.1-0ubuntu1~16.5) 7.11.1
Copyright (C) 2016 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
<http://www.gnu.org/software/gdb/documentation/>.
For help, type "help".
Type "apropos word" to search for commands related to "word".
(gdb) target remote 127.0.0.1:6666
Remote debugging using 127.0.0.1:6666
Reading /home/jeremy/git/gdb-tuto/gdb-tuto from remote target...
warning: File transfers from remote targets can be slow. Use "set sysroot" to access files locally instead.
Reading /home/jeremy/git/gdb-tuto/gdb-tuto from remote target...
Reading symbols from target:/home/jeremy/git/gdb-tuto/gdb-tuto...done.
Reading /lib64/ld-linux-x86-64.so.2 from remote target...
Reading /lib64/ld-linux-x86-64.so.2 from remote target...
Reading symbols from target:/lib64/ld-linux-x86-64.so.2...Reading /lib64/ld-2.23.so from remote target...
Reading /lib64/.debug/ld-2.23.so from remote target...
(no debugging symbols found)...done.
0x00007ffff7dd7c30 in ?? () from target:/lib64/ld-linux-x86-64.so.2
(gdb) file git/gdb-tuto
A program is being debugged already.
Are you sure you want to change the file? (y or n) y
git/gdb-tuto: Succès.
(gdb)
```

### Launch gdb for NRF52

#### Launch server

Run this script :

```bash
#!/bin/sh

device=nRF52832_xxAA
port=2331

JLinkGDBServer \
    -device $device \
    -port $port \
    -strict \
    -if swd \
    -localhostonly \
    -halt \
    -vd
```

#### Launch gdb

Launch arm gdb

```bash
$ /opt/actronika-toolchain-gcc-arm-none-eabi-4.9.2015q3/bin/arm-none-eabi-gdb build/tactronik-app
GNU gdb (GNU Tools for ARM Embedded Processors) 7.8.0.20150604-cvs
Copyright (C) 2014 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "--host=i686-linux-gnu --target=arm-none-eabi".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
<http://www.gnu.org/software/gdb/documentation/>.
For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from build/tactronik-app...done.
(gdb) target remote :2331
Remote debugging using :2331
0x00000000 in __isr_vector ()
(gdb)
```

## Memo

Command :
  
  * l | list : affiche le code 
  * s | step : fait un step
  * c | continue : continue jusqu'au breakpoint
  * p | print : affiche une variable `print \\x n_entries` (\\x pour hexa)
  * up
  * down
  * help : Permet d'afficher l'helper `help print`
  * set : Permet de setter des paramètre du programme en cours d'exécution `set n_entries=2`
  * call : Permet d'appeler une fonction `call printf("%s", n_entries)`
  * b | break : Créer un breakpoint `break my_entry_display | breazk main.c:33`
  * d | delete : Permet de supprimer un breakpoint `delete 1`
  * condition : Créer une condition sur un breakpoint avec une variable pour stopper le programme `condition 1 i > 2` (condition sur breakpoint N°1, variable i > 2)
  * info breakpoints : Affiche la liste des breakpoints
  * info registers : Affiche les registres
  * watch : Add watchpoint `watch -l entries[0].first_name` (option location permet de regarder la mémoire quand elle est modifiée)
  * finish : sortir du block courant
  * k | kill : kill le programme
  * q | quit

Can use `cgdb` instead of `gdb` to show code and gdb console.

:warning: If use `cgdb` for arm, launch command with gdb in param (`cgdb /opt/actronika-toolchain-gcc-arm-none-eabi-4.9.2015q3/bin/arm-none-eabi-gdb build/tactronik-app build/tactronik-app`).

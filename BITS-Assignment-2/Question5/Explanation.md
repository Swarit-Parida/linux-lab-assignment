# Question 5 – Recovery Mechanisms in vi

## Command 1 – Create a Configuration File

Command:
vi config.conf

Explanation:
Opens vi to create a sample configuration file used to demonstrate 
vi's recovery mechanisms.

---

## Command 2 – Simulate a Crash During Editing

Command:
vi config.conf

Explanation:
Reopens the file and makes unsaved changes; the terminal/vi session is 
then forcibly killed (not saved normally) to simulate a crash before 
the file could be written.

---

## Command 3 – Recover the File

Command:
vi -r config.conf

Explanation:
Starts vi in recovery mode. Since a swap file exists from the 
interrupted session, vi detects it and offers to restore the unsaved 
changes.

---

## Command 4 – Save the Recovered File

Command:
:wq

Explanation:
Saves the recovered content and exits, preserving the restored changes.

---

## Command 5 – Display the File

Command:
cat config.conf

Output: server_name=production
        port=9090
        log_level=DEBUG

Explanation:
Displays the recovered file's contents to confirm the unsaved changes 
were successfully restored.

---

## Command 6 – Verify Recovery-Related Files

Command:
ls -la

Output: total 28
        drwxrwxrwx+ 3 codespace codespace  4096 Jul 24 06:45 .
        drwxrwxrwx+ 7 codespace codespace  4096 Jul 24 03:42 ..
        -rw-r--r--  1 codespace codespace 12288 Jul 24 06:44 .config.conf.swp
        -rw-rw-rw-  1 codespace codespace     0 Jul 24 03:42 Explanation.md
        -rw-rw-rw-  1 codespace codespace    49 Jul 24 06:45 config.conf
        drwxrwxrwx+ 2 codespace codespace  4096 Jul 24 03:42 screenshots

Explanation:
Lists all files including hidden swap files (.config.conf.swp), 
confirming vi's recovery artifacts.

---

## Recovery Mechanisms in vi

Swap Files
Automatically created while editing; preserve unsaved changes if the 
editor or system crashes.

Undo History
The u command reverses recent changes within the current session, but 
does not help after a crash since the session no longer exists.

Registers
Temporarily store deleted/copied text, useful for restoring 
accidentally removed content mid-edit, not for crash recovery.

Backup Files
Copies of the original file made before modification (when backup 
options are enabled), protecting against accidental overwrites.

Auto-Recovery
vi -r filename recovers unsaved data from the swap file after an 
unexpected crash or shutdown.

---

## Most Reliable Recovery Strategy

Swap files combined with vi -r recovery are the most reliable, since 
swap files are created automatically without user action and directly 
restore unsaved work after a crash. Regularly saving with :w and 
enabling backup files add extra protection but rely on the user 
remembering to save — swap files protect even when the user forgets.
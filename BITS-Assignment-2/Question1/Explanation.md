# Question 1 – Duplicate Submission Detection and Backup Script

## Command 1 – Create working directories

Command:
mkdir submissions
mkdir backup

Explanation:
Creates two directories — submissions for storing student assignment 
files and backup for storing unique submissions after deduplication.

---

## Command 2 – Create sample submission files

Command:
echo "Assignment 1" > submissions/student1.txt
echo "Assignment 2" > submissions/student2.txt
echo "Assignment 1" > submissions/student3.txt
echo "Assignment 3" > submissions/student4.txt
echo "Assignment 2" > submissions/student5.txt

Explanation:
Creates five sample submission files. student1/student3 and 
student2/student5 intentionally contain identical content to simulate 
duplicate assignment submissions for testing the script.

---

## Command 3 – Verify files created

Command:
ls submissions

Output: student1.txt  student2.txt  student3.txt  student4.txt  student5.txt

Explanation:
Lists all files in the submissions directory to confirm the sample 
files were created successfully before running the script.

---

## Command 4 – Preview file contents

Command:
cat submissions/*

Output: Assignment 1
        Assignment 2
        Assignment 1
        Assignment 3
        Assignment 2

Explanation:
Displays the contents of all submission files, making it easy to 
manually verify which files are duplicates before the script processes them.

---

## Command 5 – Write the shell script

Command:
vi duplicate_backup.sh

Script content (typed inside vi):

```
backup_dir="backup"

report="report.txt"

errors="errors.log"

mkdir -p "$backup_dir"

> "$report"

> "$errors"

processed=0

duplicates=0

backedup=0

declare -A hashes

for file in submissions/*

do

if [ -f "$file" ]

then

((processed++))

hash=$(md5sum "$file" | awk '{print $1}')

if [[ -n "${hashes[$hash]}" ]]

then

((duplicates++))

else

hashes[$hash]=1

cp "$file" "$backup_dir/" 2>>"$errors"

((backedup++))

fi

fi

done

echo "Files Processed : $processed" >> "$report"

echo "Duplicate Files : $duplicates" >> "$report"

echo "Files Backed Up : $backedup" >> "$report"

echo "Backup Completed."
```

Explanation:
Opens vi to write the script. It uses md5sum to check each file's 
content (not just the filename) to find duplicates. If a file's 
content has already been seen, it's marked as a duplicate; if not, 
it's copied to backup/. The script also writes a summary to 
report.txt and saves any errors to errors.log.

---

## Command 6 – Grant execute permission

Command:
chmod +x duplicate_backup.sh

Explanation:
Grants execute permission to the script's owner, allowing it to be run 
directly with ./duplicate_backup.sh instead of calling bash explicitly.

---

## Command 7 – Run the script

Command:
./duplicate_backup.sh

Output: Backup Completed.

Explanation:
Executes the script. It processes all submission files, detects 
duplicates by content hash, copies unique files to backup/, generates 
report.txt, and logs any errors to errors.log.

---

## Command 8 – Verify backup contents

Command:
ls backup

Output: student1.txt  student2.txt  student4.txt

Explanation:
Lists the files copied into the backup directory, confirming that only 
unique submissions (student1, student2, student4) were backed up — 
duplicates (student3, student5) were correctly excluded.

---

## Command 9 – View the report

Command:
cat report.txt

Output: Files Processed : 5
        Duplicate Files : 2
        Files Backed Up : 3

Explanation:
Displays the generated report showing the total number of files 
processed, duplicate files found, and files successfully backed up.

---

## Command 10 – View the error log

Command:
cat errors.log

Output: Empty

Explanation:
Displays any error messages generated during script execution. An 
empty file indicates the script ran without any file-handling errors.

---
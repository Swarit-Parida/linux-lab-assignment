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


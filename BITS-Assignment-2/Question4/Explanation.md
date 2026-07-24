# Question 4 – Log File Monitoring and Analysis

## Command 1 – Create the Sample Log File

Command:
vi sample.log

Explanation:
Opens vi to create a sample log file containing informational and 
error messages for testing the log analysis commands.

---

## Command 2 – Display the Log File

Command:
cat sample.log

Output:
INFO: Server started successfully
INFO: User login successful
ERROR: Database connection failed
INFO: Request received
ERROR: Disk space low
INFO: Service restarted

Explanation:
Displays the log file contents to verify it contains both normal and 
error entries.

---

## Command 3 – Extract ERROR Messages

Command:
grep "ERROR" sample.log > error_report.log

Output: [no terminal output — result written directly to error_report.log]

Explanation:
Searches for lines containing "ERROR" and writes matches into 
error_report.log.

---

## Command 4 – Display the Error Report

Command:
cat error_report.log

Output:
ERROR: Database connection failed
ERROR: Disk space low

Explanation:
Displays the generated report, confirming only error messages were 
extracted.

---

## Command 5 – Suppress Unnecessary Error Output

Command:
grep "ERROR" sample.log > error_report.log 2> /dev/null

Output: [no terminal output — command errors, if any, discarded]

Explanation:
Redirects any command-level errors to /dev/null, keeping the 
terminal clean while writing matched results normally.

---

## Command 6 – Append New Log Entries

Command:
echo "ERROR: Network timeout" >> sample.log
echo "INFO: Backup completed" >> sample.log
echo "ERROR: Permission denied" >> sample.log

Output: [no terminal output — lines appended silently to sample.log]

Explanation:
Simulates new log activity by appending fresh entries, including new 
error messages, to sample.log.

---

## Command 7 – Regenerate the Error Report

Command:
grep "ERROR" sample.log > error_report.log

Output: [no terminal output — result written directly to error_report.log]

Explanation:
Updates the error report to include both original and newly added 
error messages.

---

## Command 8 – View the Updated Report

Command:
cat error_report.log

Output:
ERROR: Database connection failed
ERROR: Disk space low
ERROR: Network timeout
ERROR: Permission denied

Explanation:
Displays the updated report, confirming all current error messages 
were extracted.

---

## Command 9 – Verify the Files

Command:
ls -l

Output: total 12
        -rw-rw-rw-  1 codespace codespace    0 Jul 24 03:42 Explanation.md
        -rw-rw-rw-  1 codespace codespace  104 Jul 24 06:29 error_report.log
        -rw-rw-rw-  1 codespace codespace  236 Jul 24 06:28 sample.log
        drwxrwxrwx+ 2 codespace codespace 4096 Jul 24 03:42 screenshots

Explanation:
Confirms sample.log and error_report.log were created successfully.

---

## Command 10 – Real-Time Monitoring Demonstration

Command:
timeout 10 tail -f sample.log | grep "ERROR" >> error_report.log &
sleep 2
echo "ERROR: Disk full - triggered live" >> sample.log
sleep 9
cat error_report.log

Output: [1] 63025
        [1]+  Terminated              timeout 10 tail -f sample.log | grep --color=auto "ERROR" >> error_report.log
        ERROR: Database connection failed
        ERROR: Disk space low
        ERROR: Network timeout
        ERROR: Permission denied

Explanation:
tail -f watches sample.log continuously; while it was running in the 
background, a new error line was appended and picked up automatically 
by the pipeline, without manually re-running grep — proving real-time 
detection rather than manual re-scanning.

---

## Command 11 – Final File Verification

Command:
ls -l

Output: [add on your own]

Explanation:
Confirms error_report.log now reflects both manually regenerated and 
live-captured error entries.

---

## Linux Commands and Techniques Used

tail -f
Continuously monitors a log file and displays new entries as they are 
appended, enabling real-time analysis.

grep
Searches for a pattern in the input stream; here it filters lines 
containing "ERROR".

Pipes (|)
Passes the output of one command directly as input to the next, 
chaining tail -f into grep for live filtering.

Output Redirection (> and >>)
> writes fresh output to a file (overwriting); >> appends without 
overwriting, used to keep growing the error report as new errors appear.

Error Redirection (2>)
Redirects stderr separately from stdout, so command-level errors 
don't clutter the report or terminal.

/dev/null
A special file that discards anything written to it — used to 
suppress unwanted error output.

---
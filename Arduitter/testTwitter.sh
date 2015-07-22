cd /root

echo $(date) - Load:$(cat /proc/loadavg) - Disk:$(df -h |head -2|tail -1) - Cam: http://atrent.it:10000 '(!=Chrome)'|  tee testTwitter.log   | ./ttytter

#
# Regular cron jobs for the avian package
#
0 4	* * *	root	[ -x /usr/bin/avian_maintenance ] && /usr/bin/avian_maintenance

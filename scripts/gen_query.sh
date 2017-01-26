set -o errexit

#-----------------------------
# USAGE:
# ./gen_query first_stop last_stop first_query_time interval

# ----------------------------
# CONFIGURATION VARIABLES
. ./config_env.sh

if [ "$IS_ENV_SET" != "true" ]; then
	echo "ERROR: There was a problem setting up the enviroment variables."
	echo "Make sure that the configuration file is in the scripts folder."
	echo "Process cannot continue. Stopping now."
	exit 1
fi

./"$PROJECT_ROOT"/bin/gen_query 1 11270 384 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 396 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 408 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 420 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 432 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 444 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 456 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 456 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 468 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 480 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 492 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 504 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 516 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 528 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 540 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 552 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 564 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 576 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 588 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 600 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 612 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 624 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 636 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 648 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 660 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 672 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 684 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 696 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 708 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 720 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 732 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 744 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 756 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 768 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 780 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 792 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 804 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 816 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 828 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 840 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 852 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 864 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 876 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 888 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 900 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 912 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 924 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 936 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 948 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 960 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 972 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 984 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 996 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1008 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1020 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1032 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1044 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1056 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1068 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1080 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1092 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1104 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1116 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1128 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1140 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1152 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1164 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1176 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1188 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1200 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1212 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1224 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1236 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1248 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1260 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1272 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1284 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1296 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1308 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1320 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1332 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1344 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1356 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1368 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1380 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1392 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1404 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1416 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1428 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1440 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1452 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1464 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1476 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1488 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1500 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1512 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1524 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1536 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1548 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1560 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1572 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1584 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1596 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1608 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1620 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1632 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1644 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1656 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1668 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1680 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1692 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1704 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1716 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1728 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1740 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1752 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1764 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1776 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1788 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1800 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1812 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1824 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1836 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1848 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1860 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1872 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1884 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1896 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1908 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1920 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1932 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1944 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1956 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1968 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1980 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1992 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 2004 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 2016 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 2028 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 2040 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 2052 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 2064 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 2076 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 2088 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 2100 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 2112 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 2124 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 2136 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 2148 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 2160 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 2172 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 2184 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 2196 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 2208 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 2220 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 2232 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 2244 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 2256 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 2268 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 2280 18
./"$PROJECT_ROOT"/bin/gen_query 1 11270 2292 18

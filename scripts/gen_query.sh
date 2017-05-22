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

QUERY_FOLDER="$PROJECT_ROOT"/reach_queries
mkdir -p "$QUERY_FOLDER"

./"$PROJECT_ROOT"/bin/gen_query 1 11270 "$T_IN" "$T_END" "$ITV" "$QUERY_FOLDER"





# viajes [7.00.7.30) domingo 21, duracion 1 hora
#./"$PROJECT_ROOT"/bin/gen_query 1 11270 1812 1818 12 "$QUERY_FOLDER"
#./"$PROJECT_ROOT"/bin/gen_query 1 11270 1944 1950 12 "$QUERY_FOLDER"
#./"$PROJECT_ROOT"/bin/gen_query 1 11270 2100 2106 12 "$QUERY_FOLDER"
#./"$PROJECT_ROOT"/bin/gen_query 1 11270 2232 2238 12 "$QUERY_FOLDER"

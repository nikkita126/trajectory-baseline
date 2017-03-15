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

QUERY_FOLDER="$PROJECT_ROOT"/queries
mkdir -p "$QUERY_FOLDER"

./"$PROJECT_ROOT"/bin/gen_query 1 11270 1812 12 "$QUERY_FOLDER"
./"$PROJECT_ROOT"/bin/gen_query 1 11270 1944 12 "$QUERY_FOLDER"
./"$PROJECT_ROOT"/bin/gen_query 1 11270 2100 12 "$QUERY_FOLDER"
./"$PROJECT_ROOT"/bin/gen_query 1 11270 2232 12 "$QUERY_FOLDER"

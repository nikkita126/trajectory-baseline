set -o errexit

# ----------------------------
# CONFIGURATION VARIABLES
. ./config_env.sh

if [ "$IS_ENV_SET" != "true" ]; then
	echo "ERROR: There was a problem setting up the enviroment variables."
	echo "Make sure that the configuration file is in the scripts folder."
	echo "Process cannot continue. Stopping now."
	exit 1
fi


ENCODED_DISTANCES_FILE=""$PROJECT_ROOT"/datasets/sorted_encoded_distances.txt"
QUERY_DATA_FOLDER=""$PROJECT_ROOT"/query_data/time_q"
DATASET_NAME="sorted_transantiago_encoded_trips"
IN_STOP="1"
END_STOP="11270"
IN_TIME="372"
MINUTE_BUFFER="60"
REACHABILITY_FOLDER=""$PROJECT_ROOT"/other_extracted_data/reachability"

mkdir -p "$REACHABILITY_FOLDER"


./"$PROJECT_ROOT"/bin/calc_reachability "$ENCODED_DISTANCES_FILE" "$QUERY_DATA_FOLDER" "$DATASET_NAME" "$IN_STOP" "$END_STOP" "$IN_TIME" "$MINUTE_BUFFER" "$REACHABILITY_FOLDER"
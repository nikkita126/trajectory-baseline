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

####

STOPS_DICTIONARY_FILE=""$PROJECT_ROOT"/structures/stops.dict"
DATASET_NAME="sorted_transantiago_encoded_trips"
MINUTE_BUFFER=$(( 5 * ITV ))
QUERY_RESULTS_FOLDER=""$PROJECT_ROOT"/query_results/reachability/"$DATASET_NAME"/t"$T_IN"_t"$T_END""
REACHABILITY_FOLDER=""$PROJECT_ROOT"/reachability_measures/sorted_transantiago_encoded_trips/t"$T_IN"_t"$T_END""

mkdir -p "$REACHABILITY_FOLDER"

./"$PROJECT_ROOT"/bin/calc_reachability "$STOPS_DICTIONARY_FILE" "$QUERY_RESULTS_FOLDER" "$DATASET_NAME" "$T_IN" "$T_END" "$MINUTE_BUFFER" "$REACHABILITY_FOLDER"


######

#IN_TIME="1944"

#./"$PROJECT_ROOT"/bin/calc_reachability "$STOPS_DICTIONARY_FILE" "$QUERY_RESULTS_FOLDER" "$DATASET_NAME" "$IN_STOP" "$END_STOP" "$IN_TIME" "$END_TIME" "$MINUTE_BUFFER" "$REACHABILITY_FOLDER"

######

#IN_TIME="2100"

#./"$PROJECT_ROOT"/bin/calc_reachability "$STOPS_DICTIONARY_FILE" "$QUERY_RESULTS_FOLDER" "$DATASET_NAME" "$IN_STOP" "$END_STOP" "$IN_TIME" "$END_TIME" "$MINUTE_BUFFER" "$REACHABILITY_FOLDER"

######

#IN_TIME="2232"

#./"$PROJECT_ROOT"/bin/calc_reachability "$STOPS_DICTIONARY_FILE" "$QUERY_RESULTS_FOLDER" "$DATASET_NAME" "$IN_STOP" "$END_STOP" "$IN_TIME" "$END_TIME" "$MINUTE_BUFFER" "$REACHABILITY_FOLDER"


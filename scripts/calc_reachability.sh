set -o errexit

# ----------------------------
# CONFIGURATION VARIABLES
. ./config_env.sh

if [ "$_IS_ENV_SET" != "true" ]; then
	echo "ERROR: There was a problem setting up the enviroment variables."
	echo "Make sure that the configuration file is in the scripts folder."
	echo "Process cannot continue. Stopping now."
	exit 1
fi

####

STOPS_DICTIONARY_FILE=""$_PROJECT_ROOT"/structures/stops.dict"
DATASET_NAME="sorted_transantiago_encoded_trips"
MINUTE_BUFFER=$(( 5 * _ITV ))
QUERY_RESULTS_FOLDER=""$_PROJECT_ROOT"/query_results/reachability/"$DATASET_NAME"/t"$_T_IN"_t"$_T_END""
REACHABILITY_FOLDER=""$_PROJECT_ROOT"/reachability_measures/sorted_transantiago_encoded_trips/t"$_T_IN"_t"$_T_END""

mkdir -p "$REACHABILITY_FOLDER"

./"$_PROJECT_ROOT"/bin/calc_reachability "$STOPS_DICTIONARY_FILE" "$QUERY_RESULTS_FOLDER" "$DATASET_NAME" "$_T_IN" "$_T_END" "$MINUTE_BUFFER" "$REACHABILITY_FOLDER"


######

#IN_TIME="1944"

#./"$_PROJECT_ROOT"/bin/calc_reachability "$STOPS_DICTIONARY_FILE" "$QUERY_RESULTS_FOLDER" "$_DATASET_NAME" "$IN_STOP" "$END_STOP" "$IN_TIME" "$END_TIME" "$MINUTE_BUFFER" "$REACHABILITY_FOLDER"

######

#IN_TIME="2100"

#./"$_PROJECT_ROOT"/bin/calc_reachability "$STOPS_DICTIONARY_FILE" "$QUERY_RESULTS_FOLDER" "$_DATASET_NAME" "$IN_STOP" "$END_STOP" "$IN_TIME" "$END_TIME" "$MINUTE_BUFFER" "$REACHABILITY_FOLDER"

######

#IN_TIME="2232"

#./"$_PROJECT_ROOT"/bin/calc_reachability "$STOPS_DICTIONARY_FILE" "$QUERY_RESULTS_FOLDER" "$_DATASET_NAME" "$IN_STOP" "$END_STOP" "$IN_TIME" "$END_TIME" "$MINUTE_BUFFER" "$REACHABILITY_FOLDER"


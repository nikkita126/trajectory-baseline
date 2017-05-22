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

SORTED_DATASET=""$PROJECT_ROOT"/datasets/sorted_transantiago_encoded_trips.txt"
#SORTED_DATASET=""$PROJECT_ROOT"/datasets/s_e_test_sample.txt"
#echo "Sorted dataset: $SORTED_DATASET"
#echo "Structure dir: $STRUCTURE_DIR"


#i=372
#while [  $i -lt 2304 ]; do
#	echo $i
#   
#
#	QUERY_FILE=""$PROJECT_ROOT"/reach_queries/s1-s11270_t"$i"+18.txt"
##QUERY_FILE=""$PROJECT_ROOT"/queries/sample_query.txt"
##-----------------------------
## execute program
## queryIndex usage:
##./queryIndex dataset_name path/index/folder path/results/folder < path/query/file
#
#
#	./"$PROJECT_ROOT"/bin/queryIndex "$SORTED_DATASET" "$STRUCTURE_DIR" "$QUERY_FOLDER" < "$QUERY_FILE"
#
#	i=$((i+288))
#done



QUERY_FOLDER=""$RESULTS_DIR"/reachability/sorted_transantiago_encoded_trips/t"$T_IN"_t"$T_END""
mkdir -p "$QUERY_FOLDER"
QUERY_FILE=""$PROJECT_ROOT"/reach_queries/s1_s11270-t"$T_IN"_t"$T_END"+"$ITV".txt"
./"$PROJECT_ROOT"/bin/queryIndex "$SORTED_DATASET" "$STRUCTURE_DIR" "$QUERY_FOLDER" < "$QUERY_FILE"

















#QUERY_FOLDER=""$RESULTS_DIR"/reachability/sorted_transantiago_encoded_trips/t1944_t1950"
#mkdir -p "$QUERY_FOLDER"
#QUERY_FILE=""$PROJECT_ROOT"/reach_queries/s1_s11270-t1944_t1950+12.txt"
#./"$PROJECT_ROOT"/bin/queryIndex "$SORTED_DATASET" "$STRUCTURE_DIR" "$QUERY_FOLDER" < "$QUERY_FILE"


#QUERY_FOLDER=""$RESULTS_DIR"/reachability/sorted_transantiago_encoded_trips/t2100_t2106"
#mkdir -p "$QUERY_FOLDER"
#QUERY_FILE=""$PROJECT_ROOT"/reach_queries/s1_s11270-t2100_t2106+12.txt"
#./"$PROJECT_ROOT"/bin/queryIndex "$SORTED_DATASET" "$STRUCTURE_DIR" "$QUERY_FOLDER" < "$QUERY_FILE"


#QUERY_FOLDER=""$RESULTS_DIR"/reachability/sorted_transantiago_encoded_trips/t2232_t2238"
#mkdir -p "$QUERY_FOLDER"
#QUERY_FILE=""$PROJECT_ROOT"/reach_queries/s1_s11270-t2232_t2238+12.txt"
#./"$PROJECT_ROOT"/bin/queryIndex "$SORTED_DATASET" "$STRUCTURE_DIR" "$QUERY_FOLDER" < "$QUERY_FILE"
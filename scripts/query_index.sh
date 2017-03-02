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

mkdir -p "$RESULTS_DIR"/time_q

#i=372
#while [  $i -lt 2304 ]; do
#	echo $i
#   
#
#	QUERY_FILE=""$PROJECT_ROOT"/queries/s1-s11270_t"$i"+18.txt"
##QUERY_FILE=""$PROJECT_ROOT"/queries/sample_query.txt"
##-----------------------------
## execute program
## queryIndex usage:
##./queryIndex dataset_name path/index/folder path/results/folder < path/query/file
#
#
#	./"$PROJECT_ROOT"/bin/queryIndex "$SORTED_DATASET" "$STRUCTURE_DIR" "$RESULTS_DIR"/time_q < "$QUERY_FILE"
#
#	i=$((i+288))
#done

QUERY_FILE=""$PROJECT_ROOT"/queries/s1-s11270_t372+12.txt"
./"$PROJECT_ROOT"/bin/queryIndex "$SORTED_DATASET" "$STRUCTURE_DIR" "$RESULTS_DIR"/time_q < "$QUERY_FILE"

QUERY_FILE=""$PROJECT_ROOT"/queries/s1-s11270_t432+12.txt"
./"$PROJECT_ROOT"/bin/queryIndex "$SORTED_DATASET" "$STRUCTURE_DIR" "$RESULTS_DIR"/time_q < "$QUERY_FILE"

QUERY_FILE=""$PROJECT_ROOT"/queries/s1-s11270_t504+12.txt"
./"$PROJECT_ROOT"/bin/queryIndex "$SORTED_DATASET" "$STRUCTURE_DIR" "$RESULTS_DIR"/time_q < "$QUERY_FILE"
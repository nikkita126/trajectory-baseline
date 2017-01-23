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

QUERY_FILE=""$PROJECT_ROOT"/queries/input_uchile.txt"
#QUERY_FILE=""$PROJECT_ROOT"/queries/sample_query.txt"
#-----------------------------
# execute program
# queryIndex usage:
#./queryIndex dataset_name path/index/folder path/results/folder < path/query/file

mkdir -p "$RESULTS_DIR"
./"$PROJECT_ROOT"/bin/queryIndex "$SORTED_DATASET" "$STRUCTURE_DIR" "$RESULTS_DIR" < "$QUERY_FILE"
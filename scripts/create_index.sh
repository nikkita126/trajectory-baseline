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
#-----------------------------


# create folder where index and other structures will be stored
mkdir -p "$STRUCTURE_DIR"

#-----------------------------
# execute program
# createIndex usage
# ./createIndex path/sorted_dataset.txt path/index/folder

./"$PROJECT_ROOT"/bin/createIndex "$SORTED_DATASET" "$STRUCTURE_DIR"
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

SORTED_DATASET=""$_PROJECT_ROOT"/datasets/2013-04_et.txt"
#SORTED_DATASET=""$_PROJECT_ROOT"/datasets/s_e_test_sample.txt"
#echo "Sorted dataset: $SORTED_DATASET"
#echo "Structure dir: $_STRUCTURE_DIR"
#-----------------------------


# create folder where index and other structures will be stored
mkdir -p "$_STRUCTURE_DIR"

#-----------------------------
# execute program
# createIndex usage
# ./createIndex path/sorted_dataset.txt path/index/folder

./"$_PROJECT_ROOT"/bin/createIndex "$SORTED_DATASET" "$_STRUCTURE_DIR"

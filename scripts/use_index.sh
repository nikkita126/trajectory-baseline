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

#SORTED_DATASET=""$PROJECT_ROOT"/datasets/sorted_transantiago_travels.txt"
SORTED_DATASET=""$PROJECT_ROOT"/datasets/modif_trayectorias_muestra.txt"
#echo "Sorted dataset: $SORTED_DATASET"
#echo "Structure dir: $STRUCTURE_DIR"
#-----------------------------

# execute program

./"$PROJECT_ROOT"/bin/useIndex "$SORTED_DATASET" "$STRUCTURE_DIR"
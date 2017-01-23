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

ENCODED_DATASET=""$DATASETS_DIR"/transantiago_encoded_trips_1m.txt"

#-----------------------------
#-----------------------------
# execute program
# codeToInt usage
#./codeToInt path/stop_names_and_codes_file.txt path/trajectories_file.txt path/encoded_trajectories_file.txt time_interval(mins)

./"$PROJECT_ROOT"/bin/codeToInt "$DATASETS_DIR"/stop_ids_code.txt "$DATASETS_DIR"/transantiago_trips.txt "$ENCODED_DATASET" 1
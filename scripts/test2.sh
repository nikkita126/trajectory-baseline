
set -o errexit

if [ "$IS_ENV_SET" != "true" ]; then

	. ./config_env.sh

	if [ "$IS_ENV_SET" != "true" ]; then
		echo "ERROR: There was a problem setting up the enviroment variables."
		echo "Make sure that the configuration file is in the scripts folder."
		echo "Process cannot continue. Stopping now."
		exit 1
	else
		echo "wiiiiiiiiiiiii"
	fi

fi





echo "esta es la var1:"
echo $var1

if [ "$a" = "" ]; then

	echo "fail"
fi

if [ "$b" != "" ]; then

	echo "success"
fi

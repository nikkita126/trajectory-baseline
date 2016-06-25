# TO-DO:
#	change script to receive filename as input

# it stops if there's an error
set -o errexit 

echo "Sorting encoded trajectories..."

sort -V ../datasets/transantiago_encoded_travels.txt > ../datasets/sorted_transantiago_travels.txt

echo " DONE"
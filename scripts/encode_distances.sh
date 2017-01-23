#-----------------------------
#-----------------------------
# execute program
# codeToInt usage
#./codeToInt path/stop_names_and_codes_file.txt path/trajectories_file.txt path/encoded_trajectories_file.txt time_interval(mins)

./../bin/encode_distances ../datasets/stop_ids_code.txt /home/cathy/Magister/Tesis/datos_extraidos_bd/distancias/original_files/distancias.csv /home/cathy/Magister/Tesis/datos_extraidos_bd/distancias/original_files/encoded_distances.txt

sort -V /home/cathy/Magister/Tesis/datos_extraidos_bd/distancias/original_files/encoded_distances.txt > /home/cathy/Magister/Tesis/datos_extraidos_bd/distancias/sorted_encoded_distances.txt
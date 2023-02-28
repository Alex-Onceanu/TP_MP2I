#!/bin/bash

# le nom du programme testé est récupéré dans le premier argument
# donné au script. Par exemple si on lance ./do_test ./a.out, executable
# vaudra "./a.out"
executable=$1

# on récupère le dossier contenant l'exécutable. Si on lance do_test doss/monprograme
# alors dossier vaudra "doss". Si on lance do_test ./a.out, doss vaudra "."
dossier="$(dirname $executable)"


# on itère sur chaque fichier dans le dossier test_in/ 
for in_file in "$dossier"/test_in/* ; do

	# base va contenir le nom du fichier actuel, privé de l'extension.
	# par exemple si in_file vaut "test_in/1.in" alors base vaudra "1"
	base=$(basename "$in_file" .in)

	# out_file va contenir le nom du fichier de sortie correspondant.
	# par exemple si in_file vaut "test_in/1.in" alors ou_file vaudra
	# "test_out/1.out"
	out_file="$dossier"/test_out/"$base".out

	# On calcule res, le résultat réel obtenu en lançant l'exécutable
	# avec le fichier de test
	res=$("$executable" < "$in_file")
	# ainsi que expected, le résultat auquel
	# on s'attendait.
	expected=$(cat "$out_file")

	# On compare le résultat réel et le résultat attendu
	if [[ "$res" == "$expected" ]]; then
		echo Test $base passé
	else
		# Si les résultats sont différents on affiche un message d'erreur
		echo Erreur pour le test $base
		echo obtenu:
		echo $res
		echo attendu:
		echo $expected
	fi 
done

printf "// auto-generated from autogen.sh, DO NOT EDIT!\n\n"

printf "// INC_ and DEC_\n"
printf "// usage: cat INC_ or DEC_ to any small number to get n+1 or n-1\n"
max_inc=24
for i in $(seq 0 $[max_inc - 1])
do
	printf "#define INC_$i $[i + 1]\n"
done
for i in $(seq 0 $[max_inc - 1])
do
	printf "#define DEC_$[i + 1] $i\n"
done
printf "\n"

printf "// REMOVE_COMMAS\n"
max_commas=24
for i in $(seq 0 $[max_commas - 1])
do
	printf "#define _AG_REMOVE_COMMAS_$i(a, ...) a _AG_REMOVE_COMMAS_$[i + 1](__VA_ARGS__)\n"
done
printf "#define _AG_REMOVE_COMMAS_$max_commas(a, ...) a\n\n"

printf "// COUNT_THINGS\n"
max_count=24
printf "#define _AG_COUNT_THINGS_NUMBERS "
for i in $(seq $max_count -1 2)
do
	printf "$i, "
done
printf "1\n"
printf "#define _AG_COUNT_THINGS("
for i in $(seq 0 $[max_count - 1])
do
	printf "_$i, "
done
printf "n, ...) n\n\n"

printf "// MAP\n"
max_map=24
printf "#define _AG_MAP_0(macro, order, index, dir, empty)\n"
printf "#define _AG_MAP_1(macro, order, index, dir, item) macro(item, index)\n"
for i in $(seq 2 $max_map)
do
	printf "#define _AG_MAP_$i(macro, order, index, dir, item, ...) order(macro(item, index), _AG_MAP_$[i - 1](macro, order, EXPAND_CAT(dir, index), dir, __VA_ARGS__))\n"
done
printf "\n"
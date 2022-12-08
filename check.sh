#!/bin/bash

if [ $# != 1 ]; then
  echo "error: Invalid number of arguments!" >&2; exit 1
fi

max_input=$1

re='^[0-9]+$'
if ! [[ $max_input =~ $re ]] ; then
   echo "error: '$max_input' is not a valid number." >&2; exit 1
fi

for i in $(seq -f '%04g' 1 $max_input); do
  ./src/bank $i
  echo "Processando entrada $i..."
done

echo ""
diff --unified=0 ./saidas-esperadas ./saidas-prod

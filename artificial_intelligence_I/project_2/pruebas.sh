#!/bin/bash
CONTADOR=0
while [  $CONTADOR -lt 10 ]; 
do
    LD_LIBRARY_PATH=. ./localSearch >> resulGeneral
    let CONTADOR=CONTADOR+1 
    echo $CONTADOR
done

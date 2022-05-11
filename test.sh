#!/bin/bash

IP=$1
PARAM=$2
FILTER="host $IP or dst $IP"

echo "IP: $IP"
echo "Param: $PARAM"
echo "Filter: $FILTER"

if [ -z "$PARAM" ]; then
  echo "Usage: test.sh <param>"
  exit 1
fi

if [ "$PARAM" = "capture" ]; then
	tshark -O icmp -f "$FILTER" -w test.pcap -a duration:10
elif [ "$PARAM" = "analyze" ]; then
	tshark -O icmp -r test.pcap
fi

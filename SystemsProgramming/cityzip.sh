#!/bin/sh

# Globals

URL="https://www.zipcodestogo.com/"
STATE="Indiana"
CITY=".*"

# Functions

usage() {
	cat 1>&2 <<EOF
Usage: zipcode.sh

	-c    CITY  Which city to search
	-s    STATE Which state to search (Indiana)

If no CITY is specified, then all the zip coes for the STATE are displayed.
EOF
	exit $1
}

state() {
	# Grabs the zipcode information based on the URL and State name
	curl -s "$URL$STATE/"
}

zipcode() {
	# Grabs the City specified by URL and state name and outputs only zip
	state | grep -E ".com/$CITY/[A-Z]+/[0-9]+/\">[0-9]+</a>" | sed -E 's/^.*>([0-9]+)<.*$/\1/'
}

whitespace(){
	# corrects whitespace
	echo $1 | sed -E 's/ /%20/'
}

# Parse Command Line Options

while [ $# -gt 0 ]; do
    case $1 in
    -h) usage 0;;
	-s) STATE="$2"; shift;;
	-c) CITY="$2"; shift;;
     *) usage 1;;
    esac
    shift
done

# fix whitespace in the state name and cities
STATE=$(whitespace "$STATE")

# Display information
zipcode

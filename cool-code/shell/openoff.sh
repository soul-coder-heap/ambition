#!/bin/bash
echo "$(exiftool *cpp | grep Page_count | cut -d ":" -f2 | tr '\n' '+')""0" | bc

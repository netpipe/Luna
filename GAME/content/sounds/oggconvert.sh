 find . -name "*.wav" | while read in; do oggenc "$in" ; done;
 find . -name "*.wav" | while read in; do rm "$in" ; done
 find . -name "*.WAV" | while read in; do oggenc "$in" ; done
 find . -name "*.WAV" | while read in; do rm "$in" ; done

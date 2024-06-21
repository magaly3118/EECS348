
#!/bin/bash

input="The five boxing wizards jump quickly"

# Question 1: In the input string, Match "bo", followed by any string of any length, including the empty string, followed by "ng".
echo "Question1"
echo "$input" | grep -o 'bo.*ng'

# Question 2: In the input string, Match a word, at least four letters long, that doesn’t contain "u"
echo "Question2"
echo "$input" | grep -o '\b[a-tv-zA-TV-Z]\{4,\}\b'

# Question 3: In the input string, match three consecutive words, where the middle word begins with "b".
echo "Question3"
echo "$input" | grep -o '\b\w*\sb\w*\s\w*\b'

# Question 4: Identify all function declarations (including parameters)
echo "Question4"
grep -E '^\w+\s+(\w+\s*)+\([^)]*\)\s*{' sample.c

# Question 5: Extract lines where a C++ structure is defined using awk
echo "Question5"
awk '/^struct\s\w+\s{$/, /^};$/' sample.c

# Question 6: Replace "marks" with "score" in the code1_2.cpp using sed
echo "Question6"
sed -e 's/marks/score/g' sample.c

# Question 7: Find lines where a function is defined with at least two arguments
echo "Question7"
grep -E '^(\w*\s*){2,}\([^),]+(\,[^)]+)+\)\s{$' sample.c

# Question 8: Identify lines with preprocessor directives using grep
echo "Question8"
grep '^#.*$' sample.c

# Question 9: Using grep count the total number of lines that contain function declarations or definitions in both files.
echo "Question9"
grep -E -c '^\w+\s+(\w+\s*)+\([^)]*\)\s*{' sample.c

# Question 10: Extract and list all unique function names using grep and cut
echo "Question10"
grep -Eo '\b\w+\([^)]*\)' sample.c | cut -d '(' -f1 | sort -u

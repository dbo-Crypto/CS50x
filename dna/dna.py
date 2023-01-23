#############################################################################
# When I test my program with 2.txt and 3.txt the result is not match.      #
# However, the check50 return name. I quite don't understand why.           #
#                                                                           #
# 18.txt and 20.txt are returning the match with the most common points     #
# with the sequence. I don't understand why it should return "No match"     #
##############################################################################

import csv
import sys
import pprint


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        exit()

    # TODO: Read database file into a variable
    str_list = []
    db = []
    with open(sys.argv[1], "r") as database:
        db_reader = csv.DictReader(database)

        for row in db_reader:
            db.append(row)
            temp = row.keys()
        for i in temp:
            str_list.append(i)
    str_list.pop(0)
    #print(f"str_list: {str_list}")
    # pprint.pprint(db)

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2], "r") as sequence:
        seq_reader = csv.reader(sequence)
        for row in seq_reader:
            seq = row[0]

    # TODO: Find longest match of each STR in DNA sequence
    match = {}
    result = {}
    temp = []
    counter = 0
    counter2 = 0
    count = 0
    for i in str_list:
        longest = longest_match(seq, i)
        match[i] = longest
    #print(f"match: {match}")

    # TODO: Check database for matching profiles
    for i in db:
        count = 0
        for j in i.keys():
            #print(f"j: {j} : {i[j]}")
            for k in list(match.keys()):
                #print(f"k: {k}: {match[k]}")
                if j == k and int(match[k]) == int(i[j]):
                    count += 1
        name = i['name']
        result[name] = count
    #pprint.pprint(f"result: {result}")
    for i in result.values():
        temp.append(i)
    max_temp = (max(temp))
    max_match = (max(match.values()))
    for i in match.values():
        if i == max_match:
            counter += 1
    for i in result.values():
        if i == max_temp:
            counter2 += 1
    #print(counter)
    #print(counter2)
    identification = max(result, key=result.get)
    if counter == 1 and counter2 == 1:
        print(f"{identification}")
    else:
        print("No match")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()

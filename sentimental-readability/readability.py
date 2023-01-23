def main():

    text = input("Text: ")
    index_calculation(count_letters(text), count_words(text), count_sentences(text))

# Function to count number of words


def count_words(text):
    count = len(text.split())
    print(f"Word count : {count}")
    return count

# Function to count number of letters


def count_letters(text):
    count = 0
    for i in text:
        if i.isalpha():
            count += 1
    print(f"letter count : {count}")
    return count

# Function to count number of sentences


def count_sentences(text):
    count = 0
    for i in text:
        if i == "." or i == "?" or i == "!":
            count += 1
    print(f"sentences count : {count}")
    return count

# Algo to calculate the Coleman-Liau index


def index_calculation(nb_letters, nb_words, nb_sentences):
    L = 0
    S = 0
    index = 0
    L = nb_letters / nb_words * 100
    S = nb_sentences / nb_words * 100
    # Coleman-Liau index calculation
    index = (0.0588 * L - 0.296 * S - 15.8)
    # Return the grade number
    if (index >= 16):
        print("Grade 16+")
    elif (index < 1):
        print("Before Grade 1")
    else:
        index = round(index)
        print(f"Grade {index}")
    return index


if __name__ == "__main__":
    main()

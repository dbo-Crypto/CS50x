# TODO

def main():
    # Test to check if the number is only non-negative numerical
    while True:
        try:
            number = int(input("Number: "))
            if number > 0:
                break
            else:
                pass
        except ValueError:
            print("That's not an integer!")
    t = card_type(number)
    if (luhn_algo(number) == True):
        print(t)
    else:
        print("INVALID")

# Algo to check to which provider belong the card number


def card_type(number):
    number = str(number)
    if (len(number) == 15 and (get2digit(number) == 34 or get2digit(number) == 37)):
        return "AMEX"
    elif (len(number) == 16 and (get2digit(number) >= 51 and get2digit(number) <= 55)):
        return "MASTERCARD"
    elif (len(number) == 13 or len(number) == 16 and number[0] == '4'):
        return "VISA"
    else:
        return "INVALID"

# Definition of function to get 2 first digit of string


def get2digit(number):
    res = int(str(number)[:2])
    return res

# Liuhn algo definition


def luhn_algo(number):
    number = str(number)
    res = 0
    sum = 0
    # Scan the card number first time
    for i in range(len(number)-2, -1, -2):
        res = int(number[int(i)]) * 2
        if res > 9:
            sliced = list(str(res))
            res = int(sliced[0]) + int(sliced[1])
            sum += res
        else:
            sum += res
    # Scan the card number second time
    for i in range(len(number)-1, -1, -2):
        sum += int(number[int(i)])
    # Check if last digit of checksum is 0
    if (sum % 10 == 0):
        print("true")
        return True
    else:
        return False


if __name__ == "__main__":
    main()

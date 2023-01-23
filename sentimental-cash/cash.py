# TODO
def main():

    while True:
        try:
            change = float(input("Change owed: "))
            change = int(change * 100)
            if change > 0:
                break
            else:
                pass
        except ValueError:
            print("Incorrect value")

    # Calculate the number of quarters to give the customer
    quarters = calculate_quarters(change)
    change = change - quarters * 25

    # Calculate the number of dimes to give the customer
    dimes = calculate_dimes(change)
    change = change - dimes * 10

    # Calculate the number of nickels to give the customer
    nickels = calculate_nickels(change)
    change = change - nickels * 5

    # Calculate the number of pennies to give the customer
    pennies = calculate_pennies(change)
    change = change - pennies * 1

    # Sum coins
    coins = quarters + dimes + nickels + pennies

    # Print total number of coins to give the customer
    print(coins)


def calculate_quarters(change):
    quarters = change // 25
    print(f"cents number: {quarters}")
    return quarters


def calculate_dimes(change):
    dimes = change // 10
    print(f"cents number: {dimes}")
    return dimes


def calculate_nickels(change):
    nickels = change // 5
    print(f"cents number: {nickels}")
    return nickels


def calculate_pennies(change):
    pennies = change
    print(f"cents number: {pennies}")
    return pennies


if __name__ == "__main__":
    main()
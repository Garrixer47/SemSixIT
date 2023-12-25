def is_prime(n, i=2):
    if n <= 2:
        return n == 2
    if n % i == 0:
        return False
    if i * i > n:
        return True
    return is_prime(n, i + 1)

def find_primes(limit, num=2):
    if num <= limit:
        if is_prime(num):
            print(num, end=" ")
        find_primes(limit, num + 1)

# Prompt the user to enter the limit
limit = int(input("Enter the limit: "))

print("Prime numbers up to", limit, ":")
find_primes(limit)

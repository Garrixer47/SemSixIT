#!/bin/bash
# Function to perform addition
addition() {
echo "Enter the first number: "
read num1
echo "Enter the second number: "
read num2
sum=$((num1 + num2))
echo "The sum of $num1 and $num2 is $sum."
}
# Function to perform subtraction
subtraction() {
echo "Enter the first number: "
read num1
echo "Enter the second number: "
read num2
diff=$((num1 - num2))
echo "The difference between $num1 and $num2 is $diff."
}
# Function to perform multiplication
multiplication() {
echo "Enter the first number: "
read num1
echo "Enter the second number: "
read num2
product=$((num1 * num2))
echo "The product of $num1 and $num2 is $product."
}
# Function to perform division
division() {
echo "Enter the numerator: "
read num1
echo "Enter the denominator: "
read num2
if [ $num2 -eq 0 ]
then
echo "Error: Division by zero."
elsequotient=$((num1 / num2))
echo "The quotient of $num1 and $num2 is $quotient."
fi
}
# Main program
echo "Calculator Menu:"
echo "1. Addition"
echo "2. Subtraction"
echo "3. Multiplication"
echo "4. Division"
echo "Enter your choice (1-4): "
read choice
case $choice in
1) addition ;;
2) subtraction ;;
3) multiplication ;;
4) division ;;
*) echo "Error: Invalid choice." ;;
esac

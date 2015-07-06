int number1 = 5;
int number2 = 8;
int sum = 0;

int add(int first, int second) {
  return first + second;
}

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // print the numbers
  Serial.print(number1);
  Serial.print(" + ");
  Serial.print(number2);
  Serial.print(" = ");

  // Call the functions
  // Notice that the NAMES don't have to match
  sum = add(number1, number2);
  Serial.println(sum);
  Serial.println("----------------");

  number1 = number1 + 1;
  number2 = number2 + 1;

  // Delay so the results don't scroll by too fast
  delay(2000);
}

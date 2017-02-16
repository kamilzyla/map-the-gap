#ifndef MESSAGE_H_
#define MESSAGE_H_

int nodes();
int id();

void putChar(int target, char value);
void putInt(int target, int value);
void putDouble(int target, double value);
void send(int target);

int receive(int source);
char getChar(int source);
int getInt(int source);
double getDouble(int source);

#endif  // MESSAGE_H_

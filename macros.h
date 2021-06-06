#ifndef MACROS_H_
#define MACROS_H_

/* [MISRA VIOLATION] RULE(19.7): We are using function-like macros just in bit manipulation functions because it is more readable */
#define set_bit(Data,Bit) ((Data)|= (1<<(Bit)))
#define clr_bit(Data,Bit) ((Data)&= ~(1<<(Bit)))
#define toggle_bit(Data,Bit) ((Data)^= (1<<(Bit)))
#define get_bit(Data,Bit) (((Data)>>(Bit))&1)
#define assign_bit(Data,Bit,Val) (((Val)==1)? (set_bit((Data),(Bit))):(clr_bit((Data),(Bit))))
#define is_bit_set(Data,Bit)  (((Data)&(1<<(Bit)))>>(Bit))
#define is_bit_clr(Data,Bit)  (!(((Data)&(1<<(Bit)))>>(Bit)))

#endif /* MACROS_H_ */

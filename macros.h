#ifndef MACROS_H_
#define MACROS_H_

/* [MISRA VIOLATION] RULE(19.7): We are using function-like macros just in bit manipulation functions because it is more readable */
#define set_bit(Data,Bit) ((Data) |= (u8)((u8)1 << ((u8)Bit)))
#define clr_bit(Data,Bit) ((Data) &= (u8)(~(u8)((u8)1 << ((u8)Bit))))
#define toggle_bit(Data,Bit) ((Data) ^= (u8)((u8)1<<((u8)Bit)))
#define get_bit(Data,Bit) ((((u8)Data) >> ((u8)Bit)) & (u8)1)
#define assign_bit(Data,Bit,Val) ((((u8)Val) == (u8)1)? (set_bit((Data),(Bit))) : (clr_bit((Data),(Bit))))
#define is_bit_set(Data,Bit)  ((((u8)Data) & ((u8)1 << ((u8)Bit))) >> ((u8)Bit))
#define is_bit_clr(Data,Bit)  ((u8)(~((((u8)Data) & (u8)(((u8)1 << ((u8)Bit))) >> ((u8)Bit)))))

#endif /* MACROS_H_ */

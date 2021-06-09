#ifndef MACROS_H_
#define MACROS_H_

/* [MISRA-VIOLATION] (19.7) Standard function-like Macros */
#define set_bit(Data,Bit) ((Data)|= (1<<(Bit)))
#define clr_bit(Data,Bit) ((Data)&= ~(1<<(Bit)))
#define toggle_bit(Data,Bit) ((Data)^= (1<<(Bit)))
#define get_bit(Data,Bit) (((Data)>>(Bit))&1)
#define assign_bit(Data,Bit,Val) (((Val)==1)? (set_bit((Data),(Bit))):(clr_bit((Data),(Bit))))
#define is_bit_set(Data,Bit)  ((((u8)(Data))&((u8)1<<((u8)(Bit))))>>((u8)(Bit)))
#define is_bit_clr(Data,Bit)  (!((((u8)(Data))&((u8)1<<((u8)(Bit))))>>((u8)(Bit))))



#endif /* MACROS_H_ */

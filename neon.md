This doc lists Arm64 NEON-128 intrinsics, and optional sample code link. 64-bit NEON intrisics are not included.<br>
Arm intrinsics reference: https://developer.arm.com/architectures/instruction-sets/intrinsics/<br>

Shell glob syntax is used to simplify intrinsics naming.<br>
Ex. NEON vector addition intrisic is named as below:<br>
`vaddq_{s,u}{8,16,32,64}` for signed(s) and unsigned(u) integer with 8,16,32,64 bits in size<br>
`vaddq_f{32,64}` for float32 and float64<br>

## Addition<br>
Add two vectors lane by lane vertically.<br>
`vaddq_{s,u}{8,16,32,64}`<br>
`vaddq_f{32,64}`<br>

## Widening addition<br>
- Add two vectors and widen the result, Ex. int8 + int8 -> int16.<br>
_SAMPLE:_ https://godbolt.org/z/YKqKWEvzz<br>
`vaddl_{s,u}{8,16,32}`<br>
`vaddl_high_{s,u}{8,16,32}`<br>
`vaddl_{s,u}{8,16,32}`<br>
`vaddl_high_{s,u}{8,16,32}`<br>

- Add vector to a wide vector, Ex. int16 + int8 -> int16.<br>
_SAMPLE:_ https://godbolt.org/z/bo5x49G9n<br>
`vaddw_{s,u}{8,16,32}`<br>
`vaddw_high_{s,u}{8,16,32}`<br>
`vaddw_{s,u}{8,16,32}`<br>
`vaddw_high_{s,u}{8,16,32}`<br>

## Halving addition<br>
Halving add two vectors, Ex. (int8 + int8) >> 1 -> int8.<br>
_NOTE:_ shift right by 1 bit is not divide by 2. Ex. (-1 >> 1) is -1, not 0.<br>
`vhaddq_{s,u}{8,16,32}`<br>

## Narrowing addition<br>
- Add two vectors, keep higher half bits, Ex. (int64 + int64) -> get high 32 bits<br>
_SAMPLE:_ https://godbolt.org/z/qv5qcvb9n<br>
`vaddhn_{s,u}{16,32,64}`<br>

- TODO<br>
`vaddhn_high_{s,u}{16,32,64}`<br>

## Saturating addition<br>
- Saturating add two vectors of same type, Ex., int32 + int32 -> int32<br>
`vqaddq_{s,u}{8,16,32,64}`<br>

- Saturating add unsigned to signed integer, Ex. int32 + uint32 -> int32<br>
`vuqaddq_s{8,16,32,64}`<br>

- Saturating add signed to unsigned integer, Ex. uint32 + int32 -> uint32<br>
`vsqaddq_u{8,16,32,64}`<br>

- Saturating add scalars<br>
`vqaddb_{s,u}8`<br>
`vqaddh_{s,u}16`<br>
`vqadds_{s,u}32`<br>
`vqaddd_{s,u}64`<br>
`vuqaddb_s8`<br>
`vuqaddh_s16`<br>
`vuqadds_s32`<br>
`vuqaddd_s64`<br>
`vsqaddb_u8`<br>
`vsqaddh_u16`<br>
`vsqadds_u32`<br>
`vsqaddd_u64`<br>

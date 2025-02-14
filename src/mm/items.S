#include <combo.h>

/* MM already have 16 bits indices into the GI table */
/* Make link's gi held item unsigned */
PATCH_LOAD_STORE 8, 1
.int 0x80126a7c
.int 0x80129070
.int 0x801290a4
.int 0x801290d0
.int 0x8012916c
.int 0x80129178
.int 0x8012918c
.int 0x80129198
.int 0x801291cc
.int 0x801291f8
.int 0x80129248
.int 0x8082ed10
.int 0x8082ed14
.int 0x8084708c
.int 0x80848264
.int 0x80852c8c
.int 0x80853ad4
.int 0x80853b50
.int 0x80853b54
.int 0x80853bb8
.int 0x80859764
.int 0x8085a82c
.int 0x8085a83c
.int 0x8085b914
PATCH_END

/* Make the drawID read from the table unsigned too */
PATCH_LOAD_STORE 8, 1
.int 0x80853b40
PATCH_END

/* Use our item-inventory handler */
PATCH_START 0x8084834c
  lw v0,0x24(sp)
  lw a0,0x20(sp)
  jal comboAddItem
   lh a1,0x384(v0)
PATCH_END

/* Fix magic jars */
PATCH_START 0x80114750
  li t7,0xfff
PATCH_END

/* Fix references to remains ShaderIDs */
PATCH_START 0x80852c8c
  li v0,0
PATCH_END

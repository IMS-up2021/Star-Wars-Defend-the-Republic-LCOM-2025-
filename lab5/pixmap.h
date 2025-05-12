#pragma once

#include <stddef.h>

// needs the typedef xpm_row_t
#include <lcom/lcf.h>
/** @defgroup xpm xpm
 * @{
 *  @author Joao Cardoso (jcard@fe.up.pt)
 */

/** Format of a xpm-like (there is a real xpm format) pic:
 * <pre>
 * static xpm_row_t const picture_name[] = {
 * "number_of_x_pixels number_of_y_pixels number_of_colors",
 * "one_char_symbol the_char_symbol_color",
 * ... exactly number_of_colors lines as above
 * "any of the above one_char_symbol, exactly number_of_x_pixels times",
 * ... exactly number_of_y_pixels lines as above
 * };
 *
 * Example:
 *
 * static xpm_row_t const pic1[] = {   // the name of the picture, "pic1" in this case
 * "32 13 4",                          // number of pixels in the x and y dimension,
 *                                        and the number of colors, which follows.
 * ". 0",                              // mapping between symbols and colors; in this
 *                                        case, the "." will be mapped to color 0
 * "x 2",                              // and the "x" to color 2
 * ...                                 // the next symbol/color pairs
 * "................................", // first row, exactly 32 pixels, 
 *                                        all color 0, BLACK
 * "..............xxx...............", // next row has three GREEN pixels
 *                                        at the center
 * </pre>
 * Any real xpm picture can be read, as long as there are only 16
 * colors on it, and the colors are the ones available by default.
 *
 *  To use other/more colors than the basic ones, the graphic card
 *  palette must be programmed.
 * 
 */


/* XPM */
static xpm_row_t const ana[] = {
    "37 29 15 1 ",
    "  c #000001",
    ". c #100800",
    "X c #080810",
    "o c #201008",
    "O c #401808",
    "+ c #502810",
    "@ c #783820",
    "# c #282840",
    "$ c #484068",
    "% c #B85838",
    "& c #C84820",
    "* c #F87830",
    "= c #F08840",
    "- c #F8A850",
    "; c #000000",
    /* pixels */
    ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;++;;;;;",
    ";;;;;;;;;;;;;;;;;;;;;;;;;;++;;OOO;;;;",
    ";;;;;;;;;;;;;;;;;;;;;; oo;O+;;+&&@+;;",
    ";;;;;;;;;;;;;;;;;;;; o+#o## OOO@***+;",
    ";;;;;;;;;;;;;;;;;;;Xo#$$$$#o OOO***&+",
    ";;;;;;;;;;;;;;;;;  #$$$$#o%@X+@O@***O",
    ";;;;;;;;;;;;;;; X#$$$$##o%%% +@OO&**+",
    ";;;;;;;;;;;;;; $$$###X  +%%%X@-%+O+&@",
    ";;;;;;;;;;;;   $##XX   X+@%@ ==-%=@OO",
    ";;;;;;;;;;;     o++oX X +@%oO== +%@OO",
    ";;;;;;;;;;;     +@@+ooo o@@o+==@+++OO",
    ";;;;;;;;;;;     .++@@@@oo@@ ++%+;;;;;",
    ";;;;;;;;;;;     o+@%@%%%+@@;;;;;;;;;;",
    ";;;;;;;;;;  o+o+@@@+++@%o+@;;;;;;;;;;",
    ";;;;;;;;;;  +@@@@+ooooo  +% ;;;;;;;;;",
    ";;;;;;;;;;  o@@ooooXXXXX#+% ;;;;;;;;;",
    ";;;;;;;;;;  .+o.ooo X####+o ;;;;;;;;;",
    ";;;;;;;;;;    .ooooXXX##XXXX;;;;;;;;;",
    ";;;;###;;;     .o   XX##XX+o;;;;;;;;;",
    ";X##$$$##X  oooo@+;XXX##X#XX;;;;;;;;;",
    " $$$$#$$$$##ooo@@+; XXX#X##+ ;;;;;;;;",
    " $$$$##$$$$$Xoo+@+;XXXX#X$$oX;;;;;;;;",
    ";X####X#$$$$# o@@o; X XX#$$#;;;;;;;;;",
    ";X###$XXX##$$Xo+@o X###$#XXo;;;;;;;;;",
    "; ###X ; XX#$#o+@  ###$$$#X;;;;;;;;;;",
    ";;X##X ;;  X#X@@o; X##$$$$##;;;;;;;;;",
    ";;     ;;;;   +X;; X###$$$##;;;;;;;;;",
    ";;;;;;;;;;;;;;;;;;    X####X;;;;;;;;;",
    ";;;;;;;;;;;;;;;;;;;;;;     ;;;;;;;;;;"
  };

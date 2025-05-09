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
"33 60 25 1 ",
"  c #000000",
". c #000001",
"X c #0B0500",
"o c #05050B",
"O c #190B05",
"+ c #361205",
"@ c #202036",
"# c #45200B",
"$ c #6D2E19",
"% c #3D365D",
"& c #205565",
"* c #3B6978",
"= c #C23D19",
"- c #B14D2E",
"; c #F76D27",
": c #EE7E36",
"> c #F79F45",
", c #207597",
"< c #6C8F9A",
"1 c #4586F7",
"2 c #3DC2E5",
"3 c #95DEF1",
"4 c #9EE0F2",
"5 c #616161",
"6 c #FFFFFF",
/* pixels */
"               &                 ",
"              ,2                 ",
"              2,                 ",
"             &2&                 ",
"             ,21                 ",
"             2,                  ",
"            &2&                  ",
"            ,2                   ",
"            3,                   ",
"        6  *4<                   ",
"           ,2                    ",
"           2, 6                  ",
"          &2&    ##              ",
"          ,2   ##==##            ",
"     6    2, ##=;;;;;###         ",
"         &2&#=;;;;;=++==#        ",
"       6 ,2  ++====+$===         ",
"         2,  ++++++->>O+         ",
"        &2&  ====#:$$-$          ",
"        22 +=;=+#-:5.#           ",
"        2,o.$=OO#$::>:           ",
"       &2&@%@O.$#+-:>-           ",
"   6   2,#@%%@$#-##-:$           ",
"     $&2,#o%%%#--:@O@#           ",
"  .O$-,2-oo%%%o-##$O@%.          ",
"6O#O--,2$O.@%%o--X$O%%.          ",
".@%@#&2&#OOo%%o$$O$@%%o          ",
".o%%oo,o.OOo@%@$O$$@%%##         ",
" .@@o%%  OOo@@@o#-O%%@$#         ",
" .oo@@o  .oo@@@.$$o%%@$-.OX#.    ",
"  .oo@o  .Oo@@@O$O@@@O$#O$$X-$   ",
"  ...o.  .O.@@@O#o@@oO#OOX$#$#   ",
"   .@o   ...@@@oo@@ooOOXXXXO.X.  ",
"   @@    ....ooooo@o.OOO.XX.OO.  ",
"   %%    ......%%o. .O.OOX.OO.   ",
"  o%o    ...o.o@%o.  .XOOOO.X    ",
"  o@     XO#@%%o@%@.  ......     ",
"        .O$@@%%@%%@.             ",
"        O$$$@%%@@%@-$$           ",
"        #----$%XX$$---$$         ",
"       .$-----OO##$$$--$$        ",
"       O$----O.OXOO$$$$--$       ",
"      .O$---$...XOOXO#$$--$      ",
"      .O----#    ..OOOO#$-$$     ",
"      .#---$        ..XO#-#$     ",
"      O$---$          ..Ooo@     ",
"    .o#$--#           .o@@%@     ",
"   .ooO$$$$           .o@@%@     ",
"   .oooo#O            .o@@%@     ",
"   oooooo.            .o@@%@     ",
"  .oooooo             .o@@%@     ",
"  .ooooo               .o@%@     ",
" ..oooo.               .o@%@     ",
" oooo..                .o@%@     ",
" o@@@o                 .o@%%@@   ",
".o%%%@                 .o@%%%%@  ",
".%%%%%.                .o@%%%%%@@",
".@@@@@.                .oo@@%%%%@",
".o@%%@.                .........o",
".ooo@..                          "
  };

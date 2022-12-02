#pragma once

//Regular text
#define BLK "\x1b[0;30m"
#define RED "\x1b[0;31m"
#define GRN "\x1b[0;32m"
#define YEL "\x1b[0;33m"
#define BLU "\x1b[0;34m"
#define MAG "\x1b[0;35m"
#define CYN "\x1b[0;36m"
#define WHT "\x1b[0;37m"

//Regular bold text
#define BBLK "\x1b[1;30m"
#define BRED "\x1b[1;31m"
#define BGRN "\x1b[1;32m"
#define BYEL "\x1b[1;33m"
#define BBLU "\x1b[1;34m"
#define BMAG "\x1b[1;35m"
#define BCYN "\x1b[1;36m"
#define BWHT "\x1b[1;37m"

//Regular underline text
#define UBLK "\x1b[4;30m"
#define URED "\x1b[4;31m"
#define UGRN "\x1b[4;32m"
#define UYEL "\x1b[4;33m"
#define UBLU "\x1b[4;34m"
#define UMAG "\x1b[4;35m"
#define UCYN "\x1b[4;36m"
#define UWHT "\x1b[4;37m"

//Regular background
#define BLKB "\x1b[40m"
#define REDB "\x1b[41m"
#define GRNB "\x1b[42m"
#define YELB "\x1b[43m"
#define BLUB "\x1b[44m"
#define MAGB "\x1b[45m"
#define CYNB "\x1b[46m"
#define WHTB "\x1b[47m"

//High intensty background 
#define BLKHB "\x1b[0;100m"
#define REDHB "\x1b[0;101m"
#define GRNHB "\x1b[0;102m"
#define YELHB "\x1b[0;103m"
#define BLUHB "\x1b[0;104m"
#define MAGHB "\x1b[0;105m"
#define CYNHB "\x1b[0;106m"
#define WHTHB "\x1b[0;107m"

//High intensty text
#define HBLK "\x1b[0;90m"
#define HRED "\x1b[0;91m"
#define HGRN "\x1b[0;92m"
#define HYEL "\x1b[0;93m"
#define HBLU "\x1b[0;94m"
#define HMAG "\x1b[0;95m"
#define HCYN "\x1b[0;96m"
#define HWHT "\x1b[0;97m"

//Bold high intensity text
#define BHBLK "\x1b[1;90m"
#define BHRED "\x1b[1;91m"
#define BHGRN "\x1b[1;92m"
#define BHYEL "\x1b[1;93m"
#define BHBLU "\x1b[1;94m"
#define BHMAG "\x1b[1;95m"
#define BHCYN "\x1b[1;96m"
#define BHWHT "\x1b[1;97m"

//Reset
#define reset "\x1b[0m"

void testColors()
{
printf( BLK   "BLK"   reset "\n" );
printf( BBLK  "BBLK"  reset "\n" );
printf( UBLK  "UBLK"  reset "\n" );
printf( BLKB  "BLKB"  reset "\n" );
printf( BLKHB "BLKHB" reset "\n" );
printf( HBLK  "HBLK"  reset "\n" );
printf( BHBLK "BHBLK" reset "\n" );
printf( RED   "RED"   reset "\n" );
printf( BRED  "BRED"  reset "\n" );
printf( URED  "URED"  reset "\n" );
printf( REDB  "REDB"  reset "\n" );
printf( REDHB "REDHB" reset "\n" );
printf( HRED  "HRED"  reset "\n" );
printf( BHRED "BHRED" reset "\n" );
printf( GRN   "GRN"   reset "\n" );
printf( BGRN  "BGRN"  reset "\n" );
printf( UGRN  "UGRN"  reset "\n" );
printf( GRNB  "GRNB"  reset "\n" );
printf( GRNHB "GRNHB" reset "\n" );
printf( HGRN  "HGRN"  reset "\n" );
printf( BHGRN "BHGRN" reset "\n" );
printf( YEL   "YEL"   reset "\n" );
printf( BYEL  "BYEL"  reset "\n" );
printf( UYEL  "UYEL"  reset "\n" );
printf( YELB  "YELB"  reset "\n" );
printf( YELHB "YELHB" reset "\n" );
printf( HYEL  "HYEL"  reset "\n" );
printf( BHYEL "BHYEL" reset "\n" );
printf( BLU   "BLU"   reset "\n" );
printf( BBLU  "BBLU"  reset "\n" );
printf( UBLU  "UBLU"  reset "\n" );
printf( BLUB  "BLUB"  reset "\n" );
printf( BLUHB "BLUHB" reset "\n" );
printf( HBLU  "HBLU"  reset "\n" );
printf( BHBLU "BHBLU" reset "\n" );
printf( MAG   "MAG"   reset "\n" );
printf( BMAG  "BMAG"  reset "\n" );
printf( UMAG  "UMAG"  reset "\n" );
printf( MAGB  "MAGB"  reset "\n" );
printf( MAGHB "MAGHB" reset "\n" );
printf( HMAG  "HMAG"  reset "\n" );
printf( BHMAG "BHMAG" reset "\n" );
printf( CYN   "CYN"   reset "\n" );
printf( BCYN  "BCYN"  reset "\n" );
printf( UCYN  "UCYN"  reset "\n" );
printf( CYNB  "CYNB"  reset "\n" );
printf( CYNHB "CYNHB" reset "\n" );
printf( HCYN  "HCYN"  reset "\n" );
printf( BHCYN "BHCYN" reset "\n" );
printf( WHT   "WHT"   reset "\n" );
printf( BWHT  "BWHT"  reset "\n" );
printf( UWHT  "UWHT"  reset "\n" );
printf( WHTB  "WHTB"  reset "\n" );
printf( WHTHB "WHTHB" reset "\n" );
printf( HWHT  "HWHT"  reset "\n" );
printf( BHWHT "BHWHT" reset "\n" );
}
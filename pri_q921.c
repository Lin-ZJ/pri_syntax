#include "pri_q921.h"

void syntax_q921(char *str)
{
    int octet2 = convert(str[2])*16+convert(str[3]);
    int octet3 = convert(str[5])*16+convert(str[6]);
    int octet4 = convert(str[8])*16+convert(str[9]);
    int octet5 = -1;
    printf("octet2 :0x%x  octet3 :0x%x  octet4 :0x%x", octet2, octet3, octet4);
    switch(octet4 & 0x3) {
        case 0:
        case 2:
            octet5 = convert(str[11])*16+convert(str[12]);
            printf("  octet5 :0x%x\nType : I format\n", octet5);
            break;
        case 1:
            octet5 = convert(str[11])*16+convert(str[12]);
            printf("  octet5 :0x%x\nType : S format\n", octet5);
            switch(octet4) {
                case 0x01:
                    printf("RR (receive ready)\n");
                    break;
                case 0x05:
                    printf("RNR (receive not ready)\n");
                    break;
                case 0x09:
                    printf("REJ (reject)\n");
                    break;
                default:
                    break;
            }
            break;
        case 3:
            printf("\nType : U format\n");
            switch(octet4) {
                case 0x7f:
                    printf("SABME (set asynchronous balanced mode extended)\n");
                    break;
                case 0x1f:
                    printf("DM (disconnected mode)\n");
                    break;
                case 0x13:
                    printf("UI (unnumbered information)\n");
                    break;
                case 0x53:
                    printf("DISC (disconnect)\n");
                    break;
                case 0x73:
                    printf("UA (unnumbered acknowledgement)\n");
                    break;
                case 0x97:
                    printf("FRMR (frame reject)\n");
                    break;
                case 0xbf:
                    printf("XID (Exchange Identification)\n");
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
    printf("\n");
}

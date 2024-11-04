#include "magic_bitboard.hpp"
#include <iostream>

MagicBitboard::MagicBitboard()
{
    rookMagicNumbers = {
        0xc80001828100040ULL,
        0x26004408400010ULL,
        0x1060040000202048ULL,
        0x110141100800888ULL,
        0x84420501a000802ULL,
        0x1803002905002224ULL,
        0x104380106000182ULL,
        0x208201001041ULL,
        0x4080118100002020ULL,
        0x1c40120100004020ULL,
        0x1009040000802020ULL,
        0x884002800841010ULL,
        0x2220068801201011ULL,
        0x1911442000004022ULL,
        0x4020802010011ULL,
        0x220004400102001ULL,
        0x4009608000842280ULL,
        0x4060104318400210ULL,
        0x811002400040020ULL,
        0x4801520000c41010ULL,
        0x4280020022204ULL,
        0x413000408404041ULL,
        0xc028800000101ULL,
        0x100400e904000201ULL,
        0x3800242000100a5ULL,
        0xc0008008210321ULL,
        0x2003002400001261ULL,
        0x410028894a041001ULL,
        0x800041040002901ULL,
        0x1002080204080eULL,
        0x22218040040401ULL,
        0x24084103280482ULL,
        0x20002020801040ULL,
        0x1020200020400812ULL,
        0x4082000000c0061ULL,
        0x4042024001200804ULL,
        0x5040040000024188ULL,
        0x100040008101a13ULL,
        0x408108018080802ULL,
        0x80408064000041ULL,
        0x850400821800120ULL,
        0x8100240008480bULL,
        0x6008080001100241ULL,
        0x1eb0100200110248ULL,
        0x30202216010004ULL,
        0x802021000c6142ULL,
        0x32200444020410aULL,
        0xa0202004580041ULL,
        0x80410000406180ULL,
        0x8220200002040a3ULL,
        0x93000200a002804ULL,
        0x40080080010010b2ULL,
        0x40080101012a1304ULL,
        0x4041000001012ULL,
        0x10001000e840482ULL,
        0xc04020200004885ULL,
        0x1080006110001041ULL,
        0x2081211102084250ULL,
        0x1020001500014619ULL,
        0x3810440a10000c23ULL,
        0x410484200860422ULL,
        0x180b0201090b2004ULL,
        0x1100040124410282ULL,
        0x1820a101000443ULL
    };

    bishopMagicNumbers = {
        0x1841160051a00401ULL,
        0x202000012224a02ULL,
        0x284003005412542ULL,
        0x2800a220c40502ULL,
        0x68005050040308ULL,
        0x440802c810020230ULL,
        0x240034002014417ULL,
        0x45202411310208aULL,
        0x1a08410602016172ULL,
        0x830464044100e08ULL,
        0x411a31a010040808ULL,
        0x200124000484405ULL,
        0x60020c80000120aULL,
        0x6a001002583420aULL,
        0x10082020084c0051ULL,
        0x1325202008030692ULL,
        0x2002026a00045020ULL,
        0x41051c000052122cULL,
        0x10200b000100803ULL,
        0x720204000610032ULL,
        0x6818603041604002ULL,
        0x1041040010020001ULL,
        0x301081420025204ULL,
        0x42024420826001ULL,
        0x404304000131801ULL,
        0x1041090c00842100ULL,
        0x144110020080240ULL,
        0x1211004002202008ULL,
        0x105080000500401ULL,
        0x2080600c62080131ULL,
        0x844100114022082ULL,
        0x841080020804b00ULL,
        0x8240800080210ULL,
        0x4002144012084210ULL,
        0x2052000060904ULL,
        0x88400420500c14ULL,
        0x434000204404ULL,
        0x1840240800212081ULL,
        0x4208c019244184ULL,
        0x54da10030841ULL,
        0x1200090011080a02ULL,
        0x800140c000414c8ULL,
        0x4400382000401058ULL,
        0x100020140000105ULL,
        0x610040040044421ULL,
        0x20001202848110aULL,
        0x222011010300101ULL,
        0x106608008012304ULL,
        0x220429002014a02ULL,
        0x110800a005104208ULL,
        0x806201048200111ULL,
        0x2082008a03000802ULL,
        0x2041008034011420ULL,
        0x401006005004434ULL,
        0x90a429004080204ULL,
        0x2041040950041802ULL,
        0x1002200028441145ULL,
        0x109004012802018aULL,
        0x65100405500801ULL,
        0x284240458180a00ULL,
        0x2002441020024020ULL,
        0x4a10110101144112ULL,
        0x1010a2c00005030ULL,
        0x40c012121020424ULL
    };

    rookBitsShift = {
        12, 11, 11, 11, 11, 11, 11, 12,
        11, 10, 10, 10, 10, 10, 10, 11,
        11, 10, 10, 10, 10, 10, 10, 11,
        11, 10, 10, 10, 10, 10, 10, 11,
        11, 10, 10, 10, 10, 10, 10, 11,
        11, 10, 10, 10, 10, 10, 10, 11,
        11, 10, 10, 10, 10, 10, 10, 11,
        12, 11, 11, 11, 11, 11, 11, 12
    };

    bishopBitsShift = {
        6, 5, 5, 5, 5, 5, 5, 6,
        5, 5, 5, 5, 5, 5, 5, 5,
        5, 5, 7, 7, 7, 7, 5, 5,
        5, 5, 7, 9, 9, 7, 5, 5,
        5, 5, 7, 9, 9, 7, 5, 5,
        5, 5, 7, 7, 7, 7, 5, 5,
        5, 5, 5, 5, 5, 5, 5, 5,
        6, 5, 5, 5, 5, 5, 5, 6
    };

    generateRookMasks();

    for (int square = 0; square < 64; square++)
    {
        //rookTable[square].ptr = ;
        rookTable[square].mask = rookMasks[square];
        rookTable[square].magic = rookMagicNumbers[square];
        rookTable[square].shift = 64 - rookBitsShift[square];
    }

        
}

std::array<uint64_t, 64>& MagicBitboard::getRookMagicNumbers()
{
    return rookMagicNumbers;
}

std::array<uint64_t, 64>& MagicBitboard::getBishopMagicNumbers()
{
    return bishopMagicNumbers;
}

std::array<Bitboard, 64>& MagicBitboard::generateRookMasks()
{
    rookMasks.fill(Bitboard());

    for (int square = 0; square < 64; square++)
    {
        int file = square % 8;
        int rank = square / 8;

        for (int f = file + 1; f < 7; f++)
        {
            rookMasks[square].setPiece((rank * 8) + f);
        }

        for (int f = file - 1; f > 0; f--)
        {
            rookMasks[square].setPiece((rank * 8) + f);
        }

        for (int r = rank + 1; r < 7; r++)
        {
            rookMasks[square].setPiece((r * 8) + file);
        }

        for (int r = rank - 1; r > 0; r--)
        {
            rookMasks[square].setPiece((r * 8) + file);
        }

        rookMasks[square].print();
    }

    return rookMasks;
}
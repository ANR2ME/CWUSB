/* Copyright (c) 2020 [Rick de Bondt] - HostFS.h
 *
 * This file contains the components needed to talk to the PSP.
 *
 **/

/*
 * PSPLINK
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPLINK root for details.
 *
 * usbhostfs.h - PSPLINK USB HostFS command header
 *
 * Copyright (c) 2006 James F
 *
 */

#pragma once

#include <stdint.h>

#ifdef __GNUC__
#define PACK(__Declaration__) __Declaration__ __attribute__((__packed__))
#endif

#ifdef _MSC_VER
#define PACK(__Declaration__) __pragma(pack(push, 1)) __Declaration__ __pragma(pack(pop))
#endif
#if defined(_MSC_VER) or defined(__MINGW32__)
#include <stdlib.h>
#define bswap_16(x) _byteswap_ushort(x)
#define bswap_32(x) _byteswap_ulong(x)
#define bswap_64(x) _byteswap_uint64(x)
#else
#include <byteswap.h>  // bswap_16 bswap_32 bswap_64
#endif

namespace HostFS_Constants
{
    constexpr unsigned int cHostFSPathMax{4096};
    constexpr unsigned int cHostFsMaxBlock{64 * 1024};
    constexpr unsigned int cHostFsRenameBufSize{1024};
    constexpr unsigned int cHostFsBulkMaxWrite{1024 * 1024};
    constexpr unsigned int cDevCtlGetInfo{0x02425818};
    constexpr unsigned int cAdhocRedirectorVersion{190};
    constexpr unsigned int cAsyncCommandDebug{1};
    constexpr unsigned int cAsyncCommandPacket{2};
    constexpr unsigned int cAsyncCommandSendPacket{77};
    constexpr unsigned int cAsyncCommandPrintData{66};

    enum eMagicType
    {
        HostFS       = 0x782F0812,  //< Tells the PSP or PC what data gets send/received (HostFS)
        Asynchronous = 0x782F0813,  //< Tells the PSP or PC what data gets send/received (Async)
        Bulk         = 0x782F0814,  //< Tells the PSP or PC what data gets send/received (Bulk)
        DebugPrint   = 0x909ACCEF   //< Tells the PSP or PC what data gets send/received (DebugPrint)
    };

    struct DevctlGetInfo
    {
        /* Total number of blocks */
        unsigned int btotal;
        /* Total number of free blocks */
        unsigned int bfree;
        /* Unknown */
        unsigned int unk;
        /* Sector size */
        unsigned int ssize;
        /* Number of sectors per block */
        unsigned int sects;
    };

    enum HostFsCommands
    {
        Hello = (0x8FFCU << 16U) | cAdhocRedirectorVersion,
    };

    enum AsyncCommands
    {
        Debug  = 1,
        Packet = 2
    };

    PACK(struct HostFsCommand {
        uint32_t magic;
        uint32_t command;
        uint32_t extralen;
    });

    PACK(struct HostFsHelloCmd { struct HostFsCommand cmd; });

    PACK(struct HostFsHelloResp { struct HostFsCommand cmd; });

    PACK(struct AsyncCommand {
        eMagicType magic;
        uint32_t   channel;
    });

    PACK(struct BulkCommand {
        eMagicType magic;
        uint32_t   channel;
        uint32_t   size;
    });

    PACK(struct AdHocRedirectorEvent {
        unsigned int magic;
        int          type;
        unsigned int value1;
        unsigned int value2;
    });

    PACK(struct ScreenHeader {
        unsigned int magic; /**< Magic number to tell the bridge program what to expect. */
        int          mode;  /* 0-3 */
        int          size;
        int          ref;
    });
}  // namespace HostFS_Constants

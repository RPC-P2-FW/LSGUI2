/*++ BUILD Version: 0001    // Increment this if a change has global effects

Copyright (c) Microsoft Corporation. All rights reserved.

Module Name:

    ntddstor.h

Abstract:

    This is the include file that defines all common constants and types
    accessing the storage class drivers

--*/

#include <winapifamily.h>

#pragma region Desktop Family
#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

//
// Interface GUIDs
//
// need these GUIDs outside conditional includes so that user can
//   #include <ntddstor.h> in precompiled header
//   #include <initguid.h> in a single source file
//   #include <ntddstor.h> in that source file a second time to instantiate the GUIDs
//
#ifdef DEFINE_GUID
//
// Make sure FAR is defined...
//
#ifndef FAR
#ifdef _WIN32
#define FAR
#else
#define FAR _far
#endif
#endif

// begin_wioctlguids

DEFINE_GUID(GUID_DEVINTERFACE_DISK,                   0x53f56307L, 0xb6bf, 0x11d0, 0x94, 0xf2, 0x00, 0xa0, 0xc9, 0x1e, 0xfb, 0x8b);
DEFINE_GUID(GUID_DEVINTERFACE_CDROM,                  0x53f56308L, 0xb6bf, 0x11d0, 0x94, 0xf2, 0x00, 0xa0, 0xc9, 0x1e, 0xfb, 0x8b);
DEFINE_GUID(GUID_DEVINTERFACE_PARTITION,              0x53f5630aL, 0xb6bf, 0x11d0, 0x94, 0xf2, 0x00, 0xa0, 0xc9, 0x1e, 0xfb, 0x8b);
DEFINE_GUID(GUID_DEVINTERFACE_TAPE,                   0x53f5630bL, 0xb6bf, 0x11d0, 0x94, 0xf2, 0x00, 0xa0, 0xc9, 0x1e, 0xfb, 0x8b);
DEFINE_GUID(GUID_DEVINTERFACE_WRITEONCEDISK,          0x53f5630cL, 0xb6bf, 0x11d0, 0x94, 0xf2, 0x00, 0xa0, 0xc9, 0x1e, 0xfb, 0x8b);
DEFINE_GUID(GUID_DEVINTERFACE_VOLUME,                 0x53f5630dL, 0xb6bf, 0x11d0, 0x94, 0xf2, 0x00, 0xa0, 0xc9, 0x1e, 0xfb, 0x8b);
DEFINE_GUID(GUID_DEVINTERFACE_MEDIUMCHANGER,          0x53f56310L, 0xb6bf, 0x11d0, 0x94, 0xf2, 0x00, 0xa0, 0xc9, 0x1e, 0xfb, 0x8b);
DEFINE_GUID(GUID_DEVINTERFACE_FLOPPY,                 0x53f56311L, 0xb6bf, 0x11d0, 0x94, 0xf2, 0x00, 0xa0, 0xc9, 0x1e, 0xfb, 0x8b);
DEFINE_GUID(GUID_DEVINTERFACE_CDCHANGER,              0x53f56312L, 0xb6bf, 0x11d0, 0x94, 0xf2, 0x00, 0xa0, 0xc9, 0x1e, 0xfb, 0x8b);
DEFINE_GUID(GUID_DEVINTERFACE_STORAGEPORT,            0x2accfe60L, 0xc130, 0x11d2, 0xb0, 0x82, 0x00, 0xa0, 0xc9, 0x1e, 0xfb, 0x8b);
DEFINE_GUID(GUID_DEVINTERFACE_VMLUN,                  0x6f416619L, 0x9f29, 0x42a5, 0xb2, 0x0b, 0x37, 0xe2, 0x19, 0xca, 0x02, 0xb0);
DEFINE_GUID(GUID_DEVINTERFACE_SES,                    0x1790c9ecL, 0x47d5, 0x4df3, 0xb5, 0xaf, 0x9a, 0xdf, 0x3c, 0xf2, 0x3e, 0x48);

#define  WDI_STORAGE_PREDICT_FAILURE_DPS_GUID        {0xe9f2d03aL, 0x747c, 0x41c2, {0xbb, 0x9a, 0x02, 0xc6, 0x2b, 0x6d, 0x5f, 0xcb}};

//
// Interfaces to discover devices that are
// not reported  through conventional APIs
//

DEFINE_GUID(GUID_DEVINTERFACE_HIDDEN_VOLUME,          0x7f108a28L, 0x9833, 0x4b3b, 0xb7, 0x80, 0x2c, 0x6b, 0x5f, 0xa5, 0xc0, 0x62);

// end_wioctlguids

// begin_wioctlobsoleteguids

#define DiskClassGuid               GUID_DEVINTERFACE_DISK
#define CdRomClassGuid              GUID_DEVINTERFACE_CDROM
#define PartitionClassGuid          GUID_DEVINTERFACE_PARTITION
#define TapeClassGuid               GUID_DEVINTERFACE_TAPE
#define WriteOnceDiskClassGuid      GUID_DEVINTERFACE_WRITEONCEDISK
#define VolumeClassGuid             GUID_DEVINTERFACE_VOLUME
#define MediumChangerClassGuid      GUID_DEVINTERFACE_MEDIUMCHANGER
#define FloppyClassGuid             GUID_DEVINTERFACE_FLOPPY
#define CdChangerClassGuid          GUID_DEVINTERFACE_CDCHANGER
#define StoragePortClassGuid        GUID_DEVINTERFACE_STORAGEPORT

#define HiddenVolumeClassGuid       GUID_DEVINTERFACE_HIDDEN_VOLUME

// end_wioctlobsoleteguids

// begin_tcioctlguids
//
// GUID, identifying crash dump section, containing device information or driver information. These GUIDs are used both to identify secondary dump section in the crashdump
// and in IOCTL to identify why section is requested by the user mode application
//

// /* d8e2592f-1aab-4d56-a746-1f7585df40f4 */
DEFINE_GUID(GUID_DEVICEDUMP_STORAGE_DEVICE,             0xd8e2592f,0x1aab,0x4d56,0xa7, 0x46, 0x1f, 0x75, 0x85, 0xdf, 0x40, 0xf4);

//  /* da82441d-7142-4bc1-b844-0807c5a4b67f */
DEFINE_GUID(GUID_DEVICEDUMP_DRIVER_STORAGE_PORT,        0xda82441d,0x7142,0x4bc1,0xb8, 0x44, 0x08, 0x07, 0xc5, 0xa4, 0xb6, 0x7f);

// end_tcioctlguids




#endif

//
// Interface DEVPROPKEY
//
// need these DEVPROPKEYs outside conditional includes so that user can
//   #include <ntddstor.h> in precompiled header
//   #include <devpropdef.h> in a single source file
//   #include <ntddstor.h> in that source file a second time to instantiate the DEVPROPKEYs
//
#ifdef DEFINE_DEVPROPKEY

// begin_wioctldevpropkeys
//
// Properties associated with the volume interface.
//

DEFINE_DEVPROPKEY(DEVPKEY_Storage_Portable,           0x4d1ebee8, 0x803, 0x4774, 0x98, 0x42, 0xb7, 0x7d, 0xb5, 0x2, 0x65, 0xe9, 2);    // DEVPROP_TYPE_BOOLEAN
DEFINE_DEVPROPKEY(DEVPKEY_Storage_Removable_Media,    0x4d1ebee8, 0x803, 0x4774, 0x98, 0x42, 0xb7, 0x7d, 0xb5, 0x2, 0x65, 0xe9, 3);    // DEVPROP_TYPE_BOOLEAN
DEFINE_DEVPROPKEY(DEVPKEY_Storage_System_Critical,    0x4d1ebee8, 0x803, 0x4774, 0x98, 0x42, 0xb7, 0x7d, 0xb5, 0x2, 0x65, 0xe9, 4);    // DEVPROP_TYPE_BOOLEAN
// end_wioctldevpropkeys

#endif

// begin_winioctl

#ifndef _NTDDSTOR_H_
#define _NTDDSTOR_H_

#ifdef __cplusplus
extern "C" {
#endif

//
// IoControlCode values for storage devices
//

#define IOCTL_STORAGE_BASE FILE_DEVICE_MASS_STORAGE

//
// The following device control codes are common for all class drivers.  They
// should be used in place of the older IOCTL_DISK, IOCTL_CDROM and IOCTL_TAPE
// common codes
//

#define IOCTL_STORAGE_CHECK_VERIFY            CTL_CODE(IOCTL_STORAGE_BASE, 0x0200, METHOD_BUFFERED, FILE_READ_ACCESS)
#define IOCTL_STORAGE_CHECK_VERIFY2           CTL_CODE(IOCTL_STORAGE_BASE, 0x0200, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_STORAGE_MEDIA_REMOVAL           CTL_CODE(IOCTL_STORAGE_BASE, 0x0201, METHOD_BUFFERED, FILE_READ_ACCESS)
#define IOCTL_STORAGE_EJECT_MEDIA             CTL_CODE(IOCTL_STORAGE_BASE, 0x0202, METHOD_BUFFERED, FILE_READ_ACCESS)
#define IOCTL_STORAGE_LOAD_MEDIA              CTL_CODE(IOCTL_STORAGE_BASE, 0x0203, METHOD_BUFFERED, FILE_READ_ACCESS)
#define IOCTL_STORAGE_LOAD_MEDIA2             CTL_CODE(IOCTL_STORAGE_BASE, 0x0203, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_STORAGE_RESERVE                 CTL_CODE(IOCTL_STORAGE_BASE, 0x0204, METHOD_BUFFERED, FILE_READ_ACCESS)
#define IOCTL_STORAGE_RELEASE                 CTL_CODE(IOCTL_STORAGE_BASE, 0x0205, METHOD_BUFFERED, FILE_READ_ACCESS)
#define IOCTL_STORAGE_FIND_NEW_DEVICES        CTL_CODE(IOCTL_STORAGE_BASE, 0x0206, METHOD_BUFFERED, FILE_READ_ACCESS)

#define IOCTL_STORAGE_EJECTION_CONTROL        CTL_CODE(IOCTL_STORAGE_BASE, 0x0250, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_STORAGE_MCN_CONTROL             CTL_CODE(IOCTL_STORAGE_BASE, 0x0251, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_STORAGE_GET_MEDIA_TYPES         CTL_CODE(IOCTL_STORAGE_BASE, 0x0300, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_STORAGE_GET_MEDIA_TYPES_EX      CTL_CODE(IOCTL_STORAGE_BASE, 0x0301, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_STORAGE_GET_MEDIA_SERIAL_NUMBER CTL_CODE(IOCTL_STORAGE_BASE, 0x0304, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_STORAGE_GET_HOTPLUG_INFO        CTL_CODE(IOCTL_STORAGE_BASE, 0x0305, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_STORAGE_SET_HOTPLUG_INFO        CTL_CODE(IOCTL_STORAGE_BASE, 0x0306, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)

#define IOCTL_STORAGE_RESET_BUS               CTL_CODE(IOCTL_STORAGE_BASE, 0x0400, METHOD_BUFFERED, FILE_READ_ACCESS)
#define IOCTL_STORAGE_RESET_DEVICE            CTL_CODE(IOCTL_STORAGE_BASE, 0x0401, METHOD_BUFFERED, FILE_READ_ACCESS)
#define IOCTL_STORAGE_BREAK_RESERVATION       CTL_CODE(IOCTL_STORAGE_BASE, 0x0405, METHOD_BUFFERED, FILE_READ_ACCESS)
#define IOCTL_STORAGE_PERSISTENT_RESERVE_IN   CTL_CODE(IOCTL_STORAGE_BASE, 0x0406, METHOD_BUFFERED, FILE_READ_ACCESS)
#define IOCTL_STORAGE_PERSISTENT_RESERVE_OUT  CTL_CODE(IOCTL_STORAGE_BASE, 0x0407, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)

#define IOCTL_STORAGE_GET_DEVICE_NUMBER       CTL_CODE(IOCTL_STORAGE_BASE, 0x0420, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_STORAGE_PREDICT_FAILURE         CTL_CODE(IOCTL_STORAGE_BASE, 0x0440, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_STORAGE_FAILURE_PREDICTION_CONFIG CTL_CODE(IOCTL_STORAGE_BASE, 0x0441, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_STORAGE_READ_CAPACITY           CTL_CODE(IOCTL_STORAGE_BASE, 0x0450, METHOD_BUFFERED, FILE_READ_ACCESS)

//
// IOCTLs 0x0463 to 0x0468 reserved for dependent disk support.
//


//
// IOCTLs 0x0470 to 0x047f reserved for device and stack telemetry interfaces
//

#define IOCTL_STORAGE_GET_DEVICE_TELEMETRY      CTL_CODE(IOCTL_STORAGE_BASE, 0x0470, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)
#define IOCTL_STORAGE_DEVICE_TELEMETRY_NOTIFY   CTL_CODE(IOCTL_STORAGE_BASE, 0x0471, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)
#define IOCTL_STORAGE_DEVICE_TELEMETRY_QUERY_CAPS CTL_CODE(IOCTL_STORAGE_BASE, 0x0472, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)
#define IOCTL_STORAGE_GET_DEVICE_TELEMETRY_RAW  CTL_CODE(IOCTL_STORAGE_BASE, 0x0473, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)


#define IOCTL_STORAGE_QUERY_PROPERTY                CTL_CODE(IOCTL_STORAGE_BASE, 0x0500, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_STORAGE_MANAGE_DATA_SET_ATTRIBUTES    CTL_CODE(IOCTL_STORAGE_BASE, 0x0501, METHOD_BUFFERED, FILE_WRITE_ACCESS)
#define IOCTL_STORAGE_GET_LB_PROVISIONING_MAP_RESOURCES  CTL_CODE(IOCTL_STORAGE_BASE, 0x0502, METHOD_BUFFERED, FILE_READ_ACCESS)

//
// IOCTLs 0x0503 to 0x0580 reserved for Enhanced Storage devices.
//


//
// IOCTLs for bandwidth contracts on storage devices
// (Move this to ntddsfio if we decide to use a new base)
//

#define IOCTL_STORAGE_GET_BC_PROPERTIES         CTL_CODE(IOCTL_STORAGE_BASE, 0x0600, METHOD_BUFFERED, FILE_READ_ACCESS)
#define IOCTL_STORAGE_ALLOCATE_BC_STREAM        CTL_CODE(IOCTL_STORAGE_BASE, 0x0601, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)
#define IOCTL_STORAGE_FREE_BC_STREAM            CTL_CODE(IOCTL_STORAGE_BASE, 0x0602, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)

//
// IOCTL to check for priority support
//
#define IOCTL_STORAGE_CHECK_PRIORITY_HINT_SUPPORT    CTL_CODE(IOCTL_STORAGE_BASE, 0x0620, METHOD_BUFFERED, FILE_ANY_ACCESS)

//
// IOCTL for data integrity check support
//

#define IOCTL_STORAGE_START_DATA_INTEGRITY_CHECK     CTL_CODE(IOCTL_STORAGE_BASE, 0x0621, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)
#define IOCTL_STORAGE_STOP_DATA_INTEGRITY_CHECK      CTL_CODE(IOCTL_STORAGE_BASE, 0x0622, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)

// begin_winioctl

//
// These ioctl codes are obsolete.  They are defined here to avoid resuing them
// and to allow class drivers to respond to them more easily.
//

#define OBSOLETE_IOCTL_STORAGE_RESET_BUS        CTL_CODE(IOCTL_STORAGE_BASE, 0x0400, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)
#define OBSOLETE_IOCTL_STORAGE_RESET_DEVICE     CTL_CODE(IOCTL_STORAGE_BASE, 0x0401, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)

//
// IOCTLs 0x0643 to 0x0655 reserved for VHD disk support.
//

//
// IOCTL to support Idle Power Management, including Device Wake
//
#define IOCTL_STORAGE_ENABLE_IDLE_POWER         CTL_CODE(IOCTL_STORAGE_BASE, 0x0720, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_STORAGE_GET_IDLE_POWERUP_REASON   CTL_CODE(IOCTL_STORAGE_BASE, 0x0721, METHOD_BUFFERED, FILE_ANY_ACCESS)

//
// IOCTLs to allow class drivers to acquire and release active references on
// a unit.  These should only be used if the class driver previously sent a
// successful IOCTL_STORAGE_ENABLE_IDLE_POWER request to the port driver.
//
#define IOCTL_STORAGE_POWER_ACTIVE  CTL_CODE(IOCTL_STORAGE_BASE, 0x0722, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_STORAGE_POWER_IDLE    CTL_CODE(IOCTL_STORAGE_BASE, 0x0723, METHOD_BUFFERED, FILE_ANY_ACCESS)

//
// This IOCTL indicates that the physical device has triggered some sort of event.
//
#define IOCTL_STORAGE_EVENT_NOTIFICATION CTL_CODE(IOCTL_STORAGE_BASE, 0x0724, METHOD_BUFFERED, FILE_ANY_ACCESS)


//
//
// IOCTL_STORAGE_GET_HOTPLUG_INFO
//

typedef struct _STORAGE_HOTPLUG_INFO {
    ULONG Size; // version
    BOOLEAN MediaRemovable; // ie. zip, jaz, cdrom, mo, etc. vs hdd
    BOOLEAN MediaHotplug;   // ie. does the device succeed a lock even though its not lockable media?
    BOOLEAN DeviceHotplug;  // ie. 1394, USB, etc.
    BOOLEAN WriteCacheEnableOverride; // This field should not be relied upon because it is no longer used
} STORAGE_HOTPLUG_INFO, *PSTORAGE_HOTPLUG_INFO;

//
// IOCTL_STORAGE_GET_DEVICE_NUMBER
//
// input - none
//
// output - STORAGE_DEVICE_NUMBER structure
//          The values in the STORAGE_DEVICE_NUMBER structure are guaranteed
//          to remain unchanged until the system is rebooted.  They are not
//          guaranteed to be persistant across boots.
//

typedef struct _STORAGE_DEVICE_NUMBER {

    //
    // The FILE_DEVICE_XXX type for this device.
    //

    DEVICE_TYPE DeviceType;

    //
    // The number of this device
    //

    ULONG       DeviceNumber;

    //
    // If the device is partitionable, the partition number of the device.
    // Otherwise -1
    //

    ULONG       PartitionNumber;
} STORAGE_DEVICE_NUMBER, *PSTORAGE_DEVICE_NUMBER;

//
// Define the structures for scsi resets
//

typedef struct _STORAGE_BUS_RESET_REQUEST {
    UCHAR PathId;
} STORAGE_BUS_RESET_REQUEST, *PSTORAGE_BUS_RESET_REQUEST;

//
// Break reservation is sent to the Adapter/FDO with the given lun information.
//

typedef struct STORAGE_BREAK_RESERVATION_REQUEST {
        ULONG Length;
        UCHAR _unused;
    UCHAR PathId;
    UCHAR TargetId;
    UCHAR Lun;
} STORAGE_BREAK_RESERVATION_REQUEST, *PSTORAGE_BREAK_RESERVATION_REQUEST;


//
// IOCTL_STORAGE_MEDIA_REMOVAL disables the mechanism
// on a storage device that ejects media. This function
// may or may not be supported on storage devices that
// support removable media.
//
// TRUE means prevent media from being removed.
// FALSE means allow media removal.
//

typedef struct _PREVENT_MEDIA_REMOVAL {
    BOOLEAN PreventMediaRemoval;
} PREVENT_MEDIA_REMOVAL, *PPREVENT_MEDIA_REMOVAL;



//
//  This is the format of TARGET_DEVICE_CUSTOM_NOTIFICATION.CustomDataBuffer
//  passed to applications by the classpnp autorun code (via IoReportTargetDeviceChangeAsynchronous).
//
typedef struct _CLASS_MEDIA_CHANGE_CONTEXT {
        ULONG MediaChangeCount;
        ULONG NewState;         // see MEDIA_CHANGE_DETECTION_STATE enum in classpnp.h in DDK
} CLASS_MEDIA_CHANGE_CONTEXT, *PCLASS_MEDIA_CHANGE_CONTEXT;


// begin_ntminitape


typedef struct _TAPE_STATISTICS {
    ULONG Version;
    ULONG Flags;
    LARGE_INTEGER RecoveredWrites;
    LARGE_INTEGER UnrecoveredWrites;
    LARGE_INTEGER RecoveredReads;
    LARGE_INTEGER UnrecoveredReads;
    UCHAR         CompressionRatioReads;
    UCHAR         CompressionRatioWrites;
} TAPE_STATISTICS, *PTAPE_STATISTICS;

#define RECOVERED_WRITES_VALID   0x00000001
#define UNRECOVERED_WRITES_VALID 0x00000002
#define RECOVERED_READS_VALID    0x00000004
#define UNRECOVERED_READS_VALID  0x00000008
#define WRITE_COMPRESSION_INFO_VALID  0x00000010
#define READ_COMPRESSION_INFO_VALID   0x00000020

typedef struct _TAPE_GET_STATISTICS {
    ULONG Operation;
} TAPE_GET_STATISTICS, *PTAPE_GET_STATISTICS;

#define TAPE_RETURN_STATISTICS 0L
#define TAPE_RETURN_ENV_INFO   1L
#define TAPE_RESET_STATISTICS  2L

//
// IOCTL_STORAGE_GET_MEDIA_TYPES_EX will return an array of DEVICE_MEDIA_INFO
// structures, one per supported type, embedded in the GET_MEDIA_TYPES struct.
//

typedef enum _STORAGE_MEDIA_TYPE {
    //
    // Following are defined in ntdddisk.h in the MEDIA_TYPE enum
    //
    // Unknown,                // Format is unknown
    // F5_1Pt2_512,            // 5.25", 1.2MB,  512 bytes/sector
    // F3_1Pt44_512,           // 3.5",  1.44MB, 512 bytes/sector
    // F3_2Pt88_512,           // 3.5",  2.88MB, 512 bytes/sector
    // F3_20Pt8_512,           // 3.5",  20.8MB, 512 bytes/sector
    // F3_720_512,             // 3.5",  720KB,  512 bytes/sector
    // F5_360_512,             // 5.25", 360KB,  512 bytes/sector
    // F5_320_512,             // 5.25", 320KB,  512 bytes/sector
    // F5_320_1024,            // 5.25", 320KB,  1024 bytes/sector
    // F5_180_512,             // 5.25", 180KB,  512 bytes/sector
    // F5_160_512,             // 5.25", 160KB,  512 bytes/sector
    // RemovableMedia,         // Removable media other than floppy
    // FixedMedia,             // Fixed hard disk media
    // F3_120M_512,            // 3.5", 120M Floppy
    // F3_640_512,             // 3.5" ,  640KB,  512 bytes/sector
    // F5_640_512,             // 5.25",  640KB,  512 bytes/sector
    // F5_720_512,             // 5.25",  720KB,  512 bytes/sector
    // F3_1Pt2_512,            // 3.5" ,  1.2Mb,  512 bytes/sector
    // F3_1Pt23_1024,          // 3.5" ,  1.23Mb, 1024 bytes/sector
    // F5_1Pt23_1024,          // 5.25",  1.23MB, 1024 bytes/sector
    // F3_128Mb_512,           // 3.5" MO 128Mb   512 bytes/sector
    // F3_230Mb_512,           // 3.5" MO 230Mb   512 bytes/sector
    // F8_256_128,             // 8",     256KB,  128 bytes/sector
    // F3_200Mb_512,           // 3.5",   200M Floppy (HiFD)
    //

    DDS_4mm = 0x20,            // Tape - DAT DDS1,2,... (all vendors)
    MiniQic,                   // Tape - miniQIC Tape
    Travan,                    // Tape - Travan TR-1,2,3,...
    QIC,                       // Tape - QIC
    MP_8mm,                    // Tape - 8mm Exabyte Metal Particle
    AME_8mm,                   // Tape - 8mm Exabyte Advanced Metal Evap
    AIT1_8mm,                  // Tape - 8mm Sony AIT
    DLT,                       // Tape - DLT Compact IIIxt, IV
    NCTP,                      // Tape - Philips NCTP
    IBM_3480,                  // Tape - IBM 3480
    IBM_3490E,                 // Tape - IBM 3490E
    IBM_Magstar_3590,          // Tape - IBM Magstar 3590
    IBM_Magstar_MP,            // Tape - IBM Magstar MP
    STK_DATA_D3,               // Tape - STK Data D3
    SONY_DTF,                  // Tape - Sony DTF
    DV_6mm,                    // Tape - 6mm Digital Video
    DMI,                       // Tape - Exabyte DMI and compatibles
    SONY_D2,                   // Tape - Sony D2S and D2L
    CLEANER_CARTRIDGE,         // Cleaner - All Drive types that support Drive Cleaners
    CD_ROM,                    // Opt_Disk - CD
    CD_R,                      // Opt_Disk - CD-Recordable (Write Once)
    CD_RW,                     // Opt_Disk - CD-Rewriteable
    DVD_ROM,                   // Opt_Disk - DVD-ROM
    DVD_R,                     // Opt_Disk - DVD-Recordable (Write Once)
    DVD_RW,                    // Opt_Disk - DVD-Rewriteable
    MO_3_RW,                   // Opt_Disk - 3.5" Rewriteable MO Disk
    MO_5_WO,                   // Opt_Disk - MO 5.25" Write Once
    MO_5_RW,                   // Opt_Disk - MO 5.25" Rewriteable (not LIMDOW)
    MO_5_LIMDOW,               // Opt_Disk - MO 5.25" Rewriteable (LIMDOW)
    PC_5_WO,                   // Opt_Disk - Phase Change 5.25" Write Once Optical
    PC_5_RW,                   // Opt_Disk - Phase Change 5.25" Rewriteable
    PD_5_RW,                   // Opt_Disk - PhaseChange Dual Rewriteable
    ABL_5_WO,                  // Opt_Disk - Ablative 5.25" Write Once Optical
    PINNACLE_APEX_5_RW,        // Opt_Disk - Pinnacle Apex 4.6GB Rewriteable Optical
    SONY_12_WO,                // Opt_Disk - Sony 12" Write Once
    PHILIPS_12_WO,             // Opt_Disk - Philips/LMS 12" Write Once
    HITACHI_12_WO,             // Opt_Disk - Hitachi 12" Write Once
    CYGNET_12_WO,              // Opt_Disk - Cygnet/ATG 12" Write Once
    KODAK_14_WO,               // Opt_Disk - Kodak 14" Write Once
    MO_NFR_525,                // Opt_Disk - Near Field Recording (Terastor)
    NIKON_12_RW,               // Opt_Disk - Nikon 12" Rewriteable
    IOMEGA_ZIP,                // Mag_Disk - Iomega Zip
    IOMEGA_JAZ,                // Mag_Disk - Iomega Jaz
    SYQUEST_EZ135,             // Mag_Disk - Syquest EZ135
    SYQUEST_EZFLYER,           // Mag_Disk - Syquest EzFlyer
    SYQUEST_SYJET,             // Mag_Disk - Syquest SyJet
    AVATAR_F2,                 // Mag_Disk - 2.5" Floppy
    MP2_8mm,                   // Tape - 8mm Hitachi
    DST_S,                     // Ampex DST Small Tapes
    DST_M,                     // Ampex DST Medium Tapes
    DST_L,                     // Ampex DST Large Tapes
    VXATape_1,                 // Ecrix 8mm Tape
    VXATape_2,                 // Ecrix 8mm Tape
#if (NTDDI_VERSION < NTDDI_WINXP)
    STK_EAGLE,                 // STK Eagle
#else
    STK_9840,                  // STK 9840
#endif
    LTO_Ultrium,               // IBM, HP, Seagate LTO Ultrium
    LTO_Accelis,               // IBM, HP, Seagate LTO Accelis
    DVD_RAM,                   // Opt_Disk - DVD-RAM
    AIT_8mm,                   // AIT2 or higher
    ADR_1,                     // OnStream ADR Mediatypes
    ADR_2,
    STK_9940,                  // STK 9940
    SAIT,                      // SAIT Tapes
    VXATape                    // VXA (Ecrix 8mm) Tape
}STORAGE_MEDIA_TYPE, *PSTORAGE_MEDIA_TYPE;

#define MEDIA_ERASEABLE         0x00000001
#define MEDIA_WRITE_ONCE        0x00000002
#define MEDIA_READ_ONLY         0x00000004
#define MEDIA_READ_WRITE        0x00000008

#define MEDIA_WRITE_PROTECTED   0x00000100
#define MEDIA_CURRENTLY_MOUNTED 0x80000000

//
// Define the different storage bus types
// Bus types below 128 (0x80) are reserved for Microsoft use
//

typedef enum _STORAGE_BUS_TYPE {
    BusTypeUnknown = 0x00,
    BusTypeScsi,
    BusTypeAtapi,
    BusTypeAta,
    BusType1394,
    BusTypeSsa,
    BusTypeFibre,
    BusTypeUsb,
    BusTypeRAID,
    BusTypeiScsi,
    BusTypeSas,
    BusTypeSata,
    BusTypeSd,
    BusTypeMmc,
    BusTypeVirtual,
    BusTypeFileBackedVirtual,
    BusTypeSpaces,
    BusTypeNvme,
    BusTypeMax,
    BusTypeMaxReserved = 0x7F
} STORAGE_BUS_TYPE, *PSTORAGE_BUS_TYPE;

//
// Macro to identify which bus types
// support shared storage
//

#define SupportsDeviceSharing( BusType ) ( \
        (BusType == BusTypeScsi)  ||       \
        (BusType == BusTypeFibre) ||       \
        (BusType == BusTypeiScsi) ||       \
        (BusType == BusTypeSas)   ||       \
        (BusType == BusTypeSpaces) )

typedef struct _DEVICE_MEDIA_INFO {
    union {
        struct {
            LARGE_INTEGER Cylinders;
            STORAGE_MEDIA_TYPE MediaType;
            ULONG TracksPerCylinder;
            ULONG SectorsPerTrack;
            ULONG BytesPerSector;
            ULONG NumberMediaSides;
            ULONG MediaCharacteristics; // Bitmask of MEDIA_XXX values.
        } DiskInfo;

        struct {
            LARGE_INTEGER Cylinders;
            STORAGE_MEDIA_TYPE MediaType;
            ULONG TracksPerCylinder;
            ULONG SectorsPerTrack;
            ULONG BytesPerSector;
            ULONG NumberMediaSides;
            ULONG MediaCharacteristics; // Bitmask of MEDIA_XXX values.
        } RemovableDiskInfo;

        struct {
            STORAGE_MEDIA_TYPE MediaType;
            ULONG   MediaCharacteristics; // Bitmask of MEDIA_XXX values.
            ULONG   CurrentBlockSize;
            STORAGE_BUS_TYPE BusType;

            //
            // Bus specific information describing the medium supported.
            //

            union {
                struct {
                    UCHAR MediumType;
                    UCHAR DensityCode;
                } ScsiInformation;
            } BusSpecificData;

        } TapeInfo;
    } DeviceSpecific;
} DEVICE_MEDIA_INFO, *PDEVICE_MEDIA_INFO;

typedef struct _GET_MEDIA_TYPES {
    ULONG DeviceType;              // FILE_DEVICE_XXX values
    ULONG MediaInfoCount;
    DEVICE_MEDIA_INFO MediaInfo[1];
} GET_MEDIA_TYPES, *PGET_MEDIA_TYPES;


//
// IOCTL_STORAGE_PREDICT_FAILURE
//
// input - none
//
// output - STORAGE_PREDICT_FAILURE structure
//          PredictFailure returns zero if no failure predicted and non zero
//                         if a failure is predicted.
//
//          VendorSpecific returns 512 bytes of vendor specific information
//                         if a failure is predicted
//
typedef struct _STORAGE_PREDICT_FAILURE
{
    ULONG PredictFailure;
    UCHAR VendorSpecific[512];
} STORAGE_PREDICT_FAILURE, *PSTORAGE_PREDICT_FAILURE;


//
// IOCTL_STORAGE_FAILURE_PREDICTION_CONFIG
//
// Input - STORAGE_FAILURE_PREDICTION_CONFIG structure.
//         If the sender wants to enable or disable failure prediction then
//         the sender should set the "Set" field to TRUE.
// Output - STORAGE_FAILURE_PREDICTION_CONFIG structure.
//          If successful, the "Enabled" field will indicate if failure
//          prediction is currently enabled or not.
//
typedef struct _STORAGE_FAILURE_PREDICTION_CONFIG {
    ULONG Version;      // Set to 1 for Blue.
    ULONG Size;
    BOOLEAN Set;        // TRUE if the sender wants to enable/disable failure prediction.
    BOOLEAN Enabled;    
    USHORT Reserved;
} STORAGE_FAILURE_PREDICTION_CONFIG, *PSTORAGE_FAILURE_PREDICTION_CONFIG;

#define STORAGE_FAILURE_PREDICTION_CONFIG_V1 1

// end_ntminitape

//
// Property Query Structures
//

//
// IOCTL_STORAGE_QUERY_PROPERTY
//
// Input Buffer:
//      a STORAGE_PROPERTY_QUERY structure which describes what type of query
//      is being done, what property is being queried for, and any additional
//      parameters which a particular property query requires.
//
//  Output Buffer:
//      Contains a buffer to place the results of the query into.  Since all
//      property descriptors can be cast into a STORAGE_DESCRIPTOR_HEADER,
//      the IOCTL can be called once with a small buffer then again using
//      a buffer as large as the header reports is necessary.
//


//
// Types of queries
//

typedef enum _STORAGE_QUERY_TYPE {
    PropertyStandardQuery = 0,          // Retrieves the descriptor
    PropertyExistsQuery,                // Used to test whether the descriptor is supported
    PropertyMaskQuery,                  // Used to retrieve a mask of writeable fields in the descriptor
    PropertyQueryMaxDefined     // use to validate the value
} STORAGE_QUERY_TYPE, *PSTORAGE_QUERY_TYPE;

//
// define some initial property id's
//

typedef enum _STORAGE_PROPERTY_ID {
    StorageDeviceProperty = 0,
    StorageAdapterProperty,
    StorageDeviceIdProperty,
    StorageDeviceUniqueIdProperty,              // See storduid.h for details
    StorageDeviceWriteCacheProperty,
    StorageMiniportProperty,
    StorageAccessAlignmentProperty,
    StorageDeviceSeekPenaltyProperty,
    StorageDeviceTrimProperty,
    StorageDeviceWriteAggregationProperty,
    StorageDeviceDeviceTelemetryProperty,
    StorageDeviceLBProvisioningProperty,
    StorageDevicePowerProperty,
    StorageDeviceCopyOffloadProperty,
    StorageDeviceResiliencyProperty,
    StorageDeviceMediumProductType,
// end_winioctl
    StorageDeviceTieringProperty
// begin_winioctl
} STORAGE_PROPERTY_ID, *PSTORAGE_PROPERTY_ID;

//
// Query structure - additional parameters for specific queries can follow
// the header
//

typedef struct _STORAGE_PROPERTY_QUERY {

    //
    // ID of the property being retrieved
    //

    STORAGE_PROPERTY_ID PropertyId;

    //
    // Flags indicating the type of query being performed
    //

    STORAGE_QUERY_TYPE QueryType;

    //
    // Space for additional parameters if necessary
    //

    UCHAR AdditionalParameters[1];

} STORAGE_PROPERTY_QUERY, *PSTORAGE_PROPERTY_QUERY;

//
// Standard property descriptor header.  All property pages should use this
// as their first element or should contain these two elements
//

typedef _Struct_size_bytes_(Size) struct _STORAGE_DESCRIPTOR_HEADER {

    ULONG Version;

    ULONG Size;

} STORAGE_DESCRIPTOR_HEADER, *PSTORAGE_DESCRIPTOR_HEADER;

//
// Device property descriptor - this is really just a rehash of the inquiry
// data retrieved from a scsi device
//
// This may only be retrieved from a target device.  Sending this to the bus
// will result in an error
//

typedef _Struct_size_bytes_(Size) struct _STORAGE_DEVICE_DESCRIPTOR {

    //
    // Sizeof(STORAGE_DEVICE_DESCRIPTOR)
    //

    ULONG Version;

    //
    // Total size of the descriptor, including the space for additional
    // data and id strings
    //

    ULONG Size;

    //
    // The SCSI-2 device type
    //

    UCHAR DeviceType;

    //
    // The SCSI-2 device type modifier (if any) - this may be zero
    //

    UCHAR DeviceTypeModifier;

    //
    // Flag indicating whether the device's media (if any) is removable.  This
    // field should be ignored for media-less devices
    //

    BOOLEAN RemovableMedia;

    //
    // Flag indicating whether the device can support mulitple outstanding
    // commands.  The actual synchronization in this case is the responsibility
    // of the port driver.
    //

    BOOLEAN CommandQueueing;

    //
    // Byte offset to the zero-terminated ascii string containing the device's
    // vendor id string.  For devices with no such ID this will be zero
    //

    ULONG VendorIdOffset;

    //
    // Byte offset to the zero-terminated ascii string containing the device's
    // product id string.  For devices with no such ID this will be zero
    //

    ULONG ProductIdOffset;

    //
    // Byte offset to the zero-terminated ascii string containing the device's
    // product revision string.  For devices with no such string this will be
    // zero
    //

    ULONG ProductRevisionOffset;

    //
    // Byte offset to the zero-terminated ascii string containing the device's
    // serial number.  For devices with no serial number this will be zero
    //

    ULONG SerialNumberOffset;

    //
    // Contains the bus type (as defined above) of the device.  It should be
    // used to interpret the raw device properties at the end of this structure
    // (if any)
    //

    STORAGE_BUS_TYPE BusType;

    //
    // The number of bytes of bus-specific data which have been appended to
    // this descriptor
    //

    ULONG RawPropertiesLength;

    //
    // Place holder for the first byte of the bus specific property data
    //

    UCHAR RawDeviceProperties[1];

} STORAGE_DEVICE_DESCRIPTOR, *PSTORAGE_DEVICE_DESCRIPTOR;


//
// Adapter properties
//
// This descriptor can be retrieved from a target device object of from the
// device object for the bus.  Retrieving from the target device object will
// forward the request to the underlying bus
//

typedef _Struct_size_bytes_(Size) struct _STORAGE_ADAPTER_DESCRIPTOR {

    ULONG Version;

    ULONG Size;

    ULONG MaximumTransferLength;

    ULONG MaximumPhysicalPages;

    ULONG AlignmentMask;

    BOOLEAN AdapterUsesPio;

    BOOLEAN AdapterScansDown;

    BOOLEAN CommandQueueing;

    BOOLEAN AcceleratedTransfer;

#if (NTDDI_VERSION < NTDDI_WINXP)
    BOOLEAN BusType;
#else
    UCHAR BusType;
#endif

    USHORT BusMajorVersion;

    USHORT BusMinorVersion;

#if (NTDDI_VERSION >= NTDDI_WIN8)
    UCHAR SrbType;

    UCHAR AddressType;
#endif

} STORAGE_ADAPTER_DESCRIPTOR, *PSTORAGE_ADAPTER_DESCRIPTOR;


#if (NTDDI_VERSION >= NTDDI_WIN8)

#define NO_SRBTYPE_ADAPTER_DESCRIPTOR_SIZE  \
    FIELD_OFFSET(STORAGE_ADAPTER_DESCRIPTOR, SrbType)

#if !defined(SRB_TYPE_SCSI_REQUEST_BLOCK)
#define SRB_TYPE_SCSI_REQUEST_BLOCK         0
#endif

#if !defined(SRB_TYPE_STORAGE_REQUEST_BLOCK)
#define SRB_TYPE_STORAGE_REQUEST_BLOCK      1
#endif

#if !defined(STORAGE_ADDRESS_TYPE_BTL8)
#define STORAGE_ADDRESS_TYPE_BTL8                   0
#endif

#endif // (NTDDI_VERSION >= NTDDI_WIN8)

typedef _Struct_size_bytes_(Size) struct _STORAGE_ACCESS_ALIGNMENT_DESCRIPTOR {

    //
    // Sizeof(STORAGE_ACCESS_ALIGNMENT_DESCRIPTOR)
    //

    ULONG Version;

    //
    // Total size of the descriptor, including the space for additional
    // data and id strings
    //

    ULONG Size;

    //
    // The number of bytes in a cache line of the device
    //

    ULONG BytesPerCacheLine;

    //
    // The address offset neccessary for proper cache access alignment in bytes
    //

    ULONG BytesOffsetForCacheAlignment;

    //
    // The number of bytes in a physical sector of the device
    //

    ULONG BytesPerLogicalSector;

    //
    // The number of bytes in an addressable logical sector (LBA)of the device
    //

    ULONG BytesPerPhysicalSector;

    //
    // The address offset neccessary for proper sector access alignment in bytes
    //

    ULONG BytesOffsetForSectorAlignment;

} STORAGE_ACCESS_ALIGNMENT_DESCRIPTOR, *PSTORAGE_ACCESS_ALIGNMENT_DESCRIPTOR;

typedef _Struct_size_bytes_(Size) struct _STORAGE_MEDIUM_PRODUCT_TYPE_DESCRIPTOR {

    //
    // Sizeof(STORAGE_MEDIUM_PRODUCT_TYPE_DESCRIPTOR)
    //

    ULONG Version;

    //
    // Total size of the descriptor, including the space for additional data
    //

    ULONG Size;

    //
    // Product type of the supporting storage medium
    //

    ULONG MediumProductType;

} STORAGE_MEDIUM_PRODUCT_TYPE_DESCRIPTOR, *PSTORAGE_MEDIUM_PRODUCT_TYPE_DESCRIPTOR;


typedef enum _STORAGE_PORT_CODE_SET {
    StoragePortCodeSetReserved  = 0,
    StoragePortCodeSetStorport  = 1,
    StoragePortCodeSetSCSIport  = 2,
    StoragePortCodeSetSpaceport = 3,
    StoragePortCodeSetATAport   = 4,
    StoragePortCodeSetUSBport   = 5,
    StoragePortCodeSetSBP2port  = 6,
    StoragePortCodeSetSDport    = 7
} STORAGE_PORT_CODE_SET, *PSTORAGE_PORT_CODE_SET;

#if (NTDDI_VERSION >= NTDDI_WIN8)
#define STORAGE_MINIPORT_DESCRIPTOR_V1_SIZE     RTL_SIZEOF_THROUGH_FIELD(STORAGE_MINIPORT_DESCRIPTOR, IoTimeoutValue)
#endif

typedef struct _STORAGE_MINIPORT_DESCRIPTOR {

    ULONG Version;

    ULONG Size;

    STORAGE_PORT_CODE_SET Portdriver;

    BOOLEAN LUNResetSupported;

    BOOLEAN TargetResetSupported;

#if (NTDDI_VERSION >= NTDDI_WIN8)
    USHORT  IoTimeoutValue;
#endif
 
#if (NTDDI_VERSION >= NTDDI_WINBLUE)
    BOOLEAN ExtraIoInfoSupported;
    UCHAR   Reserved0[3];
    ULONG   Reserved1;
#endif

} STORAGE_MINIPORT_DESCRIPTOR, *PSTORAGE_MINIPORT_DESCRIPTOR;

//
// Storage identification descriptor.
// The definitions here are based on the SCSI/SBP vital product data
// device identifier page.
//

typedef enum _STORAGE_IDENTIFIER_CODE_SET {
    StorageIdCodeSetReserved = 0,
    StorageIdCodeSetBinary = 1,
    StorageIdCodeSetAscii = 2,
    StorageIdCodeSetUtf8 = 3
} STORAGE_IDENTIFIER_CODE_SET, *PSTORAGE_IDENTIFIER_CODE_SET;

typedef enum _STORAGE_IDENTIFIER_TYPE {
    StorageIdTypeVendorSpecific = 0,
    StorageIdTypeVendorId = 1,
    StorageIdTypeEUI64 = 2,
    StorageIdTypeFCPHName = 3,
    StorageIdTypePortRelative = 4,
    StorageIdTypeTargetPortGroup = 5,
    StorageIdTypeLogicalUnitGroup = 6,
    StorageIdTypeMD5LogicalUnitIdentifier = 7,
    StorageIdTypeScsiNameString = 8
} STORAGE_IDENTIFIER_TYPE, *PSTORAGE_IDENTIFIER_TYPE;

// Mislabeled above but need to keep it for backwards compatibility
#define StorageIdTypeNAA StorageIdTypeFCPHName

// NAA formats (Used with StorageIdTypeNAA)
typedef enum _STORAGE_ID_NAA_FORMAT {
        StorageIdNAAFormatIEEEExtended = 2,
        StorageIdNAAFormatIEEERegistered = 3,
        StorageIdNAAFormatIEEEERegisteredExtended = 5
} STORAGE_ID_NAA_FORMAT, *PSTORAGE_ID_NAA_FORMAT;

typedef enum _STORAGE_ASSOCIATION_TYPE {
    StorageIdAssocDevice = 0,
    StorageIdAssocPort = 1,
    StorageIdAssocTarget = 2
} STORAGE_ASSOCIATION_TYPE, *PSTORAGE_ASSOCIATION_TYPE;

typedef struct _STORAGE_IDENTIFIER {
    STORAGE_IDENTIFIER_CODE_SET CodeSet;
    STORAGE_IDENTIFIER_TYPE Type;
    USHORT IdentifierSize;
    USHORT NextOffset;

    //
    // Add new fields here since existing code depends on
    // the above layout not changing.
    //

    STORAGE_ASSOCIATION_TYPE Association;

    //
    // The identifier is a variable length array of bytes.
    //

    UCHAR Identifier[1];
} STORAGE_IDENTIFIER, *PSTORAGE_IDENTIFIER;

typedef _Struct_size_bytes_(Size) struct _STORAGE_DEVICE_ID_DESCRIPTOR {

    ULONG Version;

    ULONG Size;

    //
    // The number of identifiers reported by the device.
    //

    ULONG NumberOfIdentifiers;

    //
    // The following field is actually a variable length array of identification
    // descriptors.  Unfortunately there's no C notation for an array of
    // variable length structures so we're forced to just pretend.
    //

    UCHAR Identifiers[1];
} STORAGE_DEVICE_ID_DESCRIPTOR, *PSTORAGE_DEVICE_ID_DESCRIPTOR;

// output buffer for   StorageDeviceSeekPenaltyProperty & PropertyStandardQuery
typedef struct _DEVICE_SEEK_PENALTY_DESCRIPTOR {
    ULONG       Version;          // keep compatible with STORAGE_DESCRIPTOR_HEADER
    ULONG       Size;             // keep compatible with STORAGE_DESCRIPTOR_HEADER

    BOOLEAN     IncursSeekPenalty;
} DEVICE_SEEK_PENALTY_DESCRIPTOR, *PDEVICE_SEEK_PENALTY_DESCRIPTOR;

// output buffer for   StorageDeviceWriteAggregationProperty & PropertyStandardQuery
typedef struct _DEVICE_WRITE_AGGREGATION_DESCRIPTOR {
    ULONG       Version;          // keep compatible with STORAGE_DESCRIPTOR_HEADER
    ULONG       Size;             // keep compatible with STORAGE_DESCRIPTOR_HEADER

    BOOLEAN     BenefitsFromWriteAggregation;
} DEVICE_WRITE_AGGREGATION_DESCRIPTOR, *PDEVICE_WRITE_AGGREGATION_DESCRIPTOR;

// output buffer for   StorageDeviceTrimProperty & PropertyStandardQuery
typedef struct _DEVICE_TRIM_DESCRIPTOR {
    ULONG       Version;          // keep compatible with STORAGE_DESCRIPTOR_HEADER
    ULONG       Size;             // keep compatible with STORAGE_DESCRIPTOR_HEADER

    BOOLEAN     TrimEnabled;
} DEVICE_TRIM_DESCRIPTOR, *PDEVICE_TRIM_DESCRIPTOR;

#pragma warning(push)
#pragma warning(disable:4214) // bit fields other than int
//
// Output buffer for StorageDeviceLBProvisioningProperty & PropertyStandardQuery
//
typedef struct _DEVICE_LB_PROVISIONING_DESCRIPTOR {
    ULONG       Version;          // keep compatible with STORAGE_DESCRIPTOR_HEADER
    ULONG       Size;             // keep compatible with STORAGE_DESCRIPTOR_HEADER

    UCHAR ThinProvisioningEnabled : 1;
    UCHAR ThinProvisioningReadZeros : 1;
    UCHAR AnchorSupported : 3;
    UCHAR UnmapGranularityAlignmentValid : 1;
    UCHAR Reserved0 : 2;
    UCHAR Reserved1[7];
    ULONGLONG OptimalUnmapGranularity;      // Granularity in bytes.
    ULONGLONG UnmapGranularityAlignment;    // Granularity alignment in bytes.
#if (NTDDI_VERSION >= NTDDI_WINBLUE)
    ULONG MaxUnmapLbaCount;                 // Max LBAs that can be unmapped in a single UNMAP command, in logical blocks.
    ULONG MaxUnmapBlockDescriptorCount;     // Max number of descriptors allowed in a single UNMAP command.
#endif
} DEVICE_LB_PROVISIONING_DESCRIPTOR, *PDEVICE_LB_PROVISIONING_DESCRIPTOR;

#define DEVICE_LB_PROVISIONING_DESCRIPTOR_V1_SIZE     RTL_SIZEOF_THROUGH_FIELD(DEVICE_LB_PROVISIONING_DESCRIPTOR, UnmapGranularityAlignment)

//
// IOCTL_STORAGE_GET_LB_PROVISIONING_MAP_RESOURCES
//
// Input Buffer:
//      None
//
// Output Buffer:
//      Structure of type STORAGE_LB_PROVISIONING_MAP_RESOURCES
//

typedef struct _STORAGE_LB_PROVISIONING_MAP_RESOURCES {
    ULONG       Size;
    ULONG       Version;
    UCHAR       AvailableMappingResourcesValid : 1;
    UCHAR       UsedMappingResourcesValid : 1;
    UCHAR       Reserved0 : 6;
    UCHAR       Reserved1[3];
    UCHAR       AvailableMappingResourcesScope : 2; // See LOG_PAGE_LBP_RESOURCE_SCOPE_* definitions in scsi.h for scope values.
    UCHAR       UsedMappingResourcesScope : 2;
    UCHAR       Reserved2 : 4;
    UCHAR       Reserved3[3];
    ULONGLONG   AvailableMappingResources;  // Available LBA mapping resources, in bytes.
    ULONGLONG   UsedMappingResources;       // Used LBA mapping resources, in bytes.
} STORAGE_LB_PROVISIONING_MAP_RESOURCES, *PSTORAGE_LB_PROVISIONING_MAP_RESOURCES;

#pragma warning(pop)

// output buffer for   StorageDevicePowerProperty & PropertyStandardQuery
typedef struct _DEVICE_POWER_DESCRIPTOR {
    ULONG       Version;          // keep compatible with STORAGE_DESCRIPTOR_HEADER
    ULONG       Size;             // keep compatible with STORAGE_DESCRIPTOR_HEADER

    BOOLEAN     DeviceAttentionSupported;   // The device supports "device attention".
    BOOLEAN     AsynchronousNotificationSupported;  // The device supports asynchronous notifications, delivered via IOCTL_STORAGE_EVENT_NOTIFICATION.
    BOOLEAN     IdlePowerManagementEnabled; // The device has been registered for runtime idle power management.
    BOOLEAN     D3ColdEnabled;              // The device will be powered off when put into D3.
    BOOLEAN     D3ColdSupported;            // The platform supports D3Cold for this device.
    BOOLEAN     NoVerifyDuringIdlePower;    // Device require no verification during idle power transitions.
    UCHAR       Reserved[2];
    ULONG       IdleTimeoutInMS;            // The idle timeout value in milliseconds. Only valid if IdlePowerManagementEnabled == TRUE.
} DEVICE_POWER_DESCRIPTOR, *PDEVICE_POWER_DESCRIPTOR;

//
// Output buffer for StorageDeviceCopyOffloadProperty & PropertyStandardQuery
//
typedef struct _DEVICE_COPY_OFFLOAD_DESCRIPTOR {
    ULONG       Version;          // keep compatible with STORAGE_DESCRIPTOR_HEADER
    ULONG       Size;             // keep compatible with STORAGE_DESCRIPTOR_HEADER

    ULONG       MaximumTokenLifetime;
    ULONG       DefaultTokenLifetime;
    ULONGLONG   MaximumTransferSize;
    ULONGLONG   OptimalTransferCount;
    ULONG       MaximumDataDescriptors;
    ULONG       MaximumTransferLengthPerDescriptor;
    ULONG       OptimalTransferLengthPerDescriptor;
    USHORT      OptimalTransferLengthGranularity;
    UCHAR       Reserved[2];
} DEVICE_COPY_OFFLOAD_DESCRIPTOR, *PDEVICE_COPY_OFFLOAD_DESCRIPTOR;

//
// Output buffer for StorageDeviceResiliencyProperty & PropertyStandardQuery
//

typedef _Struct_size_bytes_(Size) struct _STORAGE_DEVICE_RESILIENCY_DESCRIPTOR {

    //
    // Size of this structure serves
    // as the version
    //

    ULONG Version;

    //
    // Size of  this structure  plus
    // all the variable sized fields
    //

    ULONG Size;

    //
    // Friendly name associated with
    // this descriptor
    //

    ULONG NameOffset;

    //
    // Number of  logical  copies of
    // data that are available
    //

    ULONG NumberOfLogicalCopies;

    //
    // Number of  complete copies of
    // data that are stored
    //

    ULONG NumberOfPhysicalCopies;

    //
    // Number of disks that can fail
    // without leading to  data loss
    //

    ULONG PhysicalDiskRedundancy;

    //
    // Number  of columns associated
    // with this descriptor
    //

    ULONG NumberOfColumns;

    //
    // Stripe  width associated with
    // this descriptor, in bytes
    //

    ULONG Interleave;

} STORAGE_DEVICE_RESILIENCY_DESCRIPTOR, *PSTORAGE_DEVICE_RESILIENCY_DESCRIPTOR;


// end_winioctl

//
//  The STORAGE_TIER is an identifier for the storage tier relative to the volume/LUN.
//  The storage tier ID for a particular volume has no relationship to the storage tier
//  ID with the same value on a different volume.
//

#define STORAGE_TIER_NAME_LENGTH           (256)
#define STORAGE_TIER_DESCRIPTION_LENGTH    (512)

#define STORAGE_TIER_FLAG_NO_SEEK_PENALTY  (0x00020000)
#define STORAGE_TIER_FLAG_WRITE_BACK_CACHE (0x00200000)

typedef enum _STORAGE_TIER_MEDIA_TYPE {

    StorageTierMediaTypeUnspecified = 0,
    StorageTierMediaTypeDisk,
    StorageTierMediaTypeSsd

} STORAGE_TIER_MEDIA_TYPE, *PSTORAGE_TIER_MEDIA_TYPE;

typedef struct _STORAGE_TIER {

    //
    // Tier ID
    //

    GUID Id;

    //
    // Name for the tier
    //

    WCHAR Name[STORAGE_TIER_NAME_LENGTH];

    //
    // Note for the tier
    //

    WCHAR Description[STORAGE_TIER_NAME_LENGTH];

    //
    // Flags: STORAGE_TIER_FLAG_xxx
    //

    ULONGLONG Flags; 

    //
    // Provisioned capacity of the tier
    //

    ULONGLONG ProvisionedCapacity;

    //
    // Media type of the tier
    //

    STORAGE_TIER_MEDIA_TYPE MediaType;

} STORAGE_TIER, *PSTORAGE_TIER;

//
//  The response returns a single structure of STORAGE_DEVICE_TIERING_DESCRIPTOR that has
//  all the tiers for this disk.
//

typedef _Struct_size_bytes_(Size) struct _STORAGE_DEVICE_TIERING_DESCRIPTOR {

    //
    // Size of this structure serves
    // as the version
    //

    ULONG Version;

    //
    // Size of  this structure  plus
    // all the variable sized fields
    //

    ULONG Size;

    //
    // Flags. The upper USHORT of these flags is reserved for file system use as
    // this structure is returned slightly tweaked in FSCTL_QUERY_STORAGE_CLASSES_OUTPUT.
    //

    ULONG Flags;

    //
    // The total number of available tiers for this disk
    //

    ULONG TotalNumberOfTiers;

    //
    // The number of tiers that fit in the output
    //

    ULONG NumberOfTiersReturned;

    //
    // Detailed info on the storage tiers.
    //

    _Field_size_(NumberOfTiersReturned) STORAGE_TIER Tiers[ANYSIZE_ARRAY];

} STORAGE_DEVICE_TIERING_DESCRIPTOR, *PSTORAGE_DEVICE_TIERING_DESCRIPTOR;

// begin_winioctl


//
// IOCTL_STORAGE_MANAGE_DATA_SET_ATTRIBUTES
//
// Input Buffer:
//     Structure of type DEVICE_MANAGE_DATA_SET_ATTRIBUTES
//
// Output Buffer:
//      If a particular action uses an output buffer, it will be a structure
//      of type DEVICE_MANAGE_DATA_SET_ATTRIBUTES_OUTPUT optionally followed
//      by a structure specific to that action.
//
//      Actions that use an output buffer are listed below, along with their
//      corresponding structure:
//
//      - DeviceDsmAction_OffloadRead:  STORAGE_OFFLOAD_READ_OUTPUT
//      - DeviceDsmAction_OffloadWrite: STORAGE_OFFLOAD_WRITE_OUTPUT
//      - DeviceDsmAction_Allocation:   DEVICE_DATA_SET_LB_PROVISIONING_STATE
//      - DeviceDsmAction_Scrub:        DEVICE_DATA_SET_SCRUB_OUTPUT
//      - DeviceDsmAction_DrtQuery:     None
//

//
//  This flag, when OR'd into an action indicates that the given action is
//  non-destructive.  If this flag is set then storage stack components which
//  do not understand the action should forward the given request
//

#define DeviceDsmActionFlag_NonDestructive  0x80000000

#define IsDsmActionNonDestructive(_Action) ((BOOLEAN)((_Action & DeviceDsmActionFlag_NonDestructive) != 0))

//
//  Defines the various actions
//

typedef ULONG DEVICE_DATA_MANAGEMENT_SET_ACTION;

    #define DeviceDsmAction_None                0
    #define DeviceDsmAction_Trim                1
    #define DeviceDsmAction_Notification      ( 2  | DeviceDsmActionFlag_NonDestructive)
    #define DeviceDsmAction_OffloadRead       ( 3  | DeviceDsmActionFlag_NonDestructive)
    #define DeviceDsmAction_OffloadWrite        4
    #define DeviceDsmAction_Allocation        ( 5  | DeviceDsmActionFlag_NonDestructive)
    #define DeviceDsmAction_Repair            ( 6  | DeviceDsmActionFlag_NonDestructive)
    #define DeviceDsmAction_Scrub             ( 7  | DeviceDsmActionFlag_NonDestructive)
    #define DeviceDsmAction_DrtQuery          ( 8  | DeviceDsmActionFlag_NonDestructive)
    #define DeviceDsmAction_DrtClear          ( 9  | DeviceDsmActionFlag_NonDestructive)
    #define DeviceDsmAction_DrtDisable        (10  | DeviceDsmActionFlag_NonDestructive)
// end_winioctl
    #define DeviceDsmAction_TieringQuery      (11  | DeviceDsmActionFlag_NonDestructive)
// begin_winioctl
    #define DeviceDsmAction_Map               (12  | DeviceDsmActionFlag_NonDestructive)
    #define DeviceDsmAction_RegenerateParity  (13  | DeviceDsmActionFlag_NonDestructive)

    #define DeviceDsmAction_NvCache_Change_Priority (14 | DeviceDsmActionFlag_NonDestructive)
    #define DeviceDsmAction_NvCache_Evict           (15 | DeviceDsmActionFlag_NonDestructive)

//
//  Flags that are global across all actions
//  These are in the low 16bits of the flags fields
//

#define DEVICE_DSM_FLAG_ENTIRE_DATA_SET_RANGE   0x00000001  // If set, the DataSetRanges fields should be 0


//
//  Flags that are specific to a given verb.
//  These are in the high 16bits of the flags field
//

//
//  DeviceDsmAction_Trim specific flags
//

#define DEVICE_DSM_FLAG_TRIM_NOT_FS_ALLOCATED   0x80000000  // If SET, the described ranges are not allocated by a file system

//
// DeviceDsmAction_Allocation specific flags
//

//
// If set, the device should only return slabs that are eligible for consolidation.
//
#define DEVICE_DSM_FLAG_ALLOCATION_CONSOLIDATEABLE_ONLY   0x40000000

//
//  DeviceDsmAction_Scrub specific flags
//

#define DEVICE_DSM_FLAG_SCRUB_SKIP_IN_SYNC           0x10000000
#define DEVICE_DSM_FLAG_SCRUB_OUTPUT_PARITY_EXTENT   0x20000000

//
//  DeviceDsmAction_Repair specific flags
//

#define DEVICE_DSM_FLAG_REPAIR_OUTPUT_PARITY_EXTENT  0x20000000

//
//  Structure used to describe the list of ranges to process
//

typedef struct _DEVICE_DATA_SET_RANGE {
    LONGLONG    StartingOffset;        //in bytes,  must allign to sector
    ULONGLONG   LengthInBytes;         // multiple of sector size.
} DEVICE_DATA_SET_RANGE, *PDEVICE_DATA_SET_RANGE;

//
// input structure for IOCTL_STORAGE_MANAGE_DATA_SET_ATTRIBUTES
// 1. Value ofParameterBlockOffset or ParameterBlockLength is 0 indicates that Parameter Block does not exist.
// 2. Value of DataSetRangesOffset or DataSetRangesLength is 0 indicates that DataSetRanges Block does not exist.
//     If DataSetRanges Block exists, it contains contiguous DEVICE_DATA_SET_RANGE structures.
// 3. The total size of buffer should be at least:
//      sizeof (DEVICE_MANAGE_DATA_SET_ATTRIBUTES) + ParameterBlockLength + DataSetRangesLength
//
typedef struct _DEVICE_MANAGE_DATA_SET_ATTRIBUTES {
    ULONG                               Size;                   // Size of structure DEVICE_MANAGE_DATA_SET_ATTRIBUTES
    DEVICE_DATA_MANAGEMENT_SET_ACTION   Action;

    ULONG                               Flags;                  // Global flags across all actions

    ULONG                               ParameterBlockOffset;   // must be alligned to corresponding structure allignment
    ULONG                               ParameterBlockLength;   // 0 means Parameter Block does not exist.

    ULONG                               DataSetRangesOffset;    // must be alligned to DEVICE_DATA_SET_RANGE structure allignment.
    ULONG                               DataSetRangesLength;    // 0 means DataSetRanges Block does not exist.

} DEVICE_MANAGE_DATA_SET_ATTRIBUTES, *PDEVICE_MANAGE_DATA_SET_ATTRIBUTES;

//
//  This defines the parameter block for the DeviceDsmAction_Notification
//  action
//

typedef struct _DEVICE_DSM_NOTIFICATION_PARAMETERS {

    ULONG                               Size;                   // Size of this structure

    ULONG                               Flags;                  // Flags specific to the notify operation

    ULONG                               NumFileTypeIDs;         // Count of how many file type ID's are given

    GUID                                FileTypeID[1];          // Identifier for the type of file being notified

} DEVICE_DSM_NOTIFICATION_PARAMETERS, *PDEVICE_DSM_NOTIFICATION_PARAMETERS;

//
//  DEVICE_DSM_NOTIFICATION_PARAMETERS flag definitions
//

#define DEVICE_DSM_NOTIFY_FLAG_BEGIN            0x00000001  // The given LBA range is being used as defined by the FileID
#define DEVICE_DSM_NOTIFY_FLAG_END              0x00000002  // The given LBA range is no longer being used as defined by the FileID

//
// Parameter Block for the DeviceDsmAction_NvCache_Change_Priority action.
//
typedef struct _DEVICE_DSM_NVCACHE_CHANGE_PRIORITY_PARAMETERS {
    ULONG       Size;                   // Size of this structure

    UCHAR       TargetPriority;         // Target priority

    UCHAR       Reserved[3];
} DEVICE_DSM_NVCACHE_CHANGE_PRIORITY_PARAMETERS, *PDEVICE_DSM_NVCACHE_CHANGE_PRIORITY_PARAMETERS;


//
// Parameter structure definitions for copy offload actions
//

//
// Offload copy interface operates in 2 steps : offload read and offload write.
//
// Input for OffloadRead action is set of extends in DSM structure
//   Output parameter of an OffloadRead is a token, returned by the target which will  uniquely identify a "point in time" snapshot of extends taken by the target.
//   Format of the token is opaque to Windows and is specific to the target.
//
//   Note: we arbitrarily limit token length to 512. SCSI interface to OffloadCopy will (may) enable negotiable size. If/when we want to have variable size
//         tokens we will need to create a new action
//
#define STORAGE_OFFLOAD_MAX_TOKEN_LENGTH                        512        // Keep as ULONG multiple
#define STORAGE_OFFLOAD_TOKEN_ID_LENGTH                         0x1F8
#define STORAGE_OFFLOAD_TOKEN_TYPE_ZERO_DATA                    0xFFFF0001

#pragma warning(push)
#pragma warning(disable:4201) // nameless struct/unions
typedef struct _STORAGE_OFFLOAD_TOKEN {
    UCHAR TokenType[4];
    UCHAR Reserved[2];
    UCHAR TokenIdLength[2];
    union {
        struct {
            UCHAR Reserved2[STORAGE_OFFLOAD_TOKEN_ID_LENGTH];
        } StorageOffloadZeroDataToken;
        UCHAR Token[STORAGE_OFFLOAD_TOKEN_ID_LENGTH];
    };
} STORAGE_OFFLOAD_TOKEN, *PSTORAGE_OFFLOAD_TOKEN;
#pragma warning(pop)

#define MAKE_ZERO_TOKEN(T) (                                                   \
    ((PSTORAGE_OFFLOAD_TOKEN)T)->TokenType[0] = 0xFF,                          \
    ((PSTORAGE_OFFLOAD_TOKEN)T)->TokenType[1] = 0xFF,                          \
    ((PSTORAGE_OFFLOAD_TOKEN)T)->TokenType[2] = 0x00,                          \
    ((PSTORAGE_OFFLOAD_TOKEN)T)->TokenType[3] = 0x01,                          \
    ((PSTORAGE_OFFLOAD_TOKEN)T)->TokenIdLength[0] = 0x01,                      \
    ((PSTORAGE_OFFLOAD_TOKEN)T)->TokenIdLength[1] = 0xF8                       \
)

#define IS_ZERO_TOKEN(T) (                                                     \
    (((PSTORAGE_OFFLOAD_TOKEN)T)->TokenType[0] == 0xFF     &&                  \
     ((PSTORAGE_OFFLOAD_TOKEN)T)->TokenType[1] == 0xFF     &&                  \
     ((PSTORAGE_OFFLOAD_TOKEN)T)->TokenType[2] == 0x00     &&                  \
     ((PSTORAGE_OFFLOAD_TOKEN)T)->TokenType[3] == 0x01     &&                  \
     ((PSTORAGE_OFFLOAD_TOKEN)T)->TokenIdLength[0] == 0x01 &&                  \
     ((PSTORAGE_OFFLOAD_TOKEN)T)->TokenIdLength[1] == 0xF8)                    \
)

typedef struct _DEVICE_DSM_OFFLOAD_READ_PARAMETERS {
    ULONG       Flags;                                          // no flags defined yet
    ULONG       TimeToLive;                                     // token TTL in milli-seconds as requested by initiator (TODO: Do we need it exposed to interface caller?)
    ULONG       Reserved[2];                                    // reserved for future use
} DEVICE_DSM_OFFLOAD_READ_PARAMETERS, *PDEVICE_DSM_OFFLOAD_READ_PARAMETERS;

typedef struct _DEVICE_DSM_OFFLOAD_WRITE_PARAMETERS {
    ULONG Flags;                                                // no flags defined yet
    ULONG Reserved;                                             // reserved for future usage
    ULONGLONG TokenOffset;                                      // The starting offset to copy from "snapshot" bound to the token
    STORAGE_OFFLOAD_TOKEN Token;                                // the token
} DEVICE_DSM_OFFLOAD_WRITE_PARAMETERS, *PDEVICE_DSM_OFFLOAD_WRITE_PARAMETERS;

//
// DSM parameters block structure for DeviceDsmAction_Repair
//

typedef struct _DEVICE_DATA_SET_REPAIR_PARAMETERS {

    ULONG NumberOfRepairCopies;                 // The number of copies that will be repaired.
    ULONG SourceCopy;                           // The copy number of the source copy.
    ULONG RepairCopies[ANYSIZE_ARRAY];          // The copy numbers of all the copies that will be repaired.

} DEVICE_DATA_SET_REPAIR_PARAMETERS, *PDEVICE_DATA_SET_REPAIR_PARAMETERS;

#if (NTDDI_VERSION >= NTDDI_WINBLUE)

//
// Parameters block for DeviceDsmAction_Allocation
//
typedef struct _DEVICE_DATA_SET_LBP_STATE_PARAMETERS {
    ULONG   Version;        // Version of this structure.
    ULONG   Size;           // Size of this structure.
    ULONG   Flags;          // No flags defined yet.

    //
    // Version of DEVICE_DATA_SET_LB_PROVISIONING_STATE to return, one of:
    //  - DEVICE_DATA_SET_LB_PROVISIONING_STATE_VERSION_V1
    //  - DEVICE_DATA_SET_LB_PROVISIONING_STATE_VERSION_V2
    //
    ULONG   OutputVersion;  
} DEVICE_DATA_SET_LBP_STATE_PARAMETERS, *PDEVICE_DATA_SET_LBP_STATE_PARAMETERS;

#define DEVICE_DATA_SET_LBP_STATE_PARAMETERS_VERSION_V1 1

#endif

//
// DSM output structure for bi-directional actions.
//
// Output parameter block is located in resultant buffer at the offset contained in OutputBlockOffset field. Offset is calculated from the beginning of the buffer,
// and callee will align it according to the requirement of the action specific structure template.
// Thus future extended bi-directional actions won't require revision of ntddstor.h
//
//   Example: for OffloadRead action in order to get a pointer to the output structure caller shall do
//
//   PSTORAGE_OFFLOAD_READ_OUTPUT pReadOut = (PSTORAGE_OFFLOAD_READ_OUTPUT) ((UCHAR *)pOutputBuffer + ((PDEVICE_MANAGE_DATA_SET_ATTRIBUTES_OUTPUT)pOutputBuffer)->OutputBlockOffset)
//

typedef struct _DEVICE_MANAGE_DATA_SET_ATTRIBUTES_OUTPUT {

    ULONG Size;                                                 // Size of the structure

    DEVICE_DATA_MANAGEMENT_SET_ACTION Action;                   // Action requested and performed

    ULONG       Flags;                                          // Common output flags for DSM actions
    ULONG       OperationStatus;                                // Operation status , used for offload actions (placeholder for richer semantic, like PENDING)
    ULONG       ExtendedError;                                  // Extended error information (Windows or driver extended error)
    ULONG       TargetDetailedError;                            // Target specific error , used for offload actions (SCSI sense code)
    ULONG       ReservedStatus;                                 // Reserved field

    ULONG       OutputBlockOffset;                              // Action specific must be alligned to corresponding structure allignment.
    ULONG       OutputBlockLength;                              // 0 means Output Parameter Block does not exist.

} DEVICE_MANAGE_DATA_SET_ATTRIBUTES_OUTPUT, *PDEVICE_MANAGE_DATA_SET_ATTRIBUTES_OUTPUT;

//
// DSM output structure for DeviceDsmAction_Allocation
//

typedef struct _DEVICE_DATA_SET_LB_PROVISIONING_STATE {

    ULONG     Size;                                 // The size of this structure, including the bitmap, in bytes.
    ULONG     Version;                              // The version of this structure.
    ULONGLONG SlabSizeInBytes;                      // The byte size of a slab
    ULONG     SlabOffsetDeltaInBytes;               // The delta from the given offset in bytes.
    ULONG     SlabAllocationBitMapBitCount;         // The number of relevant bits in the bitmap.
    ULONG     SlabAllocationBitMapLength;           // The number of ULONGS in the bitmap array.
    ULONG     SlabAllocationBitMap[ANYSIZE_ARRAY];  // Slab allocation bitmap, 1 = mapped, 0 = unmapped.

} DEVICE_DATA_SET_LB_PROVISIONING_STATE, *PDEVICE_DATA_SET_LB_PROVISIONING_STATE;

#define DEVICE_DATA_SET_LB_PROVISIONING_STATE_VERSION_V1 (sizeof(DEVICE_DATA_SET_LB_PROVISIONING_STATE))

#if (NTDDI_VERSION >= NTDDI_WINBLUE)

typedef struct _DEVICE_DATA_SET_LB_PROVISIONING_STATE_V2 {

    ULONG     Size;                                 // The size of this structure, including the bitmap, in bytes.
    ULONG     Version;                              // The version of this structure.
    ULONGLONG SlabSizeInBytes;                      // The byte size of a slab
    ULONGLONG SlabOffsetDeltaInBytes;               // The delta from the given offset in bytes.
    ULONG     SlabAllocationBitMapBitCount;         // The number of relevant bits in the bitmap.
    ULONG     SlabAllocationBitMapLength;           // The number of ULONGS in the bitmap array.
    ULONG     SlabAllocationBitMap[ANYSIZE_ARRAY];  // Slab allocation bitmap, 1 = mapped, 0 = unmapped.

} DEVICE_DATA_SET_LB_PROVISIONING_STATE_V2, *PDEVICE_DATA_SET_LB_PROVISIONING_STATE_V2;

#define DEVICE_DATA_SET_LB_PROVISIONING_STATE_VERSION_V2 (sizeof(DEVICE_DATA_SET_LB_PROVISIONING_STATE_V2))

#endif

typedef struct _STORAGE_OFFLOAD_READ_OUTPUT {

    ULONG       OffloadReadFlags;                               // Outbound flags
    ULONG       Reserved;
    ULONGLONG   LengthProtected;                                // The length of the snapshot by token. Must be from the lowest StartingOffset
    ULONG       TokenLength;                                    // Length of the token in bytes.
    STORAGE_OFFLOAD_TOKEN Token;                                // The token created on success.

} STORAGE_OFFLOAD_READ_OUTPUT, *PSTORAGE_OFFLOAD_READ_OUTPUT;

//
// STORAGE_OFFLOAD_READ_OUTPUT flag definitions
//

#define STORAGE_OFFLOAD_READ_RANGE_TRUNCATED (0x0001)

typedef struct _STORAGE_OFFLOAD_WRITE_OUTPUT {

    ULONG       OffloadWriteFlags;                               // Out flags
    ULONG       Reserved;                                        // reserved for future usage
    ULONGLONG   LengthCopied;                                    // Out parameter : The length of content copied from the "snapshot" from the start

} STORAGE_OFFLOAD_WRITE_OUTPUT, *PSTORAGE_OFFLOAD_WRITE_OUTPUT;

//
// STORAGE_OFFLOAD_WRITE_OUTPUT flag definitions - used in OffloadWriteFlags mask
//

#define STORAGE_OFFLOAD_WRITE_RANGE_TRUNCATED (0x0001)          // Write performed, but on a truncated range
#define STORAGE_OFFLOAD_TOKEN_INVALID         (0x0002)          // Token specified in offload write operation is invalid.

//
// DSM output structure for DeviceDsmAction_Scrub
//

typedef struct _DEVICE_DATA_SET_SCRUB_OUTPUT {

    ULONGLONG BytesProcessed;                                   // Number of bytes that were actually processed
    ULONGLONG BytesRepaired;                                    // Number of bytes that were out of sync and fixed
    ULONGLONG BytesFailed;                                      // Number of bytes that could not be read or fixed

} DEVICE_DATA_SET_SCRUB_OUTPUT, *PDEVICE_DATA_SET_SCRUB_OUTPUT;

//
// DSM output structure for DeviceDsmAction_Scrub
//
// ParityExtent is valid only if DEVICE_DSM_FLAG_SCRUB_OUTPUT_PARITY_EXTENT is set
// in DEVICE_MANAGE_DATA_SET_ATTRIBUTES_OUTPUT Flags
// 

typedef struct _DEVICE_DATA_SET_SCRUB_EX_OUTPUT {

    ULONGLONG BytesProcessed;                                   // Number of bytes that were actually processed
    ULONGLONG BytesRepaired;                                    // Number of bytes that were out of sync and fixed
    ULONGLONG BytesFailed;                                      // Number of bytes that could not be read or fixed

    DEVICE_DATA_SET_RANGE ParityExtent;         // Parity extent for stripe regeneration

} DEVICE_DATA_SET_SCRUB_EX_OUTPUT, *PDEVICE_DATA_SET_SCRUB_EX_OUTPUT;

//
// DSM output structure for DeviceDsmAction_Repair
//
// ParityExtent is valid only if DEVICE_DSM_FLAG_REPAIR_OUTPUT_PARITY_EXTENT is set
// in DEVICE_MANAGE_DATA_SET_ATTRIBUTES_OUTPUT Flags
// 

typedef struct _DEVICE_DATA_SET_REPAIR_OUTPUT {

    DEVICE_DATA_SET_RANGE ParityExtent;         // Parity extent for stripe regeneration

} DEVICE_DATA_SET_REPAIR_OUTPUT, *PDEVICE_DATA_SET_REPAIR_OUTPUT;

// end_winioctl

//
// DSM input structure for DeviceDsmAction_TieringQuery.
//
// This IOCTL returns the storage tier regions from the storage
// stack for a particular LUN or volume.
//

typedef struct _DEVICE_DSM_TIERING_QUERY_INPUT {

    ULONG     Version;                      // The version of this structure.
    ULONG     Size;                         // The size of this structure in bytes.

    ULONG     Flags;                        // Reserved for future use.

    ULONG     NumberOfTierIds;              // Number of entries in TierIds, 0 for all for volume
    GUID      TierIds[ANYSIZE_ARRAY];       // Storage tiers to return information for

} DEVICE_DSM_TIERING_QUERY_INPUT, *PDEVICE_DSM_TIERING_QUERY_INPUT;

//
// DSM output structures for DeviceDsmAction_TieringQuery.
//

typedef struct _STORAGE_TIER_REGION {

    GUID        TierId;     // Tier ID

    ULONGLONG   Offset;     // offset of region in bytes
    ULONGLONG   Length;     // length of region in bytes

} STORAGE_TIER_REGION, *PSTORAGE_TIER_REGION;

//
//  The DeviceDsmAction_TieringQuery DSM response returns a single one of these that include
//  multiple STORAGE_TIER_REGION records, one for each region.
//

typedef struct _DEVICE_DSM_TIERING_QUERY_OUTPUT {

    ULONG     Version;                          // The version of this structure.
    ULONG     Size;                             // The size of this structure in bytes.

    ULONG     Flags;                            // Reserved for future use.
    ULONG     Reserved;                         // Reserved for future use.

    ULONGLONG Alignment;                        // in bytes, must align to slab boundary.

    ULONG     TotalNumberOfRegions;             // Total number of available regions.
    ULONG     NumberOfRegionsReturned;          // Number of regions that fit in the output.

    _Field_size_(NumberOfRegionsReturned) STORAGE_TIER_REGION Regions[ANYSIZE_ARRAY]; // Detailed info on the regions.

} DEVICE_DSM_TIERING_QUERY_OUTPUT, *PDEVICE_DSM_TIERING_QUERY_OUTPUT;

// begin_winioctl

//
//  There are some well known GUIDS for certail types of files.  They are
//  defined in NTIFS.H
//

//
// IOCTL_STORAGE_GET_BC_PROPERTIES
//
// Input Buffer:
//     None
//
// Output Buffer:
//     Structure of type STORAGE_GET_BC_PROPERTIES_OUTPUT
//

typedef struct _STORAGE_GET_BC_PROPERTIES_OUTPUT {

    //
    // Specifies the maximum number of requests
    // that can be scheduled per period of time
    //
    ULONG MaximumRequestsPerPeriod;

    //
    // Specifies the minimum period that the
    // device uses  when scheduling requests
    //
    ULONG MinimumPeriod;

    //
    // Specifies the maximum transfer size supported
    // for  bandwidth contracts  on this  device. To
    // achieve the highest level of performance, all
    // requests should be of this size
    //
    ULONGLONG MaximumRequestSize;

    //
    // Specifies the estimated time taken to
    // perform an  Io operstion. This  field
    // is  for  informational purposes  only
    //
    ULONG EstimatedTimePerRequest;

    //
    // Specifies the number of requests that should be
    // kept outstanding.  This helps  keep the  device
    // device busy and thus obtain maximum throughput.
    // This will only be filled in if the target  file
    // has an outstanding contract.
    //
    ULONG NumOutStandingRequests;

    //
    // Specifies the required size of requests in this
    // stream.  This  will  only  be filled in  if the
    // target file has an outstanding contract.
    //
    ULONGLONG RequestSize;

} STORAGE_GET_BC_PROPERTIES_OUTPUT, *PSTORAGE_GET_BC_PROPERTIES_OUTPUT;


//
// IOCTL_STORAGE_ALLOCATE_BC_STREAM
//
// Input Buffer:
//     Structure of type STORAGE_ALLOCATE_BC_STREAM_INPUT
//
// Output Buffer:
//     Structure of type STORAGE_ALLOCATE_BC_STREAM_OUTPUT
//


//
// Current version
//
#define IOCTL_STORAGE_BC_VERSION                1

typedef struct _STORAGE_ALLOCATE_BC_STREAM_INPUT {

    //
    // Specifies the corresponding structure version
    //
    ULONG Version;

    //
    // Specifies the number of requests that
    // need to  complete  per period of time
    //
    ULONG RequestsPerPeriod;

    //
    // Specifies the period of time wherein the
    // above  number of requests  must complete
    //
    ULONG Period;

    //
    // Indicates whether failures
    // should  be retried  or not
    //
    BOOLEAN RetryFailures;

    //
    // Indicates whether reqests that  will miss
    // their deadline should be discarded or not
    //
    BOOLEAN Discardable;

    //
    // Helps align the following field
    //
    BOOLEAN Reserved1[2];

    //
    // Indicates whether the  Io  will be
    // comprised of reads, writes or both
    //
    ULONG AccessType;

    //
    // Indicates whether the  Io  to the
    // file will be sequential or random
    //
    ULONG AccessMode;

} STORAGE_ALLOCATE_BC_STREAM_INPUT, *PSTORAGE_ALLOCATE_BC_STREAM_INPUT;

typedef struct _STORAGE_ALLOCATE_BC_STREAM_OUTPUT {

    //
    // Specifies the required size
    // of  requests in this stream
    //
    ULONGLONG RequestSize;

    //
    // Specifies the number of requests that should be
    // kept outstanding.  This helps  keep the  device
    // device busy and thus obtain maximum  throughput
    //
    ULONG NumOutStandingRequests;

} STORAGE_ALLOCATE_BC_STREAM_OUTPUT, *PSTORAGE_ALLOCATE_BC_STREAM_OUTPUT;


//
// IOCTL_STORAGE_FREE_BC_STREAM
//
// Input Buffer:
//     None
//
// Output Buffer:
//     None
//

//
// IOCTL_STORAGE_CHECK_PRIORITY_HINT_SUPPORT
//
// Input Buffer :
//      None
// Output Buffer :
//      Structure of type STORAGE_PRIORITY_HINT_SUPPORT
//

#define STORAGE_PRIORITY_HINT_SUPPORTED     0x0001

typedef struct _STORAGE_PRIORITY_HINT_SUPPORT {
    ULONG SupportFlags;
} STORAGE_PRIORITY_HINT_SUPPORT, *PSTORAGE_PRIORITY_HINT_SUPPORT;



#pragma warning(push)
#pragma warning(disable:4200)

#if defined(_MSC_EXTENSIONS)

typedef struct _STORAGE_MEDIA_SERIAL_NUMBER_DATA {

    USHORT Reserved;

    //
    // the SerialNumberLength will be set to zero
    // if the command is supported and the media
    // does not have a valid serial number.
    //

    USHORT SerialNumberLength;

    //
    // the following data is binary, and is not guaranteed
    // to be NULL terminated.  this is an excercise for the
    // caller.
    //

#if !defined(__midl)
    UCHAR SerialNumber[0];
#endif

} STORAGE_MEDIA_SERIAL_NUMBER_DATA, *PSTORAGE_MEDIA_SERIAL_NUMBER_DATA;

#endif /* _MSC_EXTENSIONS */

typedef _Struct_size_bytes_(Size) struct _STORAGE_READ_CAPACITY {

    //
    // The version number, size of the STORAGE_READ_CAPACITY structure
    //
    ULONG Version;

    //
    // The size of the date returned, size of the STORAGE_READ_CAPACITY structure
    //
    ULONG Size;

    //
    // Number of bytes per block
    //

    ULONG BlockLength;

    //
    // Total number of blocks in the disk
    // This will have the last LBA + 1
    //

    LARGE_INTEGER NumberOfBlocks;

    //
    // Disk size in bytes
    //

    LARGE_INTEGER DiskLength;

} STORAGE_READ_CAPACITY, *PSTORAGE_READ_CAPACITY;

#pragma warning(pop)

//
// Device write cache property
//
// This property provides the write cache information
// about the target device.
//

typedef enum _WRITE_CACHE_TYPE {
    WriteCacheTypeUnknown,
    WriteCacheTypeNone,
    WriteCacheTypeWriteBack,
    WriteCacheTypeWriteThrough
} WRITE_CACHE_TYPE;

typedef enum _WRITE_CACHE_ENABLE {
    WriteCacheEnableUnknown,
    WriteCacheDisabled,
    WriteCacheEnabled
} WRITE_CACHE_ENABLE;

typedef enum _WRITE_CACHE_CHANGE {
    WriteCacheChangeUnknown,
    WriteCacheNotChangeable,
    WriteCacheChangeable
} WRITE_CACHE_CHANGE;

typedef enum _WRITE_THROUGH {
    WriteThroughUnknown,
    WriteThroughNotSupported,
    WriteThroughSupported
} WRITE_THROUGH;

typedef _Struct_size_bytes_(Size) struct _STORAGE_WRITE_CACHE_PROPERTY {

    //
    // The version number
    // Size of STORAGE_WRITE_CACHE_PROPERTY structure
    //
    ULONG Version;

    //
    // The size of the date returned
    // Size of STORAGE_WRITE_CACHE_PROPERTY structure
    //
    ULONG Size;

    //
    // Current write cache type
    //
    WRITE_CACHE_TYPE WriteCacheType;

    //
    // Current write cache value
    //
    WRITE_CACHE_ENABLE WriteCacheEnabled;

    //
    // Device write cache change capability
    //
    WRITE_CACHE_CHANGE WriteCacheChangeable;

    //
    // Device write through support capability
    //
    WRITE_THROUGH WriteThroughSupported;

    //
    // Device flush cache capability
    //
    BOOLEAN FlushCacheSupported;

    //
    // User selected power protection option through registry
    //
    BOOLEAN UserDefinedPowerProtection;

    //
    // Device has battery backup for write cache
    //
    BOOLEAN NVCacheEnabled;

} STORAGE_WRITE_CACHE_PROPERTY, *PSTORAGE_WRITE_CACHE_PROPERTY;

#pragma warning(push)
#pragma warning(disable:4200) // array[0]
#pragma warning(disable:4201) // nameless struct/unions
#pragma warning(disable:4214) // bit fields other than int


#if defined(_MSC_EXTENSIONS)

typedef struct _PERSISTENT_RESERVE_COMMAND {

    ULONG Version;
    ULONG Size;

    union {

        struct {

            //
            // Persistent Reserve service action.
            //

            UCHAR ServiceAction : 5;
            UCHAR Reserved1 : 3;

            //
            // Number of bytes allocated for returned parameter list.
            //

            USHORT AllocationLength;

        } PR_IN;

        struct {

            //
            // Persistent Reserve service action.
            //

            UCHAR ServiceAction : 5;
            UCHAR Reserved1 : 3;

            //
            // Persistent Reserve type and scope.
            //

            UCHAR Type : 4;
            UCHAR Scope : 4;

            //
            // Space for additional PR Out parameters.
            //

#if !defined(__midl)
            UCHAR ParameterList[0];
#endif

        } PR_OUT;
    };

} PERSISTENT_RESERVE_COMMAND, *PPERSISTENT_RESERVE_COMMAND;

#endif /* _MSC_EXTENSIONS */
#pragma warning(pop)

//
//  Device telemetry definitions
//
//  Structures and interfaces dealing with acquistion of device and driver internal telemetry.
//

// For variable size fields we use byte array, defined with zero length in structure template. Length of the field is stored as a separate field.
// No more than one variable size field is allowed in one structure and it is always placed last.

#pragma warning(push)


//
// Persistent data structures are versioned and "sized" by adding structure version field and structure size field
//
#define DEVICEDUMP_STRUCTURE_VERSION_V1         1

//
// Max size of the identification string
//
#define DEVICEDUMP_MAX_IDSTRING 32       // Keep proportional to sizeof (ULONG)
#define MAX_FW_BUCKET_ID_LENGTH 132     // 128 (ACS specification + 1 for zero termination + 3 to align on ULONG)


//
// Global telemetry collection parameters in the registry
//
#define STORAGE_CRASH_TELEMETRY_REGKEY  L"\\Registry\\Machine\\System\\CurrentControlSet\\Control\\CrashControl\\StorageTelemetry"
#define STORAGE_DEVICE_TELEMETRY_REGKEY L"\\Registry\\Machine\\System\\CurrentControlSet\\Control\\Storage\\StorageTelemetry"

//
// Reasons for telemetry collection
//
typedef enum _DEVICEDUMP_COLLECTION_TYPE {
    TCCollectionBugCheck = 1,                   // 1
    TCCollectionApplicationRequested,           // 2 (Host Initiated - HITC)
    TCCollectionDeviceRequested                 // 3 (Device initiated - DITC)
} DEVICEDUMP_COLLECTION_TYPEIDE_NOTIFICATION_TYPE, *PDEVICEDUMP_COLLECTION_TYPE;

//
// Flags for the device dump section
//
#define DDUMP_FLAG_DATA_READ_FROM_DEVICE        0x0001

//
// Firmware issue IDs (similar to bug check reasons)
//
#define FW_ISSUEID_NO_ISSUE     0x00000000
#define FW_ISSUEID_UNKNOWN      0xFFFFFFFF

//
#include <pshpack1.h>   // Structures are packed on a byte boundary , because parsers may run on separate machines and different OS flavors

//
//  Device dump section contains common device dump header, followed by set of relative pointers to sub sections
//  Each relative pointer contain size in bytes of the subsection and starting offset from the beginning of the section
//
// Layout of the device dump section is as
//
//   HEADER         - common descriptor
//   PUBLIC DATA    - publicly accessible data (eg SMART structures)
//   RESRICTED DATA - restricted access data (eg encrypted with Microsoft and IHV public keys)
//   PRIVATE DATA   - private device data
//
// All fields in the section definition are used cross platform => types used are platform neutral
//

//
// Relative descript    or of a subsection, contains size of the subsection and relative offset (0 is the start of the section)
//
typedef struct _DEVICEDUMP_SUBSECTION_POINTER {
        ULONG    dwSize;        // Size (in bytes) of the subsection
        ULONG    dwFlags;       // Parameter flags for the subsection
        ULONG    dwOffset;      // Offset (in bytes) of the subsection block from the start of the buffer
} DEVICEDUMP_SUBSECTION_POINTER,*PDEVICEDUMP_SUBSECTION_POINTER;

//
// Data structure tagging fields (version and size)
//
typedef struct _DEVICEDUMP_STRUCTURE_VERSION {
        //
        // Header signature, useful for identifying the structure when reading the dump
        //
        ULONG   dwSignature;

        //
        // Version of the template
        //
        ULONG   dwVersion;

        //
        // Size of the parent structure in bytes
        //
        ULONG   dwSize;

} DEVICEDUMP_STRUCTURE_VERSION, *PDEVICEDUMP_STRUCTURE_VERSION;

//
//  Device data header for the secondary data (in crashdump) section , holding device dump information.
//
typedef  struct _DEVICEDUMP_SECTION_HEADER {
        //
        // GUID, identifying device dump section. Same GUID as used in registering for SecondaryData callback, stored here for live telemetry interface consistency
        //
        GUID    guidDeviceDataId;

        //
        // Device identification fields.
        // These fields together should uniquely identify the device firmware image.

        //
        //  ID value, common for storage device vendors. This ID will be used by !analyze to create a vendor ID for WinQual.
        //
        //
        // Unique identifier assigned to the organization responsible for device quality (firmware quality). In most cases this is OUID (IEEE) or WorldWideName of the device vendor
        //
        UCHAR    sOrganizationID[16];

        //
        // Firmware revision as indicated in IDENITFY or INQUIRY structures
        //
        ULONG    dwFirmwareRevision;

        //
        // Device model number (keep the length of the field proportional to sizeof (ULONG))
        //
        UCHAR   sModelNumber[DEVICEDUMP_MAX_IDSTRING];

        //
        // Vendor specific device cookie, identifying process and manufacturing parameters. Opaque to the OS and applications.
        //
        UCHAR   szDeviceManufacturingID[DEVICEDUMP_MAX_IDSTRING];       // Keep the length of the field proportional to sizeof (ULONG)

        //
        // Sourcing indicator flag - used to detect if data was emulated from other structures or obtained directly from the firmware using log command
        //      Set to 1 if public data was filled in using data from the device telemetry log
        //      Set to 0 if the device doesn't support the command and the driver filled in as best it could
        //
        ULONG  dwFlags;

        //
        // Version of private data as indicated by the firmware.Initially always 0 to specify Private only unspecified data
        //
        ULONG bRestrictedPrivateDataVersion;

        //
        // Issue identifier (hash value) generated by the firmware. Reflects state of the device firmware and used for cross device type/vendor queries.
        // We will rely on standardized namespace of issue IDs and good will of firmware developers to taxonomize
        //
        ULONG dwFirmwareIssueId;                //currently unused

        //
        // Firmware bucket ID - long string, opague to Windows , but useful to create unique bucket in concatenation with device identification data
        //
        UCHAR    szIssueDescriptionString[MAX_FW_BUCKET_ID_LENGTH];      // zero terminated

} DEVICEDUMP_SECTION_HEADER, *PDEVICEDUMP_SECTION_HEADER;

//
//  Public subsection header - subsection is holding data, describing device state and accessible to everybody.
//

#define TC_PUBLIC_DEVICEDUMP_CONTENT_SMART      0x01
#define TC_PUBLIC_DEVICEDUMP_CONTENT_GPLOG      0x02

//
// Maximum number of log pages collected into the public section
#define TC_PUBLIC_DEVICEDUMP_CONTENT_GPLOG_MAX  16

// Maximum length of the description of the collected pages (filled by the miniport)
#define TC_DEVICEDUMP_SUBSECTION_DESC_LENGTH    16

//
// Standard types of collected pages
//
#define TC_PUBLIC_DATA_TYPE_ATAGP "ATAGPLogPages"
#define TC_PUBLIC_DATA_TYPE_ATASMART "ATASMARTPages"

//
// Public data is tagged with the table of "log descriptors". Each descriptor has LogAddress and number of pages.
// Specific meaning, assigned to the descriptor, is relative to the command set used.
//

typedef struct _GP_LOG_PAGE_DESCRIPTOR {
        USHORT  LogAddress;
        USHORT  LogSectors;
} GP_LOG_PAGE_DESCRIPTOR,*PGP_LOG_PAGE_DESCRIPTOR;

typedef struct _DEVICEDUMP_PUBLIC_SUBSECTION {
        ULONG   dwFlags;
        GP_LOG_PAGE_DESCRIPTOR  GPLogTable[TC_PUBLIC_DEVICEDUMP_CONTENT_GPLOG_MAX];
        CHAR    szDescription[TC_DEVICEDUMP_SUBSECTION_DESC_LENGTH]; // Zero terminated
        UCHAR   bData[ANYSIZE_ARRAY];      // Data byte array ANYSIZE_ARRAY
} DEVICEDUMP_PUBLIC_SUBSECTION, *PDEVICEDUMP_PUBLIC_SUBSECTION;

//
//  Restricted subsection header - subsection is holding data, describing device state and accessible only to Microsoft and a device vendor
//
typedef struct _DEVICEDUMP_RESTRICTED_SUBSECTION {

        UCHAR   bData[ANYSIZE_ARRAY];           // Data byte array (ANYSIZE_ARRAY)

} DEVICEDUMP_RESTRICTED_SUBSECTION, *PDEVICEDUMP_RESTRICTED_SUBSECTION;

//
//  Private subsection header - subsection is holding data, describing device state and accessible only to a device vendor
//
typedef struct _DEVICEDUMP_PRIVATE_SUBSECTION {

        ULONG   dwFlags;
        GP_LOG_PAGE_DESCRIPTOR GPLogId;

        UCHAR   bData[ANYSIZE_ARRAY];   // Data byte array (ANYSIZE_ARRAY)

} DEVICEDUMP_PRIVATE_SUBSECTION, *PDEVICEDUMP_PRIVATE_SUBSECTION;

//
// Descriptor of the storage device dump section
//
typedef _Struct_size_bytes_(Descriptor.dwSize) struct _DEVICEDUMP_STORAGEDEVICE_DATA {

        //
        // Common descriptor (signature,version of the structure)
        //
        DEVICEDUMP_STRUCTURE_VERSION    Descriptor;

        //
        // Header - set of fields, describing dump section and device (not requiring protocol communication)
        //
        DEVICEDUMP_SECTION_HEADER SectionHeader;

        //
        // Size of the whole section buffer, in bytes , including header and sum total of all the variable sized sub sections
        //
        ULONG   dwBufferSize;

        //
        // Reason for collecting telemetry
        //
        ULONG   dwReasonForCollection;

        //
        // "Pointers" to individual sub-sections. Sub sections are filled with the information, obtained from the device
        //
        DEVICEDUMP_SUBSECTION_POINTER PublicData;
        DEVICEDUMP_SUBSECTION_POINTER RestrictedData;
        DEVICEDUMP_SUBSECTION_POINTER PrivateData;

} DEVICEDUMP_STORAGEDEVICE_DATA, *PDEVICEDUMP_STORAGEDEVICE_DATA;


//
// Driver dump section contains common device driver context information:
//      - circular buffer of the IO requests as visible by the lower edge of the driver
//              (in case of storage that would be an interface to the controller stack or controller itself)
//
// All fields in the section definition are used cross platform => types used are platform neutral
//

//
// Format of the single record for publicly accessible driver state table
//

#define         CDB_SIZE                  16
#define         TELEMETRY_COMMAND_SIZE    16

#define         TCRecordStorportSrbFunction       Command[0]

typedef struct _DEVICEDUMP_STORAGESTACK_PUBLIC_STATE_RECORD {
        // The CDB for this request. variable sized CDBs are truncated.
        UCHAR     Cdb[CDB_SIZE];

        // The actual command for this request.
        UCHAR     Command[TELEMETRY_COMMAND_SIZE];

        // the time when driver received the request
        ULONGLONG StartTime;

        // the system time when the request was completed
        ULONGLONG EndTime;

        // Status value ()
        ULONG  OperationStatus;

        // Error value (eg error reg for ATAPort, SCSI error for storport)
        ULONG   OperationError;

        // Stack specific information
        union {
         struct {
                ULONG dwReserved;
                } ExternalStack;

         struct {
                ULONG   dwAtaPortSpecific;
         }  AtaPort;

         struct {
                ULONG   SrbTag  ;
         }  StorPort;

        } StackSpecific;

} DEVICEDUMP_STORAGESTACK_PUBLIC_STATE_RECORD,*PDEVICEDUMP_STORAGESTACK_PUBLIC_STATE_RECORD;


typedef _Struct_size_bytes_(Descriptor.dwSize) struct _DEVICEDUMP_STORAGESTACK_PUBLIC_DUMP {

        //
        // Common descriptor (signature,version of the structure)
        //
        DEVICEDUMP_STRUCTURE_VERSION    Descriptor;

        //
        // Reason for collecting telemetry
        //
        ULONG   dwReasonForCollection;

        //
        // Driver stack and instance
        //
        UCHAR   cDriverName[16];

        //
        // Standardized log of IO requests issued to the target, starting with number of records.
        // Log is circular, order is not guaranteed
        //
        ULONG   uiNumRecords;

        DEVICEDUMP_STORAGESTACK_PUBLIC_STATE_RECORD RecordArray[ANYSIZE_ARRAY]; //ANYSIZE_ARRAY

} DEVICEDUMP_STORAGESTACK_PUBLIC_DUMP,*PDEVICEDUMP_STORAGESTACK_PUBLIC_DUMP;

// End of the packed structure group
#include <poppack.h>


//
// Telemetry information block descriptor - bit flags in DumpCapabilities field
//

#define DEVICEDUMP_CAP_PRIVATE_SECTION          0x00000001      // Target supports private data
#define DEVICEDUMP_CAP_RESTRICTED_SECTION       0x00000002      // Target supports restricted data



#pragma warning(push)
#pragma warning(disable:4214) // bit fields other than int

//
// IOCTL_STORAGE_ENABLE_IDLE_POWER
//
// Input Buffer:
//      A STORAGE_IDLE_POWER structure specifying the idle power management
//      properties of the device.
//
// Output Buffer:
//      None.
//
typedef struct _STORAGE_IDLE_POWER {
    ULONG Version;              // Structure version, should be set to 1 for Win8.
    ULONG Size;                 // Size of this structure in bytes.
    ULONG WakeCapableHint : 1;  // Storage device supports wake from low power states.
    ULONG D3ColdSupported : 1;  // Storage device supports D3Cold
    ULONG Reserved : 30;
    ULONG D3IdleTimeout;        // Idle time in msec before storage device is transitioned to D3 (max of ~49.7 days).
} STORAGE_IDLE_POWER, *PSTORAGE_IDLE_POWER;

#pragma warning(pop)

//
// IOCTL_STORAGE_GET_IDLE_POWERUP_REASON
//
// Input Buffer:
//      None.
//
// Output Buffer:
//      A STORAGE_IDLE_POWERUP_REASON structure specifying what caused the power up.
//
typedef enum _STORAGE_POWERUP_REASON_TYPE {
  StoragePowerupUnknown           = 0,
  StoragePowerupIO,
  StoragePowerupDeviceAttention
} STORAGE_POWERUP_REASON_TYPE, *PSTORAGE_POWERUP_REASON_TYPE;

typedef struct _STORAGE_IDLE_POWERUP_REASON {
    ULONG Version;                          // Structure version, should be set to 1 for Win8.
    ULONG Size;                             // Size of this structure in bytes.
    STORAGE_POWERUP_REASON_TYPE PowerupReason;   // The reason for the power up (see above).
} STORAGE_IDLE_POWERUP_REASON, *PSTORAGE_IDLE_POWERUP_REASON;

#define STORAGE_IDLE_POWERUP_REASON_VERSION_V1 1

//
// IOCTL_STORAGE_EVENT_NOTIFICATION
//
// Input Buffer:
//      A STORAGE_EVENT_NOTIFICATION structure specifying the event(s) that occurred.
//
// Output Buffer:
//      None
//
typedef struct _STORAGE_EVENT_NOTIFICATION {
    ULONG Version;                          // Structure version, should be set to 1 for Win8.
    ULONG Size;                             // Size of this structure in bytes.
    ULONGLONG Events;                       // Bitmask of event(s) that occurred.
} STORAGE_EVENT_NOTIFICATION, *PSTORAGE_EVENT_NOTIFICATION;

#define STORAGE_EVENT_NOTIFICATION_VERSION_V1 1

#define STORAGE_EVENT_MEDIA_STATUS        0x0000000000000001
#define STORAGE_EVENT_DEVICE_STATUS       0x0000000000000002
#define STORAGE_EVENT_DEVICE_OPERATION    0x0000000000000004

#define STORAGE_EVENT_ALL (STORAGE_EVENT_MEDIA_STATUS | STORAGE_EVENT_DEVICE_STATUS | STORAGE_EVENT_DEVICE_OPERATION)

#pragma warning(pop)


#define READ_COPY_NUMBER_KEY                    0x52434e00  // 'RCN'

#define IsKeyReadCopyNumber(_k)                 (((_k) & 0xFFFFFF00) == READ_COPY_NUMBER_KEY)

#define ReadCopyNumberToKey(_c)                 (READ_COPY_NUMBER_KEY | (UCHAR)(_c))
#define ReadCopyNumberFromKey(_k)               (UCHAR)((_k) & 0x000000FF)


#ifdef __cplusplus
}
#endif


#endif // _NTDDSTOR_H_
// end_winioctl


#endif /* WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP) */
#pragma endregion

